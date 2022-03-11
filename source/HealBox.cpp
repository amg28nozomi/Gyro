/*****************************************************************//**
 * @file   HealBox.cpp
 * @brief  回復ボックスクラスの定義
 * 
 * @author 鈴木希海
 * @date   March 2022
 *********************************************************************/
#include "HealBox.h"
#include "ApplicationMain.h"
#include "CollisionAABB.h"
#include "CollisionCapsule.h"
#include "EffectComponent.h"
#include "ObjectServer.h"
#include "Player.h"

namespace Gyro {
  namespace Object {

    HealBox::HealBox(Application::ApplicationMain& app) : ObjectBase(app) {
      _id = ObjectId::Field;
      _state = ObjectState::Active;
      _healPoint = 300.0f / 600.0f;
    }

    bool HealBox::Process() {
      // 基底クラス側の更新処理を呼び出し
      ObjectBase::Process();
      // 再生時間が一定を下回った場合
      if (_totalTime <= 0.0f) {
        // 死亡状態に遷移する
        _state = ObjectState::Dead;
        return true;
      }
      // 生存時間を減少させる
      _totalTime -= _speed;
      // 自機を回復させる
      HealPlayer();
      return true;
    }

    bool HealBox::IsInvasion(const CollisionCapsule& capsule, float& heal) const {
      const auto [min, max] = capsule.LineSegment().GetVector();
      if (_collision->CheckPoint(min) || _collision->CheckPoint(max)) {
        // 回復量を返す
        heal = _healPoint;
        return true;
      }
      return false;
    }

    bool HealBox::HealPlayer() {
      // 自機の取得
      auto player = _app.GetObjectServer().GetPlayer();
      // 取得に失敗した場合はスキップ
      if (player == nullptr) return false;
      // 接触している場合は自機を回復する
      if (_collision->CheckPoint(player->GetPosition())) {
        // 回復処理を開始する
        player->Heal(_healPoint);
        return true;
      }
      return false;
    }

    bool HealBox::SetParam(const AppMath::Vector4& position, const float totalTime, const float speed) {
      // 設定は既に行われているか
      if (_speed) {
        return false; // 既に登録されている
      }
      // 座標の設定
      _position = position;
      // 当たり判定情報の生成

      // 再生時間と再生速度の設定
      _totalTime = totalTime;
      _speed = speed;
      return true;
    }
  } // namespace Object
} // 

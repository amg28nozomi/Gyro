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

namespace Gyro {
  namespace Object {

    HealBox::HealBox(Application::ApplicationMain& app) : ObjectBase(app) {
      _state = ObjectState::Active;
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
      return true;
    }

    bool HealBox::IsInvasion(const CollisionCapsule& capsule) const {
      // カプセルとAABBの衝突判定を行う
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

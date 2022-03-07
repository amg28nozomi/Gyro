/*****************************************************************//**
 * @file   AttackComponent.cpp
 * @brief  攻撃コンポーネントクラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "AttackComponent.h"
#include "ObjectBase.h"
#include "CollisionBase.h"
#include "ApplicationMain.h"

namespace Gyro {
  namespace Object {

    AttackComponent::AttackComponent(ObjectBase& owner, std::shared_ptr<CollisionBase> collision) : _owner(owner) {
      _state = AttackState::NonActive;
      // 攻撃判定用のコリジョン情報をセット
      _collision.emplace_back(std::move(collision));
      _collision.clear();
      _speed = 10.0f;
    }

    AttackComponent::AttackComponent(ObjectBase& owner, std::vector<std::shared_ptr<CollisionBase>> collisions) : _owner(owner) {
      _state = AttackState::NonActive;
      // 攻撃判定用のコリジョン情報をセット
      _collision = collisions;
    }

    void AttackComponent::Finish() {
      _state = AttackState::NonActive;
      // 攻撃判定を修正する
      for (auto collision : _collision) {
        collision->SetPosition(_owner.GetPosition());
      }
      _indexs.clear(); // フレーム情報の削除
    }

    bool AttackComponent::Process(const AppFrame::Math::Vector4& localPosition) {
      // モーション中以外は当たり判定の更新を行わない
      if (_state == AttackState::NonActive) {
        return false;
      }
      auto pos = localPosition;
      // 座標更新
      // 移動量分、当たり判定の更新を行う
      _collision.front()->SetPosition(pos);
      // 当たり判定情報の更新
      _collision.front()->Process();
      return true;
    }

    bool AttackComponent::Process() {
      // 活動状態か
      if (_state != AttackState::Active) {
        // インターバル中の場合は処理を行う
        if (IsInterval()) {
          Interval();
        }
        return false;
      }
      // セットされたフレーム回分判定を行う
      for (auto num = 0; auto frame : _indexs) {
        // 当たり判定座標をセットする
        _collision.at(num)->SetPosition(_owner.GetFramePosition(frame));
        // コリジョンの更新
        _collision.at(num)->Process();
      }
      return true; // 正常終了
    }

    void AttackComponent::SetFrame(std::vector<int> frames, std::vector<std::shared_ptr<CollisionBase>> collisions) {
      // フレーム番号の切り替え
      _indexs = frames;
      // コリジョン情報の切り替え
      _collision = collisions;
    }

#ifdef _DEBUG
    void AttackComponent::Draw() const {
      // 攻撃判定中のみ当たり判定の描画を実行する
      if (_state == AttackState::Active) {
        for (auto collision : _collision) {
          collision->Draw();
        }
      }
    }
#endif

    void AttackComponent::SetInterval(const float time, const float speed) {
      // 時間が一定未満の場合は設定しない
      if (time <= 0.0f) {
        return;
      }
      // インターバル状態に遷移
      _state = AttackState::Interval;
      _time = time;
      _speed = speed;
    }

    AppFrame::Math::Matrix44 AttackComponent::LocalToWorld(const AppFrame::Math::Vector4& local) const {
      auto position = _owner.GetPosition() + local;
      // ワールド変換行列の取得
#ifndef _DEBUG
      return AppMath::Utility::ToWorldMatrix(position, _owner.GetRotation(), AppMath::Vector4(1.0f, 1.0f, 1.0f));
#else
      return AppMath::Utility::ToWorldMatrix(position, _owner.GetRotation(), AppMath::Vector4(1.0f, 1.0f, 1.0f), AppMath::Degree);
#endif
    }

    void AttackComponent::Interval() {
      // インターバル処理を終了するかの判定
      if (_time <= 0.0f) {
        // 通常状態に遷移してい処理を終了する
        _state = AttackState::NonActive;
        _time = 0.0f;
        return;
      }
      // インターバル時間を経過させる
      _time -= _speed;
    }
  } // mamespace Object
} // namespace Gyro
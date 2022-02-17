/*****************************************************************//**
 * @file   AttackComponent.cpp
 * @brief  攻撃コンポーネントクラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "AttackComponent.h"
#include "ObjectBase.h"
#include "CollisionCapsule.h"

namespace Gyro {
  namespace Object {

    AttackComponent::AttackComponent(ObjectBase& owner, std::shared_ptr<CollisionBase> collision) : _owner(owner) {
      _state = AttackState::NonActive;
      // 攻撃判定用のコリジョン情報をセット
      _collision = std::move(collision);
    }

    void AttackComponent::Finish() {
      _state = AttackState::NonActive;
      _collision->SetPosition(_owner.GetPosition());
    }

    bool AttackComponent::Process(const AppMath::Vector4& localPosition) {
      // モーション中以外は当たり判定の更新を行わない
      if (_state == AttackState::NonActive) {
        return false;
      }
      auto pos = localPosition;
      // 座標更新
      // auto pos = LocalToWorld(_owner.GetPosition()) * localPosition;
      // 移動量分、当たり判定の更新を行う
      _collision->SetPosition(pos);
      // 当たり判定情報の更新
      _collision->Process();
      return true;
    }

#ifdef _DEBUG
    void AttackComponent::Draw() const {
      // 攻撃判定中のみ当たり判定の描画を実行する
      if (_state == AttackState::Active) {
        _collision->Draw();
      }
    }
#endif

    AppMath::Matrix44 AttackComponent::LocalToWorld(const AppMath::Vector4& local) const {
      auto position = _owner.GetPosition() + local;
      // ワールド変換行列の取得
#ifndef _DEBUG
      return AppMath::Utility::ToWorldMatrix(position, _owner.GetRotation(), AppMath::Vector4(1.0f, 1.0f, 1.0f));
#else
      return AppMath::Utility::ToWorldMatrix(position, _owner.GetRotation(), AppMath::Vector4(1.0f, 1.0f, 1.0f), AppMath::Degree);
#endif
    }
  } // mamespace Object
} // namespace Gyro
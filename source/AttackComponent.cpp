#include "AttackComponent.h"
#include "ObjectBase.h"
#include "CollisionCapsule.h"

namespace Gyro {
  namespace Object {

    AttackComponent::AttackComponent(ObjectBase& owner, std::shared_ptr<CollisionBase> collision) : _owner(owner) {
      // 攻撃判定用のコリジョン情報をセット
      _collision = std::move(collision);
    }

    bool AttackComponent::Process(const AppMath::Vector4& localPosition) {
      // 座標更新
      auto pos = LocalToWorld(AppMath::Vector4()) * localPosition;
      // 移動量分、当たり判定の更新を行う
      _collision->SetPosition(pos);
      // 当たり判定情報の更新
      _collision->Process();
      return true;
    }

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
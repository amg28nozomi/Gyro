#include "WireComponent.h"
#include "ObjectBase.h"

namespace Gyro {
  namespace Player {

    WireComponent::WireComponent(Object::ObjectBase& owner) : _owner(owner) {
      _type = ComponentType::Wire;
    }

    bool WireComponent::SetTarget(const Vector4& target) {
      // 所有者の現在座標とターゲット座標から距離と向きを算出
      auto v = target - _owner.GetPosition();
      // 向きベクトルを更新する
      _forward = Vector4::Normalize(v);
      // 移動量を算出する
      return false;
    }

    AppMath::Matrix44 WireComponent::Move() const {
      return AppMath::Matrix44::Translate(_forward);
    }

  } // namespace Player
} // namespace Gyro
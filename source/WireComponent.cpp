#include "WireComponent.h"
#include "ObjectBase.h"

namespace Gyro {
  namespace Player {

    WireComponent::WireComponent(Object::ObjectBase& owner) : _owner(owner) {
      _type = ComponentType::Wire;
    }

    bool WireComponent::SetTarget(const Vector4& target, const float time) {
      // 移動時間を設定
      _time = time;
      // 所有者の現在座標を開始座標にする
      _start = _owner.GetPosition();
      // 所有者の現在座標とターゲット座標から距離と向きを算出
      _target = target;
      // 向きベクトルを更新する
      _forward = Vector4::Normalize(_start - _owner.GetPosition());
      // 移動量を算出する
      return false;
    }

    Vector4 WireComponent::WireMove() const {
      auto v = (_target - _start) / _time; // 移動量
      return v;
    }

  } // namespace Player
} // namespace Gyro
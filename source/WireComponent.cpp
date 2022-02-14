#include "WireComponent.h"
#include "ObjectBase.h"

namespace Gyro {
  namespace Player {

    WireComponent::WireComponent(Object::ObjectBase& owner) : _owner(owner) {
      _type = ComponentType::Wire;
    }

    void WireComponent::Start() {
      _wire = true;
      // 所有者の重力処理を無効化する
      _owner.GravitySet(false);
    }

    void WireComponent::Finish() {
      _wire = false;
      // 所有者の重力処理を有効にする
      _owner.GravitySet(true);
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

    Vector4 WireComponent::WireMove() {
      // 向き情報の取得
      _forward = Vector4::Normalize(_target - _owner.GetPosition());
      return _forward * 5.0f; // 移動量を返す
    }
  } // namespace Player
} // namespace Gyro
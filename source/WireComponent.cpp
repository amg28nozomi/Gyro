/*****************************************************************//**
 * @file   WireComponent.cpp
 * @brief  ワイヤーアクション機能クラスの定義
 * 
 * @author 鈴木希海
 * @date   April 2022
 *********************************************************************/
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

    bool WireComponent::SetTarget(const Vector4& target, const float speed) {
      // 移動時間を設定
      _speed = speed;
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
      // 向きベクトルが0の場合は処理を行わない
      if (_forward.LengthSquared() == 0.0f) {
        _wire = false;
        return Vector4(); // 向きを返す
      }
      // 向き情報を角度に変換
      return _forward * _speed; // 移動量を返す
    }
  } // namespace Player
} // namespace Gyro
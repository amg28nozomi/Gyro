/*****************************************************************//**
 * @file   MoveComponent.cpp
 * @brief  移動コンポーネントクラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "MoveComponent.h"
#include <appframe.h>
#include "ObjectBase.h"

namespace Gyro {
  namespace Object {

    MoveComponent::MoveComponent(ObjectBase& owner) : _owner(owner) {
      _move = AppMath::Vector4();
      _speed = 5.0f;
    }

    void MoveComponent::OldPosition() {
      // 前フレーム座標の更新
      _oldPosition = _owner.GetPosition();
    }

    bool MoveComponent::Move(const float x, const float z) {
      // 値が0の場合は処理を行わない
      if (AppMath::Arithmetic::LengthSquared(x, z) == 0.0f) {
        return false; // 移動無し
      }
      // 現在の向き
      auto [directionX, directionY, directionZ] = _owner.

      // 移動量の算出
      auto moveX = (x / 30000.0f) * _speed;
      auto moveZ = (z / 30000.0f) * _speed;
      _move = AppMath::Vector4(moveX, 0.0f, moveZ);
      return true;   // 移動有り
    }

    void MoveComponent::Start() {

    }
    
    void MoveComponent::Finish() {
      _move.Zero();
    }
  } // namespace Object
} // namespace Gyro
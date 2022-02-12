#include "MoveComponent.h"
#include <appframe.h>

namespace Gyro {
  namespace Object {

    MoveComponent::Vector4 MoveComponent::Move(const Vector4& move) const {
      // 入力値がない場合はゼロベクトルを返す
      if (move.LengthSquared() == 0.0f) {
        return Vector4();
      }
      //
      auto x = (move.GetX() / 30000.0f) * _speed;
      auto z = (move.GetY() / 30000.0f) * _speed;
      return Vector4(x, 0.0f, z);
    }
  } // namespace Object
} // namespace Gyro
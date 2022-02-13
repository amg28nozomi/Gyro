#include "MoveComponent.h"
#include <appframe.h>

namespace Gyro {
  namespace Object {

    MoveComponent::MoveComponent(ObjectBase& owner) : _owner(owner) {
      _move = AppMath::Vector4();
      _speed = 5.0f;
    }

    AppMath::Vector4 MoveComponent::Move(const AppMath::Vector4& move) {
      // 入力値がない場合はゼロベクトルを返す
      if (move.LengthSquared() == 0.0f) {
        return AppMath::Vector4();
      }
      //
      auto x = (move.GetX() / 30000.0f) * _speed;
      auto z = (move.GetY() / 30000.0f) * _speed;
      _move = AppMath::Vector4(x, 0.0f, z);
      return AppMath::Vector4(x, 0.0f, z);
    }

    void MoveComponent::Start() {

    }
    
    void MoveComponent::Finish() {

    }
  } // namespace Object
} // namespace Gyro
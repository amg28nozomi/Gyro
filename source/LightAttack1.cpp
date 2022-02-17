#include "LightAttack1.h"

namespace Gyro {
  namespace Player {

    LightAttack1::LightAttack1(Object::ObjectBase& owner, std::shared_ptr<Object::CollisionBase> collision) : AttackComponent(owner, std::move(collision)) {
      // 
    }
  } // namespace Player
} // namespace Gyro
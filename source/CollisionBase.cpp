#include "CollisionBase.h"
#include <appframe.h>
#include <DxLib.h>
#include "ObjectBase.h"

namespace Gyro {
  namespace Object {

    CollisionBase::CollisionBase(ObjectBase& owner) : _owner(owner) {
    }

    void CollisionBase::Process() {
      // çXêVèàóù
    }

#ifdef _DEBUG
    void CollisionBase::Draw() {
    }
#endif

  } // namespace Object
} // namespace Gyro
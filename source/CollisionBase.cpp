#include "CollisionBase.h"
#include <appframe.h>
#include "ObjectBase.h"

namespace Gyro {
  namespace Object {

    CollisionBase::CollisionBase(ObjectBase& owner) : _owner(owner) {
    }

    void CollisionBase::Process() {
    }

    void CollisionBase::Process(AppMath::Vector4 vector) {
    }

#ifdef _DEBUG
    void CollisionBase::Draw() {
    }
#endif

    bool CollisionBase::IsHit() {
      return _hit; // 衝突フラグがtrueではない場合、処理を行わない
    }
  } // namespace Object
} // namespace Gyro
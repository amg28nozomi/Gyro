#include "CollisionBase.h"
#include <appframe.h>
#include <DxLib.h>
#include "ObjectBase.h"

namespace Gyro {
  namespace Object {

    CollisionBase::CollisionBase(ObjectBase& owner) : _owner(owner) {
    }

    void CollisionBase::Process() {
      // 更新処理
    }

#ifdef _DEBUG
    void CollisionBase::Draw() {
    }
#endif

    AppMath::Matrix44 CollisionBase::WorldMatrix() const {
      using Matrix4 = AppMath::Matrix44;
      auto world = Matrix4::Identity();
      // ワールド座標行列変換(回転は行わない)
      world.MulScaling(_scale);
      world.MulTranslate(_position);
      return world; // 作成したワールド座標行列を返す
    }
  } // namespace Object
} // namespace Gyro
#include "CollisionBase.h"
#include <appframe.h>
#include <DxLib.h>
#include "ObjectBase.h"

namespace Gyro {
  namespace Object {

    CollisionBase::CollisionBase(ObjectBase& owner) : _owner(owner) {
    }

    void CollisionBase::Process() {
      // �X�V����
    }

#ifdef _DEBUG
    void CollisionBase::Draw() {
    }
#endif

    AppMath::Matrix44 CollisionBase::WorldMatrix() const {
      using Matrix4 = AppMath::Matrix44;
      auto world = Matrix4::Identity();
      // ���[���h���W�s��ϊ�(��]�͍s��Ȃ�)
      world.MulScaling(_scale);
      world.MulTranslate(_position);
      return world; // �쐬�������[���h���W�s���Ԃ�
    }
  } // namespace Object
} // namespace Gyro
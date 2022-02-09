/*****************************************************************//**
 * @file   CollisionBase.cpp
 * @brief  �Փ˔���p���̊��N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "CollisionBase.h"
#include "ObjectBase.h"

namespace Gyro {
  namespace Object {

    CollisionBase::CollisionBase(ObjectBase& owner) : _owner(owner) {
      _position = AppMath::Vector4();
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
      return _hit; // �Փ˃t���O��true�ł͂Ȃ��ꍇ�A�������s��Ȃ�
    }
  } // namespace Object
} // namespace Gyro
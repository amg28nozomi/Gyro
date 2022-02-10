/*****************************************************************//**
 * @file   CollisionOBB.cpp
 * @brief  �L���o�E���f�B���O�{�b�N�X�̏Փ˔���N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "CollisionOBB.h"

namespace Gyro {
  namespace Object {

    CollisionOBB::CollisionOBB(ObjectBase& owner, AppMath::Vector4 position, AppMath::Vector4 rotation, AppMath::Vector4 scale) : CollisionBase(owner) {
      // ��������Ƀ��[���h���W�s����擾
      _matrix = AppMath::Utility::ToWorldMatrix(position, rotation, scale);
      // �t�s����擾
      auto inverse = AppMath::Matrix44::Inverse(_matrix);
    }

    bool CollisionOBB::CheckLineSegment(const AppMath::LineSegment& segment) {
      // �����ɑ΂��ċt�s���K��
      auto pos = _inverse * segment.GetStart();
      auto end = _inverse * segment.GetEnd();
      return false;
    }
  } // namespace Object
} // namespace Gyro
/*****************************************************************//**
 * @file   CollisionCapsule.cpp
 * @brief  
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "CollisionCapsule.h"
#include "CollisionSphere.h"
#include "UtilityDX.h"

namespace Gyro {
  namespace Object {

    CollisionCapsule::CollisionCapsule(ObjectBase& owner, AppMath::Vector4 center, float line, float radius) : CollisionBase(owner) {
      // �e��p�����[�^�̐ݒ�
      _position = center; 
      _length = line;
      // �����̒������s��
      _radius = radius;
    }

    void CollisionCapsule::Process(AppMath::Vector4 move) {
      // �O�t���[���̍��W
      auto old = _position;
      // �V�������W���
      auto newPosition = _position + move;
      // �X�e�[�W�Ƃ̏Փ˔�����s��
    }

#ifdef _DEBUG
    void CollisionCapsule::Draw() {
      // �����̎擾(��[�E�I�[)
      auto [start, end] = Line().GetVector();
      // ����`�悷��
      DrawCapsule3D(UtilityDX::ToVECTOR(start), UtilityDX::ToVECTOR(end), _radius, 10, 0, 0, false);
    }
#endif

    bool CollisionCapsule::IntersectLine(const AppMath::Line& line) {
      // �J�v�Z���Ɛ����̏Փ˔���

    }

    bool CollisionCapsule::IntersectSphere(const CollisionSphere& sphere) {
      // �J�v�Z���Ƌ��̏Փ˔���

    }

    bool CollisionCapsule::IntersectCapsule(const CollisionCapsule& capsule) {
      // �J�v�Z���ƃJ�v�Z���̏Փ˔���

    }

    AppMath::Line CollisionCapsule::Line() const {
      auto line = _length / 2;
      // ��������������Ԃ�
      return AppMath::Line(_position.AddVectorY(line), _position.AddVectorY(-line));
    }
  } // namespace Object
} // namespace Gyro
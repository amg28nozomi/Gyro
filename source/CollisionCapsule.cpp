/*****************************************************************//**
 * @file   CollisionCapsule.cpp
 * @brief  
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "CollisionCapsule.h"
#include <appframe.h>
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
      _position = newPosition;
      // �X�e�[�W�Ƃ̏Փ˔�����s��
    }

#ifdef _DEBUG
    void CollisionCapsule::Draw() {
      // �����̎擾(��[�E�I�[)
      auto [start, end] = LineSegment().GetVector();
      // �w����W�ɃJ�v�Z����`�悷��
      DrawCapsule3D(UtilityDX::ToVECTOR(start), UtilityDX::ToVECTOR(end), _radius, 10, 0, 0, false);
    }
#endif

    bool CollisionCapsule::IntersectLine(const AppMath::LineSegment& line) {
      // �J�v�Z���Ɛ����̏Փ˔���
      return true;
    }

    bool CollisionCapsule::IntersectSphere(const CollisionSphere& sphere) {
      // �J�v�Z���Ƌ��̏Փ˔���
      return true;
    }

    bool CollisionCapsule::IntersectCapsule(const CollisionCapsule& capsule) {
      return false;
      //float distSq = LineSegment().MinDistSq(capsule.LineSegment());
      //auto sumRadius = _radius + capsule._radius;
      //return distSq <= (sumRadius * sumRadius);
    }

    bool CollisionCapsule::IntersectPlane(const AppFrame::Math::Plane& plane) {
      // �����ƕ��ʂ͏Փ˂��Ă��邩
      if (LineSegment().IntersectPlane(plane)) {
        return true; // �Փ˂��Ă���
      }
      return false;
    }

    AppMath::LineSegment CollisionCapsule::LineSegment() const {
      auto line = _length / 2;
      // ��������������Ԃ�
      return AppMath::LineSegment(_position.AddVectorY(line), _position.AddVectorY(-line));
    }
  } // namespace Object
} // namespace Gyro
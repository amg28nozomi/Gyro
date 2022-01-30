/*****************************************************************//**
 * @file   CollisionSphere.cpp
 * @brief  �R���W�����x�[�X�̃T�u�N���X
 *         ���̓����蔻��N���X�̒�`
 * 
 * @date   January 2022
 *********************************************************************/
#include "CollisionSphere.h"
#include "ObjectBase.h"
#include "UtilityDX.h"

namespace Gyro {
  namespace Object {

    CollisionSphere::CollisionSphere(ObjectBase& owner, AppMath::Vector4 center, float radius) : CollisionBase(owner), _radius(radius) {
      _position = center;
      _type = CollisionType::Sphere; // �R���W�����^�C�v�����ɐݒ�
    }

    void CollisionSphere::Process() {
#ifdef _DEBUG
      _collision = false;
#endif
      // �X�V�������s��
      auto old = _position;
      // ���L�҂̍��W���擾
      _position = _owner.GetPosition();
    }

    void CollisionSphere::Process(AppMath::Vector4 vector) {
#ifdef _DEBUG
      _collision = false;
#endif
      // �O�t���[�����W
      auto old = _position;
      // �ړ����W
      auto newPosition = _position + vector;
      // ���S���W�Ɉړ��ʂ����Z����
      _position.Add(vector);
    }

#ifdef _DEBUG
    void CollisionSphere::Draw() {
      // �f�o�b�O�t���O�������Ă���ꍇ�̂ݕ`����s��
      if (!_debug) { return; }
      using AppColor = AppFrame::Data::Color;
      // ����`�悷��(�Փ˂��Ă���ꍇ�͋���h��ׂ�)
      DrawSphere3D(UtilityDX::ToVECTOR(_position), _radius, 10, AppColor::GetColor(0, 0, 0), 0, _collision);
    }
#endif

    bool CollisionSphere::IsHit() {
      // �������
      return false;
    }

    bool CollisionSphere::IntersectSphere(const CollisionSphere& sphere) {
      // ���Ƌ��̏Փ˔���
      auto distSq = AppMath::Vector4::LengthSquared(_position - sphere._position);
      auto sumRadius = _radius + sphere._radius;
      return distSq <= (sumRadius * sumRadius);
    }

    bool CollisionSphere::IntersectPoint(const AppMath::Vector4& point) {
      // ���Ɠ_�̏Փ˔���
      auto l = AppMath::Vector4::LengthSquared(_position - point);
      auto radius2 = _radius * _radius;
      return l <= radius2;
    }
  } // namespace Object
} // namespace Gyro
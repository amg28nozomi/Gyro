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
#ifdef _DEBUG
      using Color = AppFrame::Data::Color;
      _color = Color::GetColor(0, 0, 0); // �J���[�R�[�h�̎擾
#endif
    }

    void CollisionSphere::Process() {
#ifdef _DEBUG
      _collision = false;
#endif
      //  // �X�V�������s��
      //  auto old = _position;
      //  // ���L�҂̍��W���擾
      //  _position = _owner.GetPosition();
      //}
    }

    void CollisionSphere::Process(AppMath::Vector4 vector) {
#ifdef _DEBUG
      _collision = false; // �Փ˃t���O��������
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
      using AppColor = AppFrame::Data::Color;
      // ����`�悷��(�Փ˂��Ă���ꍇ�͋���h��ׂ�)
      DrawSphere3D(UtilityDX::ToVECTOR(_position), _radius, 10, AppColor::GetColor(0, 0, 0), 0, _collision);

      auto [x, y, z] = _position.GetVector3();
      DrawFormatString(1000, 0, 125, "�� x:%f y:%f, z:%f", x, y, z);
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
#ifndef _DEBUG
      return distSq <= (sumRadius * sumRadius);
#else
      _collision = distSq <= (sumRadius * sumRadius);
      return _collision;
#endif
    }

    bool CollisionSphere::IntersectPoint(const AppMath::Vector4& point) {
      // ���Ɠ_�̏Փ˔���
      auto l = AppMath::Vector4::LengthSquared(_position - point);
      auto radius2 = _radius * _radius;
#ifndef _DEBUG
      return l <= radius2;
#else
      _collision = l <= radius2;
      return _collision;
#endif
    }
  } // namespace Object
} // namespace Gyro
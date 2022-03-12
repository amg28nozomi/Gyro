/*****************************************************************//**
 * @file   CollisionAABB.cpp
 * @brief  �����s�o�E���f�B���O�{�b�N�X�̏Փ˔���N���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "CollisionAABB.h"
#include "CollisionSphere.h"

namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {

    CollisionAABB::CollisionAABB(ObjectBase& owner, const AppMath::Vector4& min, const AppMath::Vector4& max) : CollisionBase(owner) {
      _position = min; // �ŏ��_
      _max = max;      // �ő�_
    }

    void CollisionAABB::Process(const AppMath::Vector4& point) {
      // �_���W�x�N�g���𕪉�
      const auto [x, y, z, w] = point.GetVector4();
      // Utility�ɕʖ���`
      using Utility = AppMath::Utility;
      // �e�������ɍX�V���s��
      _position.SetX(Utility::Min(_position.GetX(), x));
      _position.SetY(Utility::Min(_position.GetY(), y));
      _position.SetZ(Utility::Min(_position.GetZ(), z));
      _max.SetX(Utility::Max(_max.GetX(), x));
      _max.SetY(Utility::Max(_max.GetY(), y));
      _max.SetZ(Utility::Max(_max.GetZ(), z));
    }

    bool CollisionAABB::CheckPoint(const AppMath::Vector4& point) {
      auto side = point.GetX() < _position.GetX() ||
        point.GetY() < _position.GetY() ||
        point.GetZ() < _position.GetZ() ||
        _max.GetX() < point.GetX() ||
        _max.GetY() < point.GetY() ||
        _max.GetZ() < point.GetZ();
      return !side;
    }

    bool CollisionAABB::CheckLineSegment(const AppMath::LineSegment& segment) {
      // �����x�N�g�����擾
      auto v = segment.Segment();
      using Vector4 = AppMath::Vector4;
      // �x�N�g���̒������Ȃ�
      if (Vector4::NearZero(v)) {
        return false;
      }



      return false;
    }

    bool CollisionAABB::CheckSphere(const CollisionSphere& sphere) {
      // ���S���W�̎擾
      auto [x, y, z] = sphere.GetPosition().GetVector3();
      // �ʖ���`
      using Utility = AppMath::Utility;
      using Vector4 = AppMath::Vector4;
      // �ŒZ�����̎Z�o
      auto directionX = Utility::Max(_position.GetX() - x, 0.0f);
      directionX = Utility::Max(directionX, x - _max.GetX());
      auto directionY = Utility::Max(_position.GetY() - y, 0.0f);
      directionY = Utility::Max(directionY, y - _max.GetY());
      auto directionZ = Utility::Max(_position.GetZ() - z, 0.0f);
      directionZ = Utility::Max(directionZ, z - _max.GetZ());
      // �����̓����Z�o
      auto distSq = Vector4::LengthSquared(Vector4(directionX, directionY, directionZ));
      // 
      return distSq <= sphere.RadiusSquared();
    }
  } // namespace Object
} // namespace Gyro
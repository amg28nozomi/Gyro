/*****************************************************************//**
 * @file   MoveComponent.cpp
 * @brief  �ړ��R���|�[�l���g�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "MoveComponent.h"
#include <appframe.h>
#include "ObjectBase.h"

namespace Gyro {
  namespace Object {

    MoveComponent::MoveComponent(ObjectBase& owner) : _owner(owner) {
      _move = AppMath::Vector4();
      _speed = 5.0f;
    }

    void MoveComponent::OldPosition() {
      // �O�t���[�����W�̍X�V
      _oldPosition = _owner.GetPosition();
    }

    bool MoveComponent::Move(const float x, const float z) {
      // �l��0�̏ꍇ�͏������s��Ȃ�
      if (AppMath::Arithmetic::LengthSquared(x, z) == 0.0f) {
        return false; // �ړ�����
      }
      // ���݂̌���
      auto [directionX, directionY, directionZ] = _owner.

      // �ړ��ʂ̎Z�o
      auto moveX = (x / 30000.0f) * _speed;
      auto moveZ = (z / 30000.0f) * _speed;
      _move = AppMath::Vector4(moveX, 0.0f, moveZ);
      return true;   // �ړ��L��
    }

    void MoveComponent::Start() {

    }
    
    void MoveComponent::Finish() {
      _move.Zero();
    }
  } // namespace Object
} // namespace Gyro
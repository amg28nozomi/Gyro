/*****************************************************************//**
 * @file   MoveComponent.cpp
 * @brief  �ړ��R���|�[�l���g�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "MoveComponent.h"
#include <appframe.h>
#include "ApplicationMain.h"
#include "Camera.h"
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
      // �ړ��ʂ��Ȃ��ꍇ�͏������s��Ȃ�
      if (AppMath::Arithmetic::LengthSquared(x, z) == 0.0f) {
        _move.Zero(); // �ړ��ʏ�����
        return false; // �ړ�����
      }
      // �J�����̎擾
      const auto& camera = _owner.GetApplicaton().GetCamera();
      // �J�������̎擾
      const auto cameraPos = camera.GetPosition();
      const auto cameraTarget = camera.GetTarget();
      // �ʖ���`
      using Vector4 = AppMath::Vector4;

      auto cameraZ = Vector4::Normalize(cameraTarget - cameraPos);
      auto cameraX = Vector4::Cross(cameraZ.Up(), cameraZ);
      cameraX = Vector4::Normalize(cameraX);
      // �J������������Ɉړ��ʂ��Z�o����
      auto length = _owner.GetPosition().Direction(cameraPos);
      // ���K��
      length.Normalize();

      // ���L�҂̌����x�N�g�����擾
      const auto [forwardX, forwardY, forwardZ] = _owner.GetForward().GetVector3();
      // �ړ��ʂ̎Z�o
      auto speedX = (x / 30000.0f) * _speed;
      auto speedZ = ((z / 30000.0f) * _speed * length.GetZ()) * -1.0f;
      _move = Vector4(speedX, 0.0f, speedZ);
      return true;   // �ړ��L��
    }

    void MoveComponent::Start() {

    }
    
    void MoveComponent::Finish() {
      _move.Zero();
    }
  } // namespace Object
} // namespace Gyro
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
      _speed = 10.0f;
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
      // �J���������̎擾
      // auto cameraForward = Vector4::Normalize(cameraPos.Direction(cameraTarget));
      auto cameraForward = cameraPos.Direction(_owner.GetPosition());
      cameraForward = Vector4::Normalize(Vector4::Scale(cameraForward, Vector4(1.0f, 0.0f, 1.0f)));
      // �f�b�h�]�[���̎擾
      const auto xState= _owner.GetApplicaton().GetOperation().GetXBoxState();
      auto deadZone = xState.GetDeadZone();
      // �ړ�����
      auto inputX = (x / static_cast<float>(deadZone.first));
      auto inputZ = (z / static_cast<float>(deadZone.second));
      // auto moveForward = Vector4::Normalize(Vector4::Scale(cameraForward ,Vector4(x / 30000.0f, 0.0f, z / 30000.0f)));
      auto moveForward = Vector4::Normalize(Vector4::Scale(cameraForward, Vector4(inputX , 0.0f, inputZ)));
      // �ړ��ʂ̎Z�o
      //auto speedX = (x / 30000.0f) * _speed;
      //auto speedZ = (z / 30000.0f) * _speed; // * /* length.GetZ()) * */ -1.0f
      _move = moveForward * _speed;
      // _move = Vector4::Scale(move, moveForward);
      // Y���W�̏��͖�������
      _move.SetY(0.0f);
      return true;   // �ړ��L��
    }

    void MoveComponent::Start() {

    }
    
    void MoveComponent::Finish() {
      _move.Zero();
    }
  } // namespace Object
} // namespace Gyro
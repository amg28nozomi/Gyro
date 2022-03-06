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
      _speed = 8.0f;
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
      // ���L�҂̍��W
      const auto target = _owner.GetPosition();
      // ��̃x�N�g���̂Ȃ��p�����߂�
      auto cos = Vector4::Dot(cameraPos, target) / (Vector4::Length(cameraPos) * Vector4::Length(target));
      // ���W�A���ŎZ�o
      auto f = std::acos(cos);
      // �J���������̎擾
      // auto cameraForward = cameraPos.Direction(_owner.GetPosition());
      // �J���������̎擾(y���͖�������)
      // cameraForward = Vector4::Normalize(Vector4::Scale(cameraForward, Vector4(1.0f, 0.0f, 1.0f)));

      // �f�b�h�]�[���̎擾
      const auto xState = _owner.GetApplicaton().GetOperation().GetXBoxState();
      auto deadZone = static_cast<float>(xState.GetDeadZoneMax());
      // �ړ�����
      auto inputX = (x / deadZone);
      auto inputZ = (z / deadZone);
      // auto moveForward = Vector4::Normalize(Vector4::Scale(cameraForward ,Vector4(x / 30000.0f, 0.0f, z / 30000.0f)));
      _move = Vector4(inputX * _speed, 0.0f, inputZ * _speed) * f;
      //// �f�b�h�]�[���̎擾
      //const auto xState= _owner.GetApplicaton().GetOperation().GetXBoxState();
      //auto deadZone = static_cast<float>(xState.GetDeadZoneMax());
      //// �ړ�����
      //auto inputX = (x / deadZone);
      //auto inputZ = (z / deadZone);
      //// auto moveForward = Vector4::Normalize(Vector4::Scale(cameraForward ,Vector4(x / 30000.0f, 0.0f, z / 30000.0f)));
      //auto moveForward = Vector4::Normalize(Vector4::Scale(cameraForward, Vector4(inputX , 0.0f, inputZ)));
      // �ړ��ʂ̎Z�o
      // _move = moveForward * _speed;
      // _move = Vector4::Scale(move, moveForward);
      // Y���W�̏��͖�������
      // _move.SetY(0.0f);
      return true;   // �ړ��L��
    }

    void MoveComponent::Start() {

    }
    
    void MoveComponent::Finish() {
      _move.Zero();
    }
  } // namespace Object
} // namespace Gyro
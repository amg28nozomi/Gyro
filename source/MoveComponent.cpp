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
      const auto position = camera.GetPosition();
      const auto target = camera.GetTarget();
      // �ʖ���`
      using Vector4 = AppMath::Vector4;
      // �f�b�h�]�[���̎擾
      const auto xState = _owner.GetApplicaton().GetOperation().GetXBoxState();
      auto deadZone = static_cast<float>(xState.GetDeadZoneMax());
      // �ړ�����
      auto inputX = (x / deadZone);
      auto inputZ = (z / deadZone);
      // �ړ���
      auto move = Vector4(inputX * _speed, 0.0f, inputZ * _speed);
      // �s��̕ʖ���`
      using Matrix44 = AppMath::Matrix44;
      // ���s�ړ��s��
      auto translate = Matrix44::Translate(move);

      // ���W�A���𐶐�(z���͔��]������)
      auto radian = std::atan2(move.GetX(), -move.GetZ());
#ifndef _DEBUG
      _owner.SetRotation(Vector4(0.0f, radian, 0.0f));
#else
      // �f�O���[�l���Z�b�g����(�f�o�b�O�p)
      _owner.SetRotation(Vector4(0.0f, AppMath::Utility::RadianToDegree(radian), 0.0f));
#endif
      // ��]�����s�ړ�
      auto moveMatrix = translate * Matrix44::ToRotationY(radian);
      // auto moveMatrix = Matrix44::ToRotationY(radian) * translate;
      auto v = Vector4(1.0f, 1.0f, -1.0f);
      _move = moveMatrix * v;
      // �^�[�Q�b�g���W�܂ł̌������Z�o
      //auto direction = position.Direction(target);
      //// �����x�N�g���̊e�������擾
      //auto [dX, dY, dZ] = direction.GetVector3();
      //// �J�����̉�]�s��
      //auto cameraRotateY = Matrix44::ToRotationY(atan2(dZ, dX));
      //// �J�����̕��s�ړ��s��
      //auto cameraTranslate = Matrix44::Translate(position);
      //// �J�����̃��[���h���W�s��
      //auto cameraWorld = cameraTranslate * cameraRotateY;
      //// �t�s��ɕϊ�
      //auto inverseWorld = Matrix44::Inverse(cameraWorld);
      //// ���݂̌�����

      //// ���W�A���𐶐�(z���͔��]������)
      //auto pRad = std::atan2(move.GetX(), -move.GetZ());
      //// ��]�s����r���[�s��
      //auto moveRad =  inverseWorld * Matrix44::ToRotationY(pRad);
      //// �ȏ�I
      //auto mPower = moveRad * translate;
      //_move = mPower * Vector4(1.0f, 0.0f, 1.0f);

      // �J���������̎擾
      // auto cameraForward = cameraPos.Direction(_owner.GetPosition());
      // �J���������̎擾(y���͖�������)
      // cameraForward = Vector4::Normalize(Vector4::Scale(cameraForward, Vector4(1.0f, 0.0f, 1.0f)));
      // auto moveForward = Vector4::Normalize(Vector4::Scale(cameraForward ,Vector4(x / 30000.0f, 0.0f, z / 30000.0f)));
      //_move = Vector4(inputX * _speed, 0.0f, inputZ * _speed) * f;
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
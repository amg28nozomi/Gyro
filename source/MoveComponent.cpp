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
      // �ړ���(-1~ 1)
      // auto normal = Vector4(inputX, 0.0f, inputZ);

      // auto thisDirection = Vector4::Cross(_owner.GetPosition(), normal);

      //// �J��������^�[�Q�b�g�ւ̌����x�N�g�����擾
      //auto direction = position.Direction(target);
      //// �J��������^�[�Q�b�g�ւ̌��������߂�
      //auto cameraCross = Vector4::Cross(position, direction);

      ////
      //auto angle = std::acos(thisDirection.Dot(cameraCross) / (thisDirection.Length() * cameraCross.Length()));
      //// �f�O���[�l�ɕϊ�
      //auto degree = AppMath::Utility::RadianToDegree(angle);

      // �s��̕ʖ���`
      using Matrix44 = AppMath::Matrix44;

      // ���W�A���𐶐�(z���͔��]������)
      auto radian = std::atan2(-move.GetZ(), move.GetX());
      auto l = Vector4::Normalize(position.Direction(target));
      radian += std::atan2(l.GetZ(), l.GetX());
#ifndef _DEBUG
      _owner.SetRotation(Vector4(0.0f, radian, 0.0f));
#else
      // �f�O���[�l���Z�b�g����(�f�o�b�O�p)
      _owner.SetRotation(Vector4(0.0f, AppMath::Utility::RadianToDegree(radian), 0.0f));
#endif

      // ��]�����s�ړ�
      auto moveMatrix = /*translate **/ Matrix44::ToRotationY(radian);
      auto v = Vector4(0.0f, 0.0f, 8.0f);
      _move = moveMatrix * v;
      return true;   // �ړ��L��
    }

    void MoveComponent::Start() {

    }
    
    void MoveComponent::Finish() {
      _move.Zero();
    }
  } // namespace Object
} // namespace Gyro
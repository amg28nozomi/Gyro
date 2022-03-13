/*****************************************************************//**
 * @file   DashComponent.cpp
 * @brief  �_�b�V���R���|�[�l���g�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   March 2022
 *********************************************************************/
#include "DashComponent.h"
#include "ObjectBase.h"

namespace Gyro {
  namespace Object {

    DashComponent::DashComponent(ObjectBase& owner) : ObjectComponent(), _owner(owner) {
      // �^�C�v�̐ݒ�
      _type = ComponentType::Dash;
    }

    void DashComponent::Init() {
      // ����������
      _dashState = DashState::NoActive;

    }

    void DashComponent::Start() {
      // �_�b�V���N��
      _dashState = DashState::Active;
    }

    void DashComponent::Finish() {
      // �_�b�V����Ԃ��I��
      _dashState = DashState::Interval;
      _count = 0;
      _dashEnd = true;
    }

    bool DashComponent::Process() {
      // �_�b�V����Ԃ��̔���
      if (!IsDash()) {
        // �C���^�[�o�������H
        Interval();
        return false;
      }
      // �ҋ@�J�ڔ���
      if (_count == 30) {
        // �C���^�[�o����ԂɑJ�ڂ���
        _dashState = DashState::Interval;
        _count = 0;
        return true;
      }
      // �J�E���g�ł̏I������
      ++_count;
      return true;
    }

    bool DashComponent::Interval() {
      // �C���^�[�o�����łȂ��ꍇ�͏������s��Ȃ�
      if (!IsInterval()) {
        return false;
      }
      // �C���^�[�o�����I���������̔���
      if (_intervalTime <= 0.0f) {
        _dashState = DashState::NoActive;
        _intervalTime = 0.0f;
        return true;
      }
      _intervalTime -= 10.0f; // �C���^�[�o���^�C�����o�߂�����
      return true;
    }

    void DashComponent::SetDash(const AppMath::Vector4& direction, float power, float totalTime) {
      // �Đ����̏ꍇ�̓Z�b�g���s��Ȃ�
      if (totalTime <= 0.0f) {
        return;
      }
      // �ړ����x�̐ݒ�
      auto speed = 10.0f;
      using Vector4 = AppMath::Vector4;
      // ���@�̌����x�N�g��
      auto forward = _owner.GetForward();

      _move = Vector4(speed * forward.GetX(), 0.0f, speed * forward.GetZ());
      // �P�ʃx�N�g����
      auto normal = AppMath::Vector4::Normalize(_move);
      // ���W�A���𐶐�(z���͔��]������)
      auto radian = std::atan2f(normal.GetX(), !normal.GetZ());
#ifndef _DEBUG
      _owner.SetRotation(AppMath::Vector4(0.0f, radian, 0.0f));
#else
      // �f�O���[�l���Z�b�g����(�f�o�b�O�p)
      _owner.SetRotation(AppMath::Vector4(0.0f, AppMath::Utility::RadianToDegree(radian), 0.0f));
#endif
      // �ړ��ʂ�ݒ肷��
      // _move = Vector4::Scale(_direction, Vector4(speed, 0.0f, speed));
      _power = power;
    }

    void DashComponent::SetIniterval(const float interval) {
      // ���Ԃ�ݒ肷��
      _intervalTime = interval;
      _dashState = DashState::Interval;
    }
  } // namespace Object
} // namespace Gyro
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
      // 
      _dashState = DashState::Active;
    }

    void DashComponent::Finish() {
      // �_�b�V����Ԃ��I��
      _dashState = DashState::NoActive;
    }

    bool DashComponent::Process(AppMath::Vector4& move) {
      // �_�b�V����Ԃ��̔���
      if (!IsDash()) {
        // �C���^�[�o�������H
        Interval();
        return false;
      }
      // �����x�N�g���̎擾
      auto forward = _owner.GetForward();
      // �͂��Z�o
      auto power = _power / _count;
      // �ʖ���`
      using Vector4 = AppMath::Vector4;
      // y�����𖳎����Čv�Z���s��
      auto m = Vector4::Scale(forward, Vector4(1.0f, 0.0f, 1.0f));
      // �����Ă�������ɐi�܂���
      _move = m * power;
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

    void DashComponent::SetDash(const float dashPower, float totalTime, float playSpeed) {
      if (totalTime <= 0.0f) {
        return;
      }
      // �ړ��͂̐ݒ�
      _power = dashPower;
      // �����񐔂̐ݒ�
      _count = static_cast<int>(totalTime / playSpeed);
    }

    void DashComponent::SetIniterval(const float interval) {
      // ���Ԃ�ݒ肷��
      _intervalTime = interval;
      _dashState = DashState::Interval;
    }
  } // namespace Object
} // namespace Gyro
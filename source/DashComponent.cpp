/*****************************************************************//**
 * @file   DashComponent.cpp
 * @brief  �_�b�V���R���|�[�l���g�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   March 2022
 *********************************************************************/
#include "DashComponent.h"

namespace Gyro {
  namespace Object {

    DashComponent::DashComponent() : ObjectComponent() {
      // �^�C�v�̐ݒ�
      _type = ComponentType::Jump;
    }

    void DashComponent::Init() {

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
      if (_dashState != DashState::Active) {
        // �C���^�[�o�������H
        if (IsInterval()) {
          Interval();
        }
        return false;
      }
      // �ړ��ʂ�ݒ肷��
      move = _move;
      return true;
    }

    void DashComponent::Interval() {
      // �C���^�[�o�����I���������̔���
      if (_time <= 0.0f) {
        _dashState = DashState::NoActive;
        _time = 0.0f;
        return;
      }
      _time -= 10.0f; // �C���^�[�o���^�C�����o�߂�����
    }

    void DashComponent::SetMove(const AppMath::Vector4& move, float time) {
      if (time <= 0.0f) {
        return;
      }
      // �ݒ�
      _length = move;
      _move = move / time;
    }

    void DashComponent::SetIniterval(const float interval) {
      // ���Ԃ�ݒ肷��
      _time = interval;
      _dashState = DashState::Interval;
    }
  } // namespace Object
} // namespace Gyro
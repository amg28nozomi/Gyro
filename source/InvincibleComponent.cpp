/*****************************************************************//**
 * @file   InvincibleComponent.cpp
 * @brief  ���G�����p�̃R���|�[�l���g�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "InvincibleComponent.h"
#include "ApplicationMain.h"

namespace Gyro {
  namespace Object {

    InvincibleComponent::InvincibleComponent(Application::ApplicationMain& app) : _app(app) {
      // ���G����
      _type = ComponentType::Invincible;
      _limit = 60;
      _time = 0;
      _infinity = false;
    }

    void InvincibleComponent::Init() {
      // �e��p�����[�^�̏�����
      _time = 0;
      _infinity = false;
    }

    void InvincibleComponent::Start() {
      Init(); // ������
      // ���G��ԂɑJ��
      _invincible = InvincibleState::Invincible;
    }

    void InvincibleComponent::Finish() {
      // �ʏ��ԂɑJ��
      _invincible = InvincibleState::Normal;
      Init();
    }

    void InvincibleComponent::InvincibleStart() {
      // ���G��ԂɑJ��
      _invincible = InvincibleState::Invincible;
      _infinity = true;
    }

    void InvincibleComponent::Process(const int speed) {
      // ���G���Ԃ��I������
      if (TimeEnd(speed)) {
        Finish(); // �I��
      }
    }

    bool InvincibleComponent::TimeEnd(const int speed) {
      // �������t���O�������Ă��邩
      if (_infinity) {
        return false;
      }
      _time += speed; // �^�C���ɉ����x�����Z����
      // �o�ߎ��Ԃ͏���𒴉߂�����
      return _limit <= _time;
    }

  } // namespace Object
} // namespace Gyro
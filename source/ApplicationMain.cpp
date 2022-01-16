/*****************************************************************//**
 * @file   ApplicationMain.cpp
 * @brief  �A�v���P�[�V�����x�[�X�̃T�u�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "ApplicationMain.h"
#include "appframe.h"
#include <DxLib.h>

namespace Gyro {
  namespace Application {
    // �A�v���P�[�V�����̎���
    ApplicationMain application;
    
    ApplicationMain::ApplicationMain() : ApplicationBase() {
      // ���̂̓o�^���s����
      if (SetInstance()) {
        // ���̍쐬
        _instance = std::make_shared<ApplicationMain>();
      }
    }

    bool ApplicationMain::Init() {
      if (!ApplicationBase::Init()) {
        return false; // ���������s
      }
      return true;
    }

    bool ApplicationMain::Input() {
      auto flag = ApplicationBase::Input();
      // ���͏�Ԃ̎擾
      auto state = _input->GetJoypadState();

      if (1 < state.GetKey()) {
        return true;
      }

      // �Q�[���I��
      if (state.GetKey() & PAD_INPUT_1) {
        _state = State::Quit;
        return true;
      }
      return flag;
    }

    bool ApplicationMain::Process() {
      return ApplicationBase::Process();
    }
  } // namespace Application
} // namespace Gyro
/*****************************************************************//**
 * @file   JoypadState.cpp
 * @brief  �W���C�p�b�h�̓��͏�ԃN���X
 *
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "JoypadState.h"

/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {

    JoypadState::JoypadState() : InputBase() {
    }

    void JoypadState::Process() {
      // �Ώۃf�o�C�X�͓��͂��󂯕t���Ă��邩
      if (_state != State::Active) {
        return; // ���͏������s��Ȃ�
      }
      auto old = _press;
      // ���͏�Ԃ̍X�V
      _press = GetJoypadInputState(DX_INPUT_PAD1);
      // ���͏�Ԃ̍X�V�͐���������
      if (_press == -1) {
        _state = State::NonActive;
        return; // �X�V���s
      }
      GetJoypadAnalogInput(&_stickX, &_stickY, DX_INPUT_PAD1);
      // �g���K���̎Z�o
      _trigger = _press ^ old & _press;
    }
  } // namespace Application
} // namespace AppFrame
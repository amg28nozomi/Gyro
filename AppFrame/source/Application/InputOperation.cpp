/*****************************************************************//**
 * @file   InputOperation.cpp
 * @brief  ���͏����N���X�̒�`
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#include "InputOperation.h"
#include <array>
#include <DxLib.h>
#include "ApplicationBase.h"
#include "XBoxState.h"

namespace {
  constexpr auto PadMax = 4;   // �W���C�p�b�h�̐ڑ������
  constexpr auto MouseMax = 1; // �}�E�X�̐ڑ������
  constexpr auto Count120 = 120;
} // namespace

namespace AppFrame {
  namespace Application {
    // �W���C�p�b�h
    std::array<int, 4> JoypadType = {
      DX_INPUT_PAD1, // �W���C�p�b�h1
      DX_INPUT_PAD2, // �W���C�p�b�h2
      DX_INPUT_PAD3, // �W���C�p�b�h3
      DX_INPUT_PAD4  // �W���C�p�b�h4
    };

    InputOperation::InputOperation(ApplicationBase& app) : _app(app), _xBox() {
      _state = State::Active;
    }

    InputOperation::~InputOperation() {
    }

    void InputOperation::Process() {
      // ��Ԃɉ����Ă������̎��s
      switch (_state) {
      case State::Active:
        //// �ڑ�����
        //if (GetJoypadNum() == 0) {
        //  _state = State::NonActive;
        //  return; // �ڑ��Ȃ�
        //}
        // ���̓f�o�C�X�̍X�V
        _xBox.Process();
      case State::Paused:
        return; // ���s�Ȃ�
      case State::NonActive:
        // �Đڑ��͊����������H
        if (GetJoypadNum() != 0) {
          // �Đڑ�����
          _state = State::Active;
          return;
        }
        //// �w��t���[���Ɉ�x�A�Đݒ�����݂�
        //if (_app.GetFrameCount() % Count120 == 0) {
        //  ReSetupJoypad();
        //}
        return;
      }
    }

    bool InputOperation::AddJoypad() {
      GetJoypadNum();
      // �ǉ����ꂽ�ꍇ
      return false;
    }

    const bool InputOperation::IsConnection() {
      // �W���C�p�b�h�͐ڑ�����Ă��邩
      if (GetJoypadNum == 0) {
        // �ڑ���Ԃ̏ꍇ�͔�ڑ���ԂɈڍs
        if (_state == State::Active) {
          _state = State::NonActive;
        }
        return false; // �ڑ��Ȃ�
      }
      return true;    // �ڑ�����
    }

    int InputOperation::ToNumber(std::string_view key) const {
      // �Ώۂ̃L�[��ϊ�����
      return 0;
    }
  } // namespace Application
} // namespace AppFrame
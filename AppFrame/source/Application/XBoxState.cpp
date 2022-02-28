/*****************************************************************//**
 * @file   XBoxState.cpp
 * @brief  Xbox�R���g���[���[�̓��͏�ԃN���X�̒�`
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#include "XBoxState.h"
#include <algorithm>
#include <cmath>
#include <string>
#ifdef _DEBUG
#include <stdexcept>
#endif
#include "../Math/Arithmetic.h"
#include "../Math/Vector4.h"

namespace AppFrame {
  namespace Application {
    constexpr auto JoypadLeftStick = false; // ���X�e�B�b�N
    constexpr auto JoypadRightStick = true; // �E�X�e�B�b�N

    constexpr auto Front = 0; // DeadZoneTable�̐�[
    constexpr auto End = 1;   // DeadZoneTable�̖���

    constexpr short DeadZoneZero = 0;    // �f�b�h�]�[��
    constexpr short DeadZoneMax = 30000; //
    constexpr short DefaultDeadZoneMin = 3000;
    constexpr short DefaultDeadZoneMax = 30000;

    XBoxState::XBoxState() : InputBase() {
      _press = XINPUT_STATE();
      _triggerButtons.fill(false);
      _type = DeviceType::Joypad;
      // �f�b�h�]�[�����f�t�H���g�̒l�ŃZ�b�g����
      _deadZone = std::make_pair(DefaultDeadZoneMin, DefaultDeadZoneMax);
    }

    void XBoxState::Process() {
      auto old = _press; // �O�t���[���̃{�^�����͏��
      // ���͏�Ԃ̎擾�ɐ���������
      if (GetJoypadXInputState(DX_INPUT_PAD1, &_press) == Error) {
        // ���s�����ꍇ�͖��ڑ���ԂɑJ��
        _state = State::NonActive;
#ifdef _DEBUG
        throw std::logic_error("����ID���L���ł͂���܂���\n");
#endif
        return; // �擾���s
      }
      // �A�i���O�X�e�B�b�N��p�̍X�V
      AnalogStickUpdate();
      // �{�^���̂݃g���K�����X�V����
      for (auto no = 0; auto && button : _triggerButtons) {
        // ���͏�Ԃ��r���ăg���K�����Z�o����
        button = Trigger(_press.Buttons[no], old.Buttons[no]);
        ++no;
      }
    }

    void XBoxState::DeadZone(short& param) {
      // �����ǂ��炩�̔���
      short p = (Math::Arithmetic::IsPositive(param)) ? 1 : -1;
      short min = _deadZone.first * p;  // ���͉���
      short max = _deadZone.second * p; // ���͏��
      // �Ώۂ��������ɉ�����
      if (p == 1) {
        // ���������������ꍇ��0�Ƃ��Ĉ���
        if (param < min) {
          param = 0;
          return;
        }
        // ����ȊO�̏ꍇ�̓N�����v����
        param = std::clamp(param, min, max);
        return;
      }
      // �Ώۂ��������A���������傫���ꍇ0�Ƃ��Ĉ���
      if (min < param) {
        param = 0;
      }
      // �����𖞂����Ă���ꍇ�̓N�����v����
      param = std::clamp(param, max, min);
      return;
    }

    void XBoxState::AnalogStickUpdate() {
      // �e��X�e�B�b�N���Ƀf�b�h�]�[���������s��
      DeadZone(_press.ThumbLX);
      DeadZone(_press.ThumbLY);
      DeadZone(_press.ThumbRX);
      DeadZone(_press.ThumbRY);
    }

    bool XBoxState::SetDeadZone(const float min, const float max) {
      using Utility = Math::Arithmetic;
      // ����p�e�[�u���̍쐬
      std::array<short, 2> deadZoneTable = { std::move(static_cast<short>(min)), std::move(static_cast<short>(max)) };
      for (auto param : deadZoneTable) {
        // �����͔͈͓��Ɏ��܂��Ă��邩
        if (!Utility::IsRange(param, DefaultDeadZoneMin, DeadZoneMax)) {
#ifndef _DEBUG
          return false; // �������s��
#else
          // �������s���ȏꍇ�͗�O�𓊂���
          throw std::logic_error("SetDeadZone:�������s���ł�\n");
#endif
        }
      }
      // �f�b�h�]�[�����X�V����
      _deadZone = { deadZoneTable[Front], deadZoneTable[End] };
      return true; // �ݒ萬��
    }

    bool XBoxState::GetButton(const int key, const bool type) const {
      // �͈͓��Ɏ��܂��Ă��邩�̔���
      if (!Math::Arithmetic::IsRange(key, 0, 15)) {
        return false; // �L�[���s��
      }
      // �t���O�ɉ����ĕԂ��l��؂�ւ���
      if (type == InputPress) {
        return _press.Buttons[key]; // ��������Ԃ�
      }
      return _triggerButtons[key];  // �g���K����Ԃ�
    }

    std::pair<int, int> XBoxState::GetStick(const bool stick) const {
      int x, y; // �c���̓��͏��
      // ���E�ǂ���̓��͏�Ԃ��擾���邩
      if (stick == JoypadLeftStick) {
        // ���X�e�B�b�N�̓��͏�Ԃ�Ԃ�
        x = static_cast<int>(_press.ThumbLX);
        y = static_cast<int>(_press.ThumbLY);
        return std::make_pair(x, y);
      }
      // �E�X�e�B�b�N�̓��͏�Ԃ�Ԃ�
      x = static_cast<int>(_press.ThumbRX);
      y = static_cast<int>(_press.ThumbRY);
      return std::make_pair(x, y);
    }
  } // namespace Application
} // namespace AppFrame
/*****************************************************************//**
 * @file   KeyboardState.cpp
 * @brief  �L�[�{�[�h�̓��͏�ԃN���X�̒�`
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "KeyboardState.h"
#ifdef _DEBUG
#include <stdexcept>
#include "../Math/Arithmetic.h"
#endif
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �A�v���P�[�V����
   */
  namespace Application {

    KeyboardState::KeyboardState() : InputBase() {
      _press.fill(0);
      _trigger = _press;
      _type = DeviceType::Keyborad;
    }

    void KeyboardState::Process() {
      auto old = _press; // �O�t���[���̏��
      char keyboard[AllKeysNum];
      // ���͏�Ԃ̎擾�ɐ���������
      if (GetHitKeyStateAll(keyboard) == Error) {
#ifdef _DEBUG
        throw std::logic_error("KeyboardState:���͏�Ԃ̍X�V�Ɏ��s���܂���\n");
#endif
        _state = State::NonActive;
        return; // �擾���s
      }
      // �e���Ԃ̍X�V
      for (auto number = 0; auto&& key : _press) {
        key = keyboard[number]; // �������̍X�V
        _trigger[number] = key ^ old[number] & key; // �g���K���̍X�V
      }
    }

    const int KeyboardState::GetKey(const int keyCode) const {
#ifndef _DEBUG
      if (keyCode < 0 || AllKeysNum < keyCode) {
        return Error; // �������͈͊O
      }
#else
      // �������L�����̔���
      try {
        auto number = Math::Arithmetic::Clamp(keyCode, 0, AllKeysNum);
      } catch (std::out_of_range error) {
        OutputDebugString(error.what());
        return Error; //�͈͊O
      }
#endif
      return _press.at(keyCode);
    }
  } // namespace Application
} // namespace AppFrame
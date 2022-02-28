/*****************************************************************//**
 * @file   MouseState.cpp
 * @brief  �}�E�X�̓��͏�ԃN���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "MouseState.h"

namespace AppFrame {
  namespace Application {

    MouseState::MouseState() : InputBase() {
      _type = DeviceType::Mouse;
      _press = 0;
      _trigger = 0;
    }

    void MouseState::Process() {
      // ���͏�Ԃ̍X�V
      auto old = _press;
      _press = GetMouseInput();
      _trigger = _press ^ old & _press;
      // ���ݍ��W�̎擾
      int x, y;
      GetMousePoint(&x, &y);
      Math::Vector4 pos(x, y);
      // �ω��ʂ̎Z�o
      _move = pos - _position;
      _position = pos;
    }
  } // namespace Application
} // namespace AppFrame
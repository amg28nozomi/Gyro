/*****************************************************************//**
 * @file   MouseState.cpp
 * @brief  マウスの入力状態クラスの定義
 * 
 * @author 鈴木希海
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
      // 入力状態の更新
      auto old = _press;
      _press = GetMouseInput();
      _trigger = _press ^ old & _press;
      // 現在座標の取得
      int x, y;
      GetMousePoint(&x, &y);
      Math::Vector4 pos(x, y);
      // 変化量の算出
      _move = pos - _position;
      _position = pos;
    }
  } // namespace Application
} // namespace AppFrame
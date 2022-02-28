/*****************************************************************//**
 * @file   JoypadState.cpp
 * @brief  ジョイパッドの入力状態クラス
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "JoypadState.h"

/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {

    JoypadState::JoypadState() : InputBase() {
    }

    void JoypadState::Process() {
      // 対象デバイスは入力を受け付けているか
      if (_state != State::Active) {
        return; // 入力処理を行わない
      }
      auto old = _press;
      // 入力状態の更新
      _press = GetJoypadInputState(DX_INPUT_PAD1);
      // 入力状態の更新は成功したか
      if (_press == -1) {
        _state = State::NonActive;
        return; // 更新失敗
      }
      GetJoypadAnalogInput(&_stickX, &_stickY, DX_INPUT_PAD1);
      // トリガ情報の算出
      _trigger = _press ^ old & _press;
    }
  } // namespace Application
} // namespace AppFrame
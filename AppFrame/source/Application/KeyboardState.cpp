/*****************************************************************//**
 * @file   KeyboardState.cpp
 * @brief  キーボードの入力状態クラスの定義
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "KeyboardState.h"
#ifdef _DEBUG
#include <stdexcept>
#include "../Math/Arithmetic.h"
#endif
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief アプリケーション
   */
  namespace Application {

    KeyboardState::KeyboardState() : InputBase() {
      _press.fill(0);
      _trigger = _press;
      _type = DeviceType::Keyborad;
    }

    void KeyboardState::Process() {
      auto old = _press; // 前フレームの状態
      char keyboard[AllKeysNum];
      // 入力状態の取得に成功したか
      if (GetHitKeyStateAll(keyboard) == Error) {
#ifdef _DEBUG
        throw std::logic_error("KeyboardState:入力状態の更新に失敗しました\n");
#endif
        _state = State::NonActive;
        return; // 取得失敗
      }
      // 各種状態の更新
      for (auto number = 0; auto&& key : _press) {
        key = keyboard[number]; // 押下情報の更新
        _trigger[number] = key ^ old[number] & key; // トリガ情報の更新
      }
    }

    const int KeyboardState::GetKey(const int keyCode) const {
#ifndef _DEBUG
      if (keyCode < 0 || AllKeysNum < keyCode) {
        return Error; // 引数が範囲外
      }
#else
      // 引数が有効かの判定
      try {
        auto number = Math::Arithmetic::Clamp(keyCode, 0, AllKeysNum);
      } catch (std::out_of_range error) {
        OutputDebugString(error.what());
        return Error; //範囲外
      }
#endif
      return _press.at(keyCode);
    }
  } // namespace Application
} // namespace AppFrame
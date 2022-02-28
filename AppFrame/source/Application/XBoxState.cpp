/*****************************************************************//**
 * @file   XBoxState.cpp
 * @brief  Xboxコントローラーの入力状態クラスの定義
 * 
 * @author 鈴木希海
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
    constexpr auto JoypadLeftStick = false; // 左スティック
    constexpr auto JoypadRightStick = true; // 右スティック

    constexpr auto Front = 0; // DeadZoneTableの先端
    constexpr auto End = 1;   // DeadZoneTableの末尾

    constexpr short DeadZoneZero = 0;    // デッドゾーン
    constexpr short DeadZoneMax = 30000; //
    constexpr short DefaultDeadZoneMin = 3000;
    constexpr short DefaultDeadZoneMax = 30000;

    XBoxState::XBoxState() : InputBase() {
      _press = XINPUT_STATE();
      _triggerButtons.fill(false);
      _type = DeviceType::Joypad;
      // デッドゾーンをデフォルトの値でセットする
      _deadZone = std::make_pair(DefaultDeadZoneMin, DefaultDeadZoneMax);
    }

    void XBoxState::Process() {
      auto old = _press; // 前フレームのボタン入力情報
      // 入力状態の取得に成功したか
      if (GetJoypadXInputState(DX_INPUT_PAD1, &_press) == Error) {
        // 失敗した場合は未接続状態に遷移
        _state = State::NonActive;
#ifdef _DEBUG
        throw std::logic_error("識別IDが有効ではありません\n");
#endif
        return; // 取得失敗
      }
      // アナログスティック専用の更新
      AnalogStickUpdate();
      // ボタンのみトリガ情報を更新する
      for (auto no = 0; auto && button : _triggerButtons) {
        // 入力状態を比較してトリガ情報を算出する
        button = Trigger(_press.Buttons[no], old.Buttons[no]);
        ++no;
      }
    }

    void XBoxState::DeadZone(short& param) {
      // 正負どちらかの判定
      short p = (Math::Arithmetic::IsPositive(param)) ? 1 : -1;
      short min = _deadZone.first * p;  // 入力下限
      short max = _deadZone.second * p; // 入力上限
      // 対象が正負かに応じて
      if (p == 1) {
        // 下限よりも小さい場合は0として扱う
        if (param < min) {
          param = 0;
          return;
        }
        // それ以外の場合はクランプする
        param = std::clamp(param, min, max);
        return;
      }
      // 対象が負数かつ、下限よりも大きい場合0として扱う
      if (min < param) {
        param = 0;
      }
      // 条件を満たしている場合はクランプする
      param = std::clamp(param, max, min);
      return;
    }

    void XBoxState::AnalogStickUpdate() {
      // 各種スティック情報にデッドゾーン処理を行う
      DeadZone(_press.ThumbLX);
      DeadZone(_press.ThumbLY);
      DeadZone(_press.ThumbRX);
      DeadZone(_press.ThumbRY);
    }

    bool XBoxState::SetDeadZone(const float min, const float max) {
      using Utility = Math::Arithmetic;
      // 判定用テーブルの作成
      std::array<short, 2> deadZoneTable = { std::move(static_cast<short>(min)), std::move(static_cast<short>(max)) };
      for (auto param : deadZoneTable) {
        // 引数は範囲内に収まっているか
        if (!Utility::IsRange(param, DefaultDeadZoneMin, DeadZoneMax)) {
#ifndef _DEBUG
          return false; // 引数が不正
#else
          // 引数が不正な場合は例外を投げる
          throw std::logic_error("SetDeadZone:引数が不正です\n");
#endif
        }
      }
      // デッドゾーンを更新する
      _deadZone = { deadZoneTable[Front], deadZoneTable[End] };
      return true; // 設定成功
    }

    bool XBoxState::GetButton(const int key, const bool type) const {
      // 範囲内に収まっているかの判定
      if (!Math::Arithmetic::IsRange(key, 0, 15)) {
        return false; // キーが不正
      }
      // フラグに応じて返す値を切り替える
      if (type == InputPress) {
        return _press.Buttons[key]; // 押下情報を返す
      }
      return _triggerButtons[key];  // トリガ情報を返す
    }

    std::pair<int, int> XBoxState::GetStick(const bool stick) const {
      int x, y; // 縦横の入力状態
      // 左右どちらの入力状態を取得するか
      if (stick == JoypadLeftStick) {
        // 左スティックの入力状態を返す
        x = static_cast<int>(_press.ThumbLX);
        y = static_cast<int>(_press.ThumbLY);
        return std::make_pair(x, y);
      }
      // 右スティックの入力状態を返す
      x = static_cast<int>(_press.ThumbRX);
      y = static_cast<int>(_press.ThumbRY);
      return std::make_pair(x, y);
    }
  } // namespace Application
} // namespace AppFrame
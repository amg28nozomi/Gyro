/*****************************************************************//**
 * @file   InputOperation.h
 * @brief  入力処理クラス
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <string>
#include <vector>
#include <future>
#include "JoypadState.h"
#include "XboxState.h"

/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    // XBOXコントローラの各種ボタンに紐づける文字列
    constexpr auto PadUp = "up";       //!< 上矢印ボタン
    constexpr auto PadDown = "down";   //!< 下矢印ボタン
    constexpr auto PadLeft = "left";   //!< 左矢印ボタン
    constexpr auto PadRight = "right"; //!< 右矢印ボタン
    constexpr auto PadStart = "start"; //!< STARTボタン
    constexpr auto PadBack = "back";   //!< BACKボタン
    //!< 左スティック
    constexpr auto PadLeftThumb = "leftThumb";
    //!< 右スティック
    constexpr auto PadRightThumb = "rightThumb";
    //!< LBボタン
    constexpr auto PadLeftShoulder = "leftShoulder";
    //!< RBボタン
    constexpr auto PadRightShoulder = "rightShoulder";
    constexpr auto PadButtonA = "a"; //!< Aボタン
    constexpr auto PadButtonB = "b"; //!< Bボタン
    constexpr auto PadButtonX = "x"; //!< Xボタン
    constexpr auto PadButtonY = "y"; //!< Yボタン
    // デバイスタイプ(入力状態の取得で使用)
    constexpr auto DeviceKeyboard = 0; //!< キーボード
    constexpr auto DeviceMouse = 1;    //!< マウス
    constexpr auto DeviceJoypad = 2;   //!< ジョイパッド
    /**
     * @class InputOperation
     * @brief 入力処理
     */
    class InputOperation {
    public:
      /**
       * @brief 実行状態
       */
      enum class State {
        Active,   // 正常
        Paused,   // 一時停止
        NonActive // 接続なし
      };
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      InputOperation(class ApplicationBase& app);
      /**
       * @brief デストラクタ
       */
      ~InputOperation();
      /**
       * @brief 更新処理
       */
      void Process();
      /**
       * @brief  入力デバイスの登録
       * @return true:追加成功 false:追加失敗
       */
      bool AddJoypad();
      /**
       * @brief  入力デバイスが接続されているかの判定
       * @return true:接続あり　false:接続なし
       */
      const bool IsConnection();
      /**
       * @brief  実行状態の取得
       * @return 実行状態
       */
      const State OperationState() const {
        return _state;
      }
      /**
       * @brief  XBOXコントローラ入力状態の取得
       * @return XBOXコントローラの入力状態の参照
       */
      inline XBoxState& GetXBoxState() {
        return _xBox;
      }
      /**
       * @brief  ジョイパッド状態の取得
       * @return ジョイパッドの入力状態の参照
       */
      //inline JoypadState& GetJoypadState() {
      //  return _joypad;
      //}
    private:
      ApplicationBase& _app; //!< アプリケーションの参照
      State _state{};        //!< 状態
      XBoxState _xBox; //!< xボックスコントローラの入力状態
      // JoypadState _joypad;  //!< ジョイパッドの入力状態
      int _accessLimit{0};   //!< デバイスの接続上限
      /**
       * @brief 
       * @param  key 対象ボタンのキー
       * @return 
       */
      int ToNumber(std::string_view key) const;
    };
  } // namespace Application
} // namespace AppFrame
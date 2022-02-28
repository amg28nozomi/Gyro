/*****************************************************************//**
 * @file   XBoxState.h
 * @brief  Xboxコントローラーの入力状態クラス
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "InputBase.h"
#include <array>
#include <utility>
#include <DxLib.h>
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    constexpr auto ButtonNum = 16; //!< ボタン総数
    constexpr auto InputPress = true;    //!< 押下情報
    constexpr auto InputTrigger = false; //!< トリガ入力
    /**
     * @class XBoxState
     * @brief Xboxコントローラーの入力状態(XInput)
     */
    class XBoxState : public InputBase  {
    public:
      /**
       * @brief コンストラクタ
       */
      XBoxState();
      /**
       * @brief  入力状態の更新
       */
      void Process() override;
      /**
       * @brief
       * @param min
       * @param max
       * @return 
       */
      bool SetDeadZone(const float min, const float max);
      /**
       * @brief  ボタン情報の取得(押下)
       * @param  key  対応するキー番号(0～15)
       *              DXライブラリのXINPUTボタン入力定義
       * @brief  type 取得する情報の種類
       *              InputPress:押下情報(デフォルト) InputTrigger:トリガ情報
       * @return true:入力有り false:入力無し
       */
      bool GetButton(const int key, const bool type = InputPress) const;
      /**
       * @brief  アナログスティックの入力状態を取得
       * @brief  stick 左右どちらのアナログスティックの入力を取得するか
       *               false:左スティック　true:右スティック
       * @return first:横軸の入力状態 second:縦軸の入力状態
       */
      std::pair<int, int> GetStick(const bool stick) const;
      /**
       * @brief  左右トリガーボタンの入力状態を取得
       * @return first:左トリガー second:右トリガー
       */
      inline std::pair<int, int> GetTrigger() const {
        return std::make_pair(_press.LeftTrigger, _press.RightTrigger);
      }
      /**
       * @brief  デッドゾーンの取得処理
       * @return デッドゾーン(左辺:最低値 右辺:最大値)
       */
      inline std::pair<short, short> GetDeadZone() const {
        return _deadZone;
      }
      /**
       * @brief  デッドゾーン(最低値)の取得
       * @return デッドゾーン
       */
      inline short GetDeadZoneMin() const {
        return _deadZone.first;
      }
      /**
       * @brief  デッドゾーン(最大値)の取得
       * @return デッドゾーン
       */
      inline short GetDeadZoneMax() const {
        return _deadZone.second;
      }
    private:
      XINPUT_STATE _press;   //!< 入力情報(押下入力)
      std::array<bool, ButtonNum> _triggerButtons; //!< 各種ボタンの押下情報
      std::pair<short, short> _deadZone;           //!< 各種スティックのデッドゾーン情報
      /**
       * @brief  トリガ情報の生成
       * @param  press 対象キーの押下情報
       * @param  old   対象キーの押下情報(前フレーム)
       * @return 対象キーのトリガ情報
       */
      inline int Trigger(const int press, const int old) {
        return press ^ old & press;
      }
      /**
       * @brief デッドゾーン処理
       * @param param 入力情報の参照
       */
      void DeadZone(short& param);
      /**
       * @brief アナログスティックの更新
       */
      void AnalogStickUpdate();
    };
  } // namespace Application
} // namespace AppFrame
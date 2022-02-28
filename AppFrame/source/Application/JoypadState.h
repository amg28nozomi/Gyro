/*****************************************************************//**
 * @file   JoypadState.h
 * @brief  ジョイパッドの入力状態クラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "InputBase.h"
#include <utility>
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    /**
     * @class JoyoadState
     * @brief ジョイパッドの入力状態
     */
    class JoypadState : public InputBase {
    public:
      /**
       * @brief コンストラクタ
       */
      JoypadState();
      /**
       * @brief  入力状態の更新
       */
      void Process() override;
      /**
       * @brief  押下情報の取得
       * @return ジョイパッドの押下情報
       */
      inline int GetKey() const {
        return _press;
      }
      /**
       * @brief  トリガ情報の取得
       * @return ジョイパッドのトリガ情報
       */
      inline int GetTriggerKey() const {
        return _trigger;
      }
      /**
       * @brief  アナログスティックの入力状態取得
       * @return first:横軸の入力状態 second:縦軸の入力状態
       */
      inline std::pair<int, int> GetAnalogStick() const {
        return { _stickX, _stickY };
      }
    private:
      int _press{0};   //!< 押下情報
      int _trigger{0}; //!< トリガ情報
      int _stickX{0};  //!< アナログスティックの入力状態(x軸)
      int _stickY{0};  //!< アナログスティックの入力状態(y軸)
    };
  } // namespace Application
} // namespace AppFrame
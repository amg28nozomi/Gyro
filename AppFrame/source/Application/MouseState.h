/*****************************************************************//**
 * @file   MouseState.h
 * @brief  マウスの入力状態クラス
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "InputBase.h"
#include "../Math/Vector4.h"

/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    /**
     * @class MouseState
     * @brief マウスの入力状態
     */
    class MouseState : public InputBase {
    public:
      /**
       * @brief  コンストラクタ
       */
      MouseState();
      /**
       * @brief  入力状態の更新
       */
      void Process() override;
      /**
       * @brief  押下情報の取得
       * @return 押下情報
       */
      inline int GetKey() const {
        return _press;
      }
      /**
       * @brief  トリガ情報の取得
       * @return トリガ情報
       */
      inline int GetTriggerKey() {
        return _trigger;
      }
      /**
       * @brief  座標の取得
       * @return カーソル座標
       */
      inline Math::Vector4 GetPosition() const {
        return _position;
      }
      /**
       * @brief  変化量の取得
       * @return カーソルの変化量
       */
      inline Math::Vector4 GetMove() const {
        return _move;
      }
    private:
      int _press;   //!< 押下情報
      int _trigger; //!< トリガ情報
      Math::Vector4 _position{0,0}; //!< 座標
      Math::Vector4 _move{0,0};     //!< 変化量
    };
  } // namespace Application
} // namespace AppFrame
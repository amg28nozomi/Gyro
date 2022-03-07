/*****************************************************************//**
 * @file   Light.h
 * @brief  モードゲーム時のライトクラス
 * 
 * @author 土橋峡介
 * @date   March 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief ライト
   */
  namespace Light {
    /**
     * @class Light
     * @brief モードゲーム用ライトクラス
     */
    class Light {
    public:
      /**
       * @brief コンストラクタ
       */
      Light();
      /**
       * @brief デストラクタ
       */
      ~Light();
      /**
       * @brief 初期化処理
       */
      void Init();
      /**
       * @brief 更新処理
       */
      void Process();
      /**
       * @brief 描画処理
       */
      void Draw() const;
    };
  } // namespace Light
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectPlayerDash.h
 * @brief   プレイヤーダッシュエフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#pragma once
#include "EffectBase.h"

 /**
  * @brief ゲームベース
  */
namespace Gyro {
  /**
   * @brief エフェクトベース
   */
  namespace Effect {
    /**
     * @class EffectPlayerDash
     * @brief プレイヤーダッシュエフェクトクラス
     */
    class EffectPlayerDash : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectPlayerDash(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectPlayerDash();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectPlayerLanding.h
 * @brief   プレイヤー着地エフェクトクラス
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
     * @class EffectPlayerLanding
     * @brief プレイヤー着地エフェクトクラス
     */
    class EffectPlayerLanding : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectPlayerLanding(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectPlayerLanding();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
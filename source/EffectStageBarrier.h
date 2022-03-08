/*****************************************************************//**
 * @file    EffectStageBarrier.h
 * @brief   ステージバリアエフェクトクラス
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
     * @class EffectStageBarrier
     * @brief ステージバリアエフェクトクラス
     */
    class EffectStageBarrier : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectStageBarrier(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectStageBarrier();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
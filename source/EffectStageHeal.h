/*****************************************************************//**
 * @file    EffectStageHeal.h
 * @brief   ステージ回復エフェクトクラス
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
     * @class EffectStageHeal
     * @brief ステージ回復エフェクトクラス
     */
    class EffectStageHeal : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectStageHeal(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectStageHeal();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
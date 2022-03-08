/*****************************************************************//**
 * @file    EffectStageBoxDestroy.h
 * @brief   ステージ箱破壊エフェクトクラス
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
     * @class EffectStageBoxDestroy
     * @brief ステージ箱破壊エフェクトクラス
     */
    class EffectStageBoxDestroy : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectStageBoxDestroy(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectStageBoxDestroy();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectEnemyBossExprosion.h
 * @brief   敵ボス爆発エフェクトクラス
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
     * @class EffectEnemyBossExprosion
     * @brief 敵ボス爆発エフェクトクラス
     */
    class EffectEnemyBossExprosion : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectEnemyBossExprosion(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectEnemyBossExprosion();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
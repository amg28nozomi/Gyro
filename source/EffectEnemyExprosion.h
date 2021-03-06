/*****************************************************************//**
 * @file    EffectEnemyExprosion.h
 * @brief   敵爆発エフェクトクラス
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
     * @class EffectEnemyExprosion
     * @brief 敵爆発エフェクトクラス
     */
    class EffectEnemyExprosion : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectEnemyExprosion(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectEnemyExprosion();
      /**
       * @brief  初期化
       */
      void Init() override;
      /**
       * @brief  更新
       */
      void Process() override;
    };
  } // namespace Effect
} // namespace Gyro
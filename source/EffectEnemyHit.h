/*****************************************************************//**
 * @file    EffectEnemyHit.h
 * @brief   敵被ダメエフェクトクラス
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
     * @class EffectEnemyHit
     * @brief 敵被ダメエフェクトクラス
     */
    class EffectEnemyHit : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectEnemyHit(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectEnemyHit();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
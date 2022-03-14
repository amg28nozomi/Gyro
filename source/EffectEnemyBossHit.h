/*****************************************************************//**
 * @file    EffectEnemyBossHit.h
 * @brief   敵ボス被ダメエフェクトクラス
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
     * @class EffectEnemyBossHit
     * @brief 敵ボス被ダメエフェクトクラス
     */
    class EffectEnemyBossHit : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectEnemyBossHit(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectEnemyBossHit();
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
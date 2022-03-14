/*****************************************************************//**
 * @file    EffectEnemyBossAirAttack.h
 * @brief   敵ボス空中攻撃エフェクトクラス
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
     * @class EffectEnemyBossAirAttack
     * @brief 敵ボス空中攻撃エフェクトクラス
     */
    class EffectEnemyBossAirAttack : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectEnemyBossAirAttack(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectEnemyBossAirAttack();
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
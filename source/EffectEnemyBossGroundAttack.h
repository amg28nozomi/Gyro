/*****************************************************************//**
 * @file    EffectEnemyBossGroundAttack.h
 * @brief   敵ボス地上攻撃エフェクトクラス
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
     * @class EffectEnemyBossGroundAttack
     * @brief 敵ボス地上攻撃エフェクトクラス
     */
    class EffectEnemyBossGroundAttack : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectEnemyBossGroundAttack(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectEnemyBossGroundAttack();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
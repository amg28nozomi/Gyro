/*****************************************************************//**
 * @file    EffectEnemyBossGroundAttack1.h
 * @brief   敵ボス地上攻撃1エフェクトクラス
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
     * @class EffectEnemyBossGroundAttack1
     * @brief 敵ボス地上攻撃1エフェクトクラス
     */
    class EffectEnemyBossGroundAttack1 : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectEnemyBossGroundAttack1(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectEnemyBossGroundAttack1();
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
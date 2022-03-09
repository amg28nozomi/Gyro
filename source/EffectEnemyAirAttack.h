/*****************************************************************//**
 * @file    EffectEnemyAirAttack.h
 * @brief   敵空中攻撃エフェクトクラス
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
     * @class EffectEnemyAirAttack
     * @brief 敵空中攻撃エフェクトクラス
     */
    class EffectEnemyAirAttack : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectEnemyAirAttack(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectEnemyAirAttack();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
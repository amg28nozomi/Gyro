/*****************************************************************//**
 * @file    EffectEnemyGroundAttack.h
 * @brief   敵地上攻撃エフェクトクラス
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
     * @class EffectEnemyGroundAttack
     * @brief 敵地上攻撃エフェクトクラス
     */
    class EffectEnemyGroundAttack : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectEnemyGroundAttack(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectEnemyGroundAttack();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectPlayerAirHeavyAttack2.h
 * @brief   プレイヤー空中強攻撃2エフェクトクラス
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
     * @class EffectPlayerAirHeavyAttack2
     * @brief プレイヤー空中強攻撃2エフェクトクラス
     */
    class EffectPlayerAirHeavyAttack2 : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectPlayerAirHeavyAttack2(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectPlayerAirHeavyAttack2();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
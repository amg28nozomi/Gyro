/*****************************************************************//**
 * @file    EffectPlayerAirWeakAttack1.h
 * @brief   プレイヤー空中弱攻撃1エフェクトクラス
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
     * @class EffectPlayerAirWeakAttack1
     * @brief プレイヤー空中弱攻撃1エフェクトクラス
     */
    class EffectPlayerAirWeakAttack1 : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectPlayerAirWeakAttack1(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectPlayerAirWeakAttack1();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
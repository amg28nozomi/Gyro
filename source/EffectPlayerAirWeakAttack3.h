/*****************************************************************//**
 * @file    EffectPlayerAirWeakAttack3.h
 * @brief   プレイヤー空中弱攻撃3エフェクトクラス
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
     * @class EffectPlayerAirWeakAttack3
     * @brief プレイヤー空中弱攻撃3エフェクトクラス
     */
    class EffectPlayerAirWeakAttack3 : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectPlayerAirWeakAttack3(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectPlayerAirWeakAttack3();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
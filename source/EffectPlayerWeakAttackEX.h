/*****************************************************************//**
 * @file    EffectPlayerWeakAttackEX.h
 * @brief   プレイヤー弱攻撃EXエフェクトクラス
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
     * @class EffectPlayerWeakAttackEX
     * @brief プレイヤー弱攻撃EXエフェクトクラス
     */
    class EffectPlayerWeakAttackEX : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectPlayerWeakAttackEX(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectPlayerWeakAttackEX();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
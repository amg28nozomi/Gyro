/*****************************************************************//**
 * @file    EffectPlayerAvoidance.h
 * @brief   プレイヤー回避エフェクトクラス
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
     * @class EffectPlayerAvoidance
     * @brief プレイヤー回避エフェクトクラス
     */
    class EffectPlayerAvoidance : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectPlayerAvoidance(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectPlayerAvoidance();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
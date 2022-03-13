/*****************************************************************//**
 * @file    EffectPlayerJustEmit.h
 * @brief   プレイヤージャスト終了エフェクトクラス
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
     * @class EffectPlayerJustEmit
     * @brief プレイヤージャスト終了エフェクトクラス
     */
    class EffectPlayerJustEmit : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectPlayerJustEmit(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectPlayerJustEmit();
      /**
       * @brief  初期化
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
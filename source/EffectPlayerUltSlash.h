/*****************************************************************//**
 * @file    EffectPlayerUltSlash.h
 * @brief   プレイヤー必殺攻撃エフェクトクラス
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
     * @class EffectPlayerUltSlash
     * @brief プレイヤー必殺攻撃エフェクトクラス
     */
    class EffectPlayerUltSlash : public EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectPlayerUltSlash(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectPlayerUltSlash();
      /**
       * @brief  初期化
       */
      void Init() override;

    private:
      /**
       * @brief  エフェクト消去
       */
      void DeadEffect() override;
    };
  } // namespace Effect
} // namespace Gyro
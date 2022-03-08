/*****************************************************************//**
 * @file    EffectComponent.h
 * @brief   エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"

 /**
  * @brief ゲームベース
  */
namespace Gyro {
  /**
   * @brief エフェクトベース
   */
  namespace Effect {
    namespace AppMath = AppFrame::Math;
    /**
     * @class EffecComponent
     * @brief エフェクトクラス
     */
    class EffectComponent {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectComponent(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectComponent();
      /**
       * @brief  更新
       */
      void Process();
      /**
       * @brief  描画
       */
      void Draw() const;
      /**
       * @brief  エフェクト再生
       * @param  key エフェクトキー
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       */
      void PlayEffect(const std::string_view key, const AppMath::Vector4 position, const float radian);

    private:
      /**
       * @brief  エフェクトハンドルの取得
       * @param  key エフェクトキー
       */
      int GetEffectHandle(const std::string_view key);

      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
    };
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file   GaugeHP.h
 * @brief  ゲーム内のトリックゲージの処理するクラス
 *
 * @author 土橋 峡介
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "GaugeBase.h"
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief ゲージ
   */
  namespace Gauge {
    /**
     * @class ゲージHP
     * @brief ゲーム内のHPの処理するクラス
     */
    class GaugeTrick : public Gauge::GaugeBase {
    public:
      /**
       * @brief コンストラクタ
       */
      GaugeTrick(Application::ApplicationMain& app);
      /**
       * デストラクタ
       */
      ~GaugeTrick();
      /**
      * @brief  初期化処理
      * @param  value ゲージの最大値
      * @return true
      */
      bool Init(float value) override;
      /**
       * @brief 更新
       */
      bool Process() override;
      /**
       * @brief 描画
       */
      bool Draw() const override;
    private:
    };
  } // namesapce Gauge
} // namespace Gyro

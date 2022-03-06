/*****************************************************************//**
 * @file   GaugeHP.h
 * @brief  ゲーム内のHPゲージの処理するクラス
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
    class GaugeHP : public Gauge::GaugeBase {
    public:
      /**
       * @brief コンストラクタ
       */
      GaugeHP(Application::ApplicationMain& app);
      /**
       * デストラクタ
       */
      ~GaugeHP();
      /**
       * @brief  初期化
       * @param  ゲージの最大値
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


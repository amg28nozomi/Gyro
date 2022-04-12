/*****************************************************************//**
 * @file   GaugeHP.h
 * @brief  ゲーム内のエネミーのHPゲージの処理するクラス
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
    class GaugeEnemy : public Gauge::GaugeBase {
    public:
      /**
       * @brief コンストラクタ
       */
      GaugeEnemy(Application::ApplicationMain& app);
      /**
       * デストラクタ
       */
      ~GaugeEnemy();
      /**
       * @brief  初期化
       * @param  valu ゲージの最大値
       * @return true
       */
      bool Init(float value) override;
      /**
       * @brief 更新
       */
      bool Process() override;
      /**
       * @brief 描画
       * @param position 座標
       * @param height 座標
       */
      bool Draw(const AppFrame::Math::Vector4 position, const float height) const;
      /**
       * @brief 画像の読み込み
       */
      void LoadGraphs();
      /**
       * @brief 画像の解放
       */
      void ReleaseGraph();
    private:
      AppFrame::Math::Vector4 _position;  //!< 座標
      int _gaugeFrontHandle{ 0 }; //!< HPゲージ画像(上)
      int _gaugeBackHandle{ 0 };  //!< HPゲージ画像(下)
      int _hpFrame{ 0 };          //!< HPフレーム画像(外枠)
    };
  } // namesapce Gauge
} // namespace Gyro

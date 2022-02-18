/*****************************************************************//**
 * @file   GaugeHP.h
 * @brief  ゲーム内のエネミーのHPゲージの処理するクラス
 *
 * @author 土橋 峡介
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "GaugeBase.h"
#include "GaugeServer.h"
#include "ObjectBase.h"
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
       * @brief 初期化
       */
      bool Init() override;
      /**
       * @brief 更新
       */
      bool Process() override;
      /**
       * @brief 描画
       */
      bool Draw() const override;
    private:
      AppFrame::Math::Vector4 _position;  //!< 座標
      int _handle{ 0 };
      int _handle2{ 0 };
      int _handle3{ 0 };
    };
  } // namesapce Gauge
} // namespace Gyro

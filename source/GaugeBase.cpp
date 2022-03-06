/*****************************************************************//**
 * @file   GaugeBase.cpp
 * @brief  ゲームゲージの基底クラス
 * 
 * @author 土橋峡介
 * @date   January 2022
 *********************************************************************/
#include "GaugeBase.h"

namespace Gyro {
  namespace Gauge {

    GaugeBase::GaugeBase(Application::ApplicationMain& app) : _app(app) {
    }

    bool GaugeBase::Init(float value) {
      return true;
    }

    bool GaugeBase::Process() {
      // 描画用に使う値の計算処理
      _point = ((_maxW - 5) / _maxGauge) * _value;

      return true;
    }

    bool GaugeBase::Draw() const {
      return true;
    }

    void GaugeBase::Add(float value) {
      _value += value;
    }

    void GaugeBase::Sub(float value) {
      _value -= value;
    }
  } // namespace Gauge
} // namespace Gyro
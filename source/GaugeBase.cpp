/*****************************************************************//**
 * @file   GaugeBase.cpp
 * @brief  ƒQ[ƒ€ƒQ[ƒW‚ÌŠî’êƒNƒ‰ƒX
 * 
 * @author “y‹´‹¬‰î
 * @date   January 2022
 *********************************************************************/
#include "GaugeBase.h"

namespace Gyro {
  namespace Gauge {

    GaugeBase::GaugeBase(Application::ApplicationMain& app) : _app(app) {
    }

    bool GaugeBase::Init() {
      return true;
    }

    bool GaugeBase::Process() {
      _point = (_maxW - 5) - ((_maxW - 5) / _maxGauge) * _value;

      return true;
    }

    bool GaugeBase::Draw() const {
      return true;
    }

    void GaugeBase::Add(float value) {
      _value += value;
    }
  } // namespace Gauge
} // namespace Gyro

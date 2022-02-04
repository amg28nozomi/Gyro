/*****************************************************************//**
 * @file   GaugeHP.cpp
 * @brief  プレイヤーのHPバー処理
 * 
 * @author 土橋 峡介
 * @date   February 2022
 *********************************************************************/
#include "GaugeHP.h"

namespace {
  constexpr auto GAUGE_X_POSITION_1 = 40;
  constexpr auto GAUGE_X_POSITION_2 = 640;
  constexpr auto GAUGE_Y_POSITION_1 = 100;
  constexpr auto GAUGE_Y_POSITION_2 = 125;
}

namespace Gyro {
  namespace Gauge {

    GaugeHP::GaugeHP() {
    }

    GaugeHP::~GaugeHP() {
    }

    bool GaugeHP::Init() {
      _maxW = 645.f;
      _maxGauge = 1000.f;
      _point = 600.f;
      _hitPoint = 640.f;

      return true;
    }

    bool GaugeHP::Process() {
      GaugeBase::Process();
      if (_point < GAUGE_X_POSITION_1) {
          _point = GAUGE_X_POSITION_1;
      }
      if (_point != _hitPoint) {
          _hitPoint--;
      }
      if (_hitPoint < GAUGE_X_POSITION_1) {
          _hitPoint = GAUGE_X_POSITION_1;
      }

      return true;
    }

    bool GaugeHP::Draw() const {
      auto cr = GetColor(0, 0, 0);
      auto cr2 = GetColor(255, 0, 0);
      auto cr3 = GetColor(204, 204, 204);
      auto hpCr = GetColor(0, 255, 0);
      DrawBox(GAUGE_X_POSITION_1 - 5, GAUGE_Y_POSITION_1 - 5, static_cast<int>(_maxW), GAUGE_Y_POSITION_2 + 5, cr, TRUE);
      DrawBox(GAUGE_X_POSITION_1, GAUGE_Y_POSITION_1, GAUGE_X_POSITION_2, GAUGE_Y_POSITION_2, cr3, TRUE);
      DrawBox(GAUGE_X_POSITION_1, GAUGE_Y_POSITION_1, static_cast<int>(_hitPoint), GAUGE_Y_POSITION_2, cr2, TRUE);
      DrawBox(GAUGE_X_POSITION_1, GAUGE_Y_POSITION_1, static_cast<int>(_point), GAUGE_Y_POSITION_2, hpCr, TRUE);

      return true;
    }
  } // namespace Gauge
} // namespace Gyro

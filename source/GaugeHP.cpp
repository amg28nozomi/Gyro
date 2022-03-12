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

    GaugeHP::GaugeHP(Application::ApplicationMain& app) : Gauge::GaugeBase(app) {
    }

    GaugeHP::~GaugeHP() {
    }

    bool GaugeHP::Init(float value) {
      _maxW = 645.f; // HPフレームの横幅
      _maxGauge = value; // HPの上限
      _point = 600.f; // HPゲージの前面
      _hitPoint = 640.f; // HPゲージの背面
      _value = value;

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
      auto black = GetColor(0, 0, 0);
      auto red = GetColor(255, 0, 0);
      auto gray = GetColor(204, 204, 204);
      auto green = GetColor(0, 255, 0);
      DrawBox(GAUGE_X_POSITION_1 - 5, GAUGE_Y_POSITION_1 - 5, static_cast<int>(_maxW), GAUGE_Y_POSITION_2 + 5, black, TRUE);
      DrawBox(GAUGE_X_POSITION_1, GAUGE_Y_POSITION_1, GAUGE_X_POSITION_2, GAUGE_Y_POSITION_2, gray, TRUE);
      DrawBox(GAUGE_X_POSITION_1, GAUGE_Y_POSITION_1, static_cast<int>(_hitPoint), GAUGE_Y_POSITION_2, red, TRUE);
      DrawBox(GAUGE_X_POSITION_1, GAUGE_Y_POSITION_1, static_cast<int>(_point), GAUGE_Y_POSITION_2, green, TRUE);

      return true;
    }

    bool GaugeHP::IsMax() const {
      return static_cast<int>(_value) == static_cast<int>(_maxGauge);
    }
  } // namespace Gauge
} // namespace Gyro

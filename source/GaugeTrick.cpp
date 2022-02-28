/*****************************************************************//**
 * @file   GaugeHP.cpp
 * @brief  プレイヤーのHPゲージ処理
 *
 * @author 土橋 峡介
 * @date   February 2022
 *********************************************************************/
#include "GaugeTrick.h"

namespace {
  constexpr auto GAUGE_X_POSITION_1 = 40;
  constexpr auto GAUGE_X_POSITION_2 = 600;
  constexpr auto GAUGE_Y_POSITION_1 = 150;
  constexpr auto GAUGE_Y_POSITION_2 = 175;
}

namespace Gyro {
  namespace Gauge {

    GaugeTrick::GaugeTrick(Application::ApplicationMain& app) : Gauge::GaugeBase(app) {
    }

    GaugeTrick::~GaugeTrick() {
    }

    bool GaugeTrick::Init(float value) {
      _maxW = 605.f;
      _maxGauge = value;
      _point = 0.f;
      _value = 0.f;

      return true;
    }

    bool GaugeTrick::Process() {
      GaugeBase::Process();
      if (_point < GAUGE_X_POSITION_1) {
          _point = GAUGE_X_POSITION_1;
      }else if (_point > GAUGE_X_POSITION_2) {
          _point = GAUGE_X_POSITION_2;
      }

      return true;
    }

    bool GaugeTrick::Draw() const {
      auto black = GetColor(0, 0, 0);
      auto gray = GetColor(204, 204, 204);
      auto orange = GetColor(255, 165, 0);
      DrawBox(GAUGE_X_POSITION_1 - 5, GAUGE_Y_POSITION_1 - 5, static_cast<int>(_maxW), GAUGE_Y_POSITION_2 + 5, black, TRUE);
      DrawBox(GAUGE_X_POSITION_1, GAUGE_Y_POSITION_1, GAUGE_X_POSITION_2, GAUGE_Y_POSITION_2, gray, TRUE);
      DrawBox(GAUGE_X_POSITION_1, GAUGE_Y_POSITION_1, static_cast<int>(_point), GAUGE_Y_POSITION_2, orange, TRUE);

      return true;
    }
  } // namespace Gauge
} // namespace Gyro
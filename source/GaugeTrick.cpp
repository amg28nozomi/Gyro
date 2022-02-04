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

    GaugeTrick::GaugeTrick() {
    }

    GaugeTrick::~GaugeTrick() {
    }

    bool GaugeTrick::Init() {
      _maxW = 605.f;
      _maxGauge = 1000.f;
      _point = 0.f;
      _value = 950.f;

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
      auto cr = GetColor(0, 0, 0);
      auto cr2 = GetColor(204, 204, 204);
      auto trickCr = GetColor(255, 165, 0);
      DrawBox(GAUGE_X_POSITION_1 - 5, GAUGE_Y_POSITION_1 - 5, static_cast<int>(_maxW), GAUGE_Y_POSITION_2 + 5, cr, TRUE);
      DrawBox(GAUGE_X_POSITION_1, GAUGE_Y_POSITION_1, GAUGE_X_POSITION_2, GAUGE_Y_POSITION_2, cr2, TRUE);
      DrawBox(GAUGE_X_POSITION_1, GAUGE_Y_POSITION_1, static_cast<int>(_point), GAUGE_Y_POSITION_2, trickCr, TRUE);

      return true;
    }
  } // namespace Gauge
} // namespace Gyro
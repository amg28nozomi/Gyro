/*****************************************************************//**
 * @file   GaugeBase.cpp
 * @brief  �Q�[���Q�[�W�̊��N���X
 * 
 * @author �y������
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
      // �`��p�Ɏg���l�̌v�Z����
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
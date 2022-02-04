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

        GaugeBase::GaugeBase() {
        }

        GaugeBase::GaugeBase(int gauge) {
            _point = static_cast<float>(gauge);
        }

        GaugeBase::GaugeBase(float gauge) : _point(gauge) {
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

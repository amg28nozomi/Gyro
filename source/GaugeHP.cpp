/*****************************************************************//**
 * @file   GaugeHP.cpp
 * @brief  �v���C���[��HP�o�[����
 * 
 * @author �y�� ����
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
      // �e�평����
      _maxW = 645.f; // HP�t���[���̉���
      _maxGauge = value; // HP�̏��
      _point = 640.f; // HP�Q�[�W�̑O��
      _hitPoint = 640.f; // HP�Q�[�W�̔w��
      _value = value;

      return true;
    }

    bool GaugeHP::Process() {
      GaugeBase::Process();
      // �Q�[�W���t���[�����͂ݏo�Ȃ��悤�ɂ���
      // �Œ�l
      if (_point < GAUGE_X_POSITION_1) {
        _point = GAUGE_X_POSITION_1;
      }
      else if (_hitPoint < GAUGE_X_POSITION_1) {
        _hitPoint = GAUGE_X_POSITION_1;
      }
      // �ő�l
      if (_point > GAUGE_X_POSITION_2) {
        _point = GAUGE_X_POSITION_2;
      }
      else if (_hitPoint > GAUGE_X_POSITION_2) {
        _hitPoint = GAUGE_X_POSITION_2;
      }
      // �w�ʂ�HP�Q�[�W��O�ʂɂ��Ă����悤�ɂ���
      if (_point <= _hitPoint) {
        _hitPoint--;
      }
      else if (_hitPoint <= _point) {
        _hitPoint = _point;
      }

      return true;
    }

    bool GaugeHP::Draw() const {
      auto black = GetColor(0, 0, 0);
      auto red = GetColor(255, 0, 0);
      auto gray = GetColor(204, 204, 204);
      auto green = GetColor(0, 255, 0);
      DrawBox(GAUGE_X_POSITION_1 - 5, GAUGE_Y_POSITION_1 - 5, static_cast<int>(_maxW), GAUGE_Y_POSITION_2 + 5, black, true);
      DrawBox(GAUGE_X_POSITION_1, GAUGE_Y_POSITION_1, GAUGE_X_POSITION_2, GAUGE_Y_POSITION_2, gray, true);
      DrawBox(GAUGE_X_POSITION_1, GAUGE_Y_POSITION_1, static_cast<int>(_hitPoint), GAUGE_Y_POSITION_2, red, true);  // �w��HP�Q�[�W
      DrawBox(GAUGE_X_POSITION_1, GAUGE_Y_POSITION_1, static_cast<int>(_point), GAUGE_Y_POSITION_2, green, true);   // �O��HP�Q�[�W

      return true;
    }

    bool GaugeHP::IsMax() const {
      return static_cast<int>(_value) == static_cast<int>(_maxGauge);
    }
  } // namespace Gauge
} // namespace Gyro

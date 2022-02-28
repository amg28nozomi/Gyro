/*****************************************************************//**
 * @file   GaugeHP.cpp
 * @brief  �G�l�~�[��HP�o�[����
 *
 * @author �y�� ����
 * @date   February 2022
 *********************************************************************/
#include "GaugeEnemy.h"
#include "ObjectBase.h"
#include "ObjectServer.h"
#include "UtilityDX.h"

namespace {
  constexpr auto GAUGE_X_POSITION_1 = -33.f;
  constexpr auto GAUGE_X_POSITION_2 = 33.f;
  constexpr auto GAUGE_Y_POSITION_1 = 2.5f;
  constexpr auto GAUGE_Y_POSITION_2 = -2.5f;
}

namespace Gyro {
  namespace Gauge {

    GaugeEnemy::GaugeEnemy(Application::ApplicationMain& app) : Gauge::GaugeBase(app) {
      LoadGraphs();
    }

    GaugeEnemy::~GaugeEnemy() {
      ReleaseGraph();
    }

    bool GaugeEnemy::Init(float value) {
      _maxW = 66.f;
      _maxGauge = value;
      _point = GAUGE_X_POSITION_2;
      _hitPoint = GAUGE_X_POSITION_2;
      _value = value;

      return true;
    }

    bool GaugeEnemy::Process() {
      // �v�Z������`�捷�������l�����炷
      _point = ((_maxW / _maxGauge) * _value) - 33.f;
      if (_point < GAUGE_X_POSITION_1) {
        _point = GAUGE_X_POSITION_1; // HP���Œ�l��艺����Ȃ��悤�ɂ���
      }
      if (_point != _hitPoint) {
        _hitPoint--; // �ԃQ�[�W��HP�ɂ��Ă����悤�ɂ���
      }
      if (_hitPoint < GAUGE_X_POSITION_1) {
        _hitPoint = GAUGE_X_POSITION_1; // �ԃQ�[�W���Œ�l��艺����Ȃ��悤�ɂ���
      }

      return true;
    }

    bool GaugeEnemy::Draw(const AppFrame::Math::Vector4 position) const {
      auto objects = _app.GetObjectServer().GetObjects(); // �I�u�W�F�N�g�̃R�s�[
      AppFrame::Math::Vector4 DrawPosition;
      auto pos = position;
      DrawPosition = pos.AddVectorY(220.f); // Enemy�̍�������
      DrawBillboard3D(UtilityDX::ToVECTOR(DrawPosition), 0.5f, 0.5f, 68.0f, 0.0f, _hpFrame, true); // �O�g
      DrawModiBillboard3D(UtilityDX::ToVECTOR(DrawPosition), GAUGE_X_POSITION_1, 2.5f, _hitPoint, 2.5f, _hitPoint, -2.5f, -33.f, -2.5f, _gaugeBackHandle, true); // �w��HP�Q�[�W
      DrawModiBillboard3D(UtilityDX::ToVECTOR(DrawPosition), GAUGE_X_POSITION_1, 2.5f, _point, 2.5f, _point, -2.5f, -33.f, -2.5f, _gaugeFrontHandle, true); // �O��HP�Q�[�W

      return true;
    }

    void GaugeEnemy::LoadGraphs() {
      // �摜�̓ǂݍ���
      _gaugeFrontHandle = LoadGraph("res/UI/Ehp01.png");
      _gaugeBackHandle = LoadGraph("res/UI/Ehp02.png");
      _hpFrame = LoadGraph("res/UI/Ehp03.png");
    }

    void GaugeEnemy::ReleaseGraph() {
      // �ǂݍ��񂾉摜�̉��
      DeleteGraph(_gaugeFrontHandle);
      DeleteGraph(_gaugeBackHandle);
      DeleteGraph(_hpFrame);
    }
  } // namespace Gauge
} // namespace Gyro

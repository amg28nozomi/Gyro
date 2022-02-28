/*****************************************************************//**
 * @file   GaugeHP.cpp
 * @brief  エネミーのHPバー処理
 *
 * @author 土橋 峡介
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
      // 計算した後描画差分だけ値を減らす
      _point = ((_maxW / _maxGauge) * _value) - 33.f;
      if (_point < GAUGE_X_POSITION_1) {
        _point = GAUGE_X_POSITION_1; // HPが最低値より下がらないようにする
      }
      if (_point != _hitPoint) {
        _hitPoint--; // 赤ゲージをHPについていくようにする
      }
      if (_hitPoint < GAUGE_X_POSITION_1) {
        _hitPoint = GAUGE_X_POSITION_1; // 赤ゲージが最低値より下がらないようにする
      }

      return true;
    }

    bool GaugeEnemy::Draw(const AppFrame::Math::Vector4 position) const {
      auto objects = _app.GetObjectServer().GetObjects(); // オブジェクトのコピー
      AppFrame::Math::Vector4 DrawPosition;
      auto pos = position;
      DrawPosition = pos.AddVectorY(220.f); // Enemyの高さ足す
      DrawBillboard3D(UtilityDX::ToVECTOR(DrawPosition), 0.5f, 0.5f, 68.0f, 0.0f, _hpFrame, true); // 外枠
      DrawModiBillboard3D(UtilityDX::ToVECTOR(DrawPosition), GAUGE_X_POSITION_1, 2.5f, _hitPoint, 2.5f, _hitPoint, -2.5f, -33.f, -2.5f, _gaugeBackHandle, true); // 背面HPゲージ
      DrawModiBillboard3D(UtilityDX::ToVECTOR(DrawPosition), GAUGE_X_POSITION_1, 2.5f, _point, 2.5f, _point, -2.5f, -33.f, -2.5f, _gaugeFrontHandle, true); // 前面HPゲージ

      return true;
    }

    void GaugeEnemy::LoadGraphs() {
      // 画像の読み込み
      _gaugeFrontHandle = LoadGraph("res/UI/Ehp01.png");
      _gaugeBackHandle = LoadGraph("res/UI/Ehp02.png");
      _hpFrame = LoadGraph("res/UI/Ehp03.png");
    }

    void GaugeEnemy::ReleaseGraph() {
      // 読み込んだ画像の解放
      DeleteGraph(_gaugeFrontHandle);
      DeleteGraph(_gaugeBackHandle);
      DeleteGraph(_hpFrame);
    }
  } // namespace Gauge
} // namespace Gyro

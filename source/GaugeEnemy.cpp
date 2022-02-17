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
      Init();
      _handle = LoadGraph("res/UI/Ehp01.png");
      _handle2 = LoadGraph("res/UI/Ehp02.png");
      _handle3 = LoadGraph("res/UI/Ehp03.png");
    }

    GaugeEnemy::~GaugeEnemy() {
    }

    bool GaugeEnemy::Init() {
      _maxW = 38.f;
      _maxGauge = 1000.f;
      _point = GAUGE_X_POSITION_2;
      _hitPoint = GAUGE_X_POSITION_2;

      return true;
    }

    bool GaugeEnemy::Process() {
      GaugeBase::Process();
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

    bool GaugeEnemy::Draw() const {
      auto objects = _app.GetObjectServer().GetObjects(); // オブジェクトのコピー
      AppFrame::Math::Vector4 finalPosition;
      // Enemyの座標を持ってくる
      for (auto obj : objects) {
        // 敵の場合のみ処理を行う
        if (obj->GetId() == Object::ObjectBase::ObjectId::Enemy) {
          auto position = obj->GetPosition();
          finalPosition = position.AddVectorY(220.f); // Enemyの高さ足す
        }
        DrawBillboard3D(UtilityDX::ToVECTOR(finalPosition), 0.5f, 0.5f, 68.0f, 0.0f, _handle3, true); // 外枠
        DrawModiBillboard3D(UtilityDX::ToVECTOR(finalPosition), GAUGE_X_POSITION_1, 2.5f, _hitPoint, 2.5f, _hitPoint, -2.5f, -33.f, -2.5f, _handle2, true); // HPの下
        DrawModiBillboard3D(UtilityDX::ToVECTOR(finalPosition), GAUGE_X_POSITION_1, 2.5f, _point, 2.5f, _point, -2.5f, -33.f, -2.5f, _handle, true);  // HP
      }

      return true;
    }
  } // namespace Gauge
} // namespace Gyro

/*****************************************************************//**
 * @file   CollisionCylinder.cpp
 * @brief  円柱の当たり判定クラスの定義
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "CollisionCylinder.h"
#include <appframe.h>
#include <DxLib.h>

namespace Gyro {

  namespace Object {

    CollisionCylinder::CollisionCylinder() : _position(), _radius(), _line() {
#ifdef _DEBUG
      _color = AppData::Color();
#endif
    }

    CollisionCylinder::CollisionCylinder(AppMath::Vector4 pos, float radius, AppMath::Line line) {
      _position = pos;
      _radius = radius;
      _line = line;
#ifdef _DEBUG
      _color = AppData::Color();
#endif
    }

    void CollisionCylinder::Process(AppMath::Vector4 pos) {
      // 座標を更新する
      _position = pos;
    }

    void CollisionCylinder::Draw() {
#ifdef _DEBUG
      
      auto [start, end] = _line.GetVector();
      // 始点・終点
      VECTOR sVector(start.GetX(), start.GetY(), start.GetZ());
      VECTOR eVector(end.GetX(), end.GetY(), end.GetZ());
      // 情報を元に描画を行う
      DrawCapsule3D();
#endif
    }
  } // namespace Object
} // namespace Gyro
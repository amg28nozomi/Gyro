/*****************************************************************//**
 * @file   CollisionCylinder.cpp
 * @brief  円柱の当たり判定クラスの定義
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "CollisionCylinder.h"
#include <DxLib.h>
#include "UtilityDX.h"
#include "ObjectBase.h"

namespace Gyro {

  namespace Object {

    CollisionCylinder::CollisionCylinder(ObjectBase& owner) : _owner(owner), _position(), _radius(), _line() {
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
      // 円の座標を更新する

    }

    void CollisionCylinder::Draw() {
#ifdef _DEBUG
      // ベクトルの取得
      auto [start, end] = _line.GetVector();
      // 始点・終点
      auto sVector = UtilityDX::ToVECTOR(start);
      auto eVector = UtilityDX::ToVECTOR(end);
      // 情報を元にスフィアの描画を行う
      DrawCapsule3D(sVector, eVector, _radius * 2, 10, 0, 0, TRUE);
      // 直線を描画する
      DrawLine3D(sVector, eVector, _color.GetColorCode());
#endif
    }
  } // namespace Object
} // namespace Gyro
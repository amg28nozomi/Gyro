/*****************************************************************//**
 * @file   CollisionSphere.cpp
 * @brief  コリジョンベースのサブクラス
 *         球の当たり判定クラスの定義
 * 
 * @date   January 2022
 *********************************************************************/
#include "CollisionSphere.h"
#include "ObjectBase.h"
#include "UtilityDX.h"

namespace Gyro {
  namespace Object {

    CollisionSphere::CollisionSphere(ObjectBase& owner, AppMath::Vector4 center, float radius) : CollisionBase(owner), _radius(radius) {
      _position = center;
      _type = CollisionType::Sphere; // コリジョンタイプを球に設定
#ifdef _DEBUG
      using Color = AppFrame::Data::Color;
      _color = Color::GetColor(0, 0, 0); // カラーコードの取得
#endif
    }

    void CollisionSphere::Process() {
#ifdef _DEBUG
      _collision = false;
#endif
      //  // 更新処理を行う
      //  auto old = _position;
      //  // 所有者の座標を取得
      //  _position = _owner.GetPosition();
      //}
    }

    void CollisionSphere::Process(AppMath::Vector4 vector) {
#ifdef _DEBUG
      _collision = false; // 衝突フラグを初期化
#endif
      // 前フレーム座標
      auto old = _position;
      // 移動座標
      auto newPosition = _position + vector;
      // 中心座標に移動量を加算する
      _position.Add(vector);
    }

#ifdef _DEBUG
    void CollisionSphere::Draw() {
      // デバッグフラグが立っている場合のみ描画を行う
      using AppColor = AppFrame::Data::Color;
      // 球を描画する(衝突している場合は球を塗り潰す)
      DrawSphere3D(UtilityDX::ToVECTOR(_position), _radius, 10, AppColor::GetColor(0, 0, 0), 0, _collision);

      auto [x, y, z] = _position.GetVector3();
      DrawFormatString(1000, 0, 125, "球 x:%f y:%f, z:%f", x, y, z);
    }
#endif

    bool CollisionSphere::IsHit() {
      // 後程実装
      return false;
    }

    bool CollisionSphere::IntersectSphere(const CollisionSphere& sphere) {
      // 球と球の衝突判定
      auto distSq = AppMath::Vector4::LengthSquared(_position - sphere._position);
      auto sumRadius = _radius + sphere._radius;
#ifndef _DEBUG
      return distSq <= (sumRadius * sumRadius);
#else
      _collision = distSq <= (sumRadius * sumRadius);
      return _collision;
#endif
    }

    bool CollisionSphere::IntersectPoint(const AppMath::Vector4& point) {
      // 球と点の衝突判定
      auto l = AppMath::Vector4::LengthSquared(_position - point);
      auto radius2 = _radius * _radius;
#ifndef _DEBUG
      return l <= radius2;
#else
      _collision = l <= radius2;
      return _collision;
#endif
    }
  } // namespace Object
} // namespace Gyro
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
    }

    void CollisionSphere::Process() {
      // 更新処理を行う
      auto old = _position;
      // 所有者の座標を取得
      _position = _owner.GetPosition();
    }

    void CollisionSphere::Process(AppMath::Vector4 vector) {
      // 前フレーム座標
      auto old = _position;
      // 移動座標
      auto newPosition = _position + vector;
    }

#ifdef _DEBUG
    void CollisionSphere::Draw() {
      // デバッグフラグが立っている場合のみ描画を行う
      if (!_debug) { return; }
      using AppColor = AppFrame::Data::Color;
      // 球を描画する
      DrawSphere3D(UtilityDX::ToVECTOR(_position), _radius, 10, AppColor::GetColor(0, 0, 0), 0, FALSE);
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
      return distSq <= (sumRadius * sumRadius);
    }
  } // namespace Object
} // namespace Gyro
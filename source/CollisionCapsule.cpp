/*****************************************************************//**
 * @file   CollisionCapsule.cpp
 * @brief  
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "CollisionCapsule.h"
#include <appframe.h>
#include "CollisionSphere.h"
#include "UtilityDX.h"

namespace Gyro {
  namespace Object {

    CollisionCapsule::CollisionCapsule(ObjectBase& owner, AppMath::Vector4 center, float line, float radius) : CollisionBase(owner) {
      // 各種パラメータの設定
      _position = center; 
      _length = line;
      // 線分の調整を行う
      _radius = radius;
    }

    void CollisionCapsule::Process(AppMath::Vector4 move) {
      // 前フレームの座標
      auto old = _position;
      // 新しい座標情報
      auto newPosition = _position + move;
      _position = newPosition;
      // ステージとの衝突判定を行う
    }

#ifdef _DEBUG
    void CollisionCapsule::Draw() {
      // 線分の取得(先端・終端)
      auto [start, end] = LineSegment().GetVector();
      // 指定座標にカプセルを描画する
      DrawCapsule3D(UtilityDX::ToVECTOR(start), UtilityDX::ToVECTOR(end), _radius, 10, 0, 0, false);
    }
#endif

    bool CollisionCapsule::IntersectLine(const AppMath::LineSegment& line) {
      // カプセルと線分の衝突判定
      return true;
    }

    bool CollisionCapsule::IntersectSphere(const CollisionSphere& sphere) {
      // カプセルと球の衝突判定
      return true;
    }

    bool CollisionCapsule::IntersectCapsule(const CollisionCapsule& capsule) {
      return false;
      //float distSq = LineSegment().MinDistSq(capsule.LineSegment());
      //auto sumRadius = _radius + capsule._radius;
      //return distSq <= (sumRadius * sumRadius);
    }

    bool CollisionCapsule::IntersectPlane(const AppFrame::Math::Plane& plane) {
      // 線分と平面は衝突しているか
      if (LineSegment().IntersectPlane(plane)) {
        return true; // 衝突している
      }
      return false;
    }

    AppMath::LineSegment CollisionCapsule::LineSegment() const {
      auto line = _length / 2;
      // 生成した線分を返す
      return AppMath::LineSegment(_position.AddVectorY(line), _position.AddVectorY(-line));
    }
  } // namespace Object
} // namespace Gyro
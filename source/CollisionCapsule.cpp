/*****************************************************************//**
 * @file   CollisionCapsule.cpp
 * @brief  コリジョンベースのサブクラス
 *         カプセルの衝突判定クラスの定義
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
      // DrawFormatString(0, 500, 0, "コリジョンx:%f, y:%f, z:%f", _position.GetX(), _position.GetY(), _position.GetZ());
    }
#endif

    bool CollisionCapsule::IntersectLine(const AppMath::LineSegment& line) {
      // カプセルと線分の衝突判定
      return true;
    }

    bool CollisionCapsule::IntersectSphere(const CollisionSphere& sphere) {
      // 球の半径を取得
      auto sphereRadius = sphere.Radius();
      auto spherePos = sphere.GetPosition();
      // 球の高さを線分に変換
      AppMath::LineSegment lengthSphere(spherePos.AddVectorY(-sphereRadius), spherePos.AddVectorY(sphereRadius));
      float dist = LineSegment().MinDist(lengthSphere);
      // 半径
      auto sumRadius = _radius + sphereRadius;
      auto sr = sumRadius * sumRadius;
      return dist <= sr;
    }

    bool CollisionCapsule::IntersectCapsule(const CollisionCapsule& capsule) {
      // 線分間の最短距離を取得
      float dist = LineSegment().MinDist(capsule.LineSegment());
      // 半径
      auto sumRadius = _radius + capsule._radius;
      auto sr = sumRadius * sumRadius;
      return dist <= sr;
    }

    bool CollisionCapsule::IntersectPlane(const AppFrame::Math::Plane& plane) {
      // 線分と平面は衝突しているか
      if (LineSegment().IntersectPlane(plane)) {
        return true; // 衝突している
      }
      return false;
    }

    AppMath::LineSegment CollisionCapsule::LineSegment() const {
      // 生成した線分を返す
      return AppMath::LineSegment(_position.AddVectorY(_length), _position);
    }
  } // namespace Object
} // namespace Gyro
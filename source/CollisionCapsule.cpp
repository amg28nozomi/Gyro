/*****************************************************************//**
 * @file   CollisionCapsule.cpp
 * @brief  
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "CollisionCapsule.h"
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
      // ステージとの衝突判定を行う
    }

#ifdef _DEBUG
    void CollisionCapsule::Draw() {
      // 線分の取得(先端・終端)
      auto [start, end] = Line().GetVector();
      // 球を描画する
      DrawCapsule3D(UtilityDX::ToVECTOR(start), UtilityDX::ToVECTOR(end), _radius, 10, 0, 0, false);
    }
#endif

    bool CollisionCapsule::IntersectLine(const AppMath::Line& line) {
      // カプセルと線分の衝突判定

    }

    bool CollisionCapsule::IntersectSphere(const CollisionSphere& sphere) {
      // カプセルと球の衝突判定

    }

    bool CollisionCapsule::IntersectCapsule(const CollisionCapsule& capsule) {
      // カプセルとカプセルの衝突判定

    }

    AppMath::Line CollisionCapsule::Line() const {
      auto line = _length / 2;
      // 生成した線分を返す
      return AppMath::Line(_position.AddVectorY(line), _position.AddVectorY(-line));
    }
  } // namespace Object
} // namespace Gyro
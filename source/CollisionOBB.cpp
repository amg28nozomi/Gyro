/*****************************************************************//**
 * @file   CollisionOBB.cpp
 * @brief  有向バウンディングボックスの衝突判定クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "CollisionOBB.h"

namespace Gyro {
  namespace Object {

    CollisionOBB::CollisionOBB(ObjectBase& owner, AppMath::Vector4 position, AppMath::Vector4 rotation, AppMath::Vector4 scale) : CollisionBase(owner) {
      // 引数を基にワールド座標行列を取得
      _matrix = AppMath::Utility::ToWorldMatrix(position, rotation, scale);
      // 逆行列を取得
      auto inverse = AppMath::Matrix44::Inverse(_matrix);
    }

    bool CollisionOBB::CheckLineSegment(const AppMath::LineSegment& segment) {
      // 線分に対して逆行列を適応
      auto pos = _inverse * segment.GetStart();
      auto end = _inverse * segment.GetEnd();
      return false;
    }
  } // namespace Object
} // namespace Gyro
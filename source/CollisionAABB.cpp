/*****************************************************************//**
 * @file   CollisionAABB.cpp
 * @brief  軸平行バウンディングボックスの衝突判定クラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "CollisionAABB.h"

namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {

    CollisionAABB::CollisionAABB(ObjectBase& owner, const AppMath::Vector4& min, const AppMath::Vector4& max) : CollisionBase(owner) {
      _position = min; // 最小点
      _max = max;      // 最大点
    }

    void CollisionAABB::Process(const AppMath::Vector4& point) {
      // 点座標ベクトルを分解
      const auto [x, y, z, w] = point.GetVector4();
      // Utilityに別名定義
      using Utility = AppMath::Utility;
      // 各成分毎に更新を行う
      _position.SetX(Utility::Min(_position.GetX(), x));
      _position.SetY(Utility::Min(_position.GetY(), y));
      _position.SetZ(Utility::Min(_position.GetZ(), z));
      _max.SetX(Utility::Max(_max.GetX(), x));
      _max.SetY(Utility::Max(_max.GetY(), y));
      _max.SetZ(Utility::Max(_max.GetZ(), z));
    }

    bool CollisionAABB::CheckPoint(const AppMath::Vector4& point) {
      auto side = point.GetX() < _position.GetX() ||
        point.GetY() < _position.GetY() ||
        point.GetZ() < _position.GetZ() ||
        _max.GetX() < point.GetX() ||
        _max.GetY() < point.GetY() ||
        _max.GetZ() < point.GetZ();
      return !side;
    }

    bool CollisionAABB::CheckLineSegment(const AppMath::LineSegment& segment) {
      // 向きベクトルを取得
      auto v = segment.Segment();
      using Vector4 = AppMath::Vector4;
      // 長さがない
      if (Vector4::NearZero(v)) {
        return false;
      }



      return false;
    }
  } // namespace Object
} // namespace Gyro
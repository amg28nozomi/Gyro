/*****************************************************************//**
 * @file   Plane.cpp
 * @brief  平面クラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "Plane.h"

namespace AppFrame{
  namespace Math {

    Plane::Plane(const Vector4& a, const Vector4& b, const Vector4& c) {
      auto ab = b - a;
      auto ac = c - a;
      // 計算したベクトルを元に法線を算出する
      _normal = Vector4::Cross(ab, ac);
      _normal.Normalize();
      _mDistance = -Vector4::Dot(a, _normal);
    }

    float Plane::SignedDist(const Vector4& point) const {
      return Vector4::Dot(point, _normal) - _mDistance;
    }
  }
} // namespace AppFrame
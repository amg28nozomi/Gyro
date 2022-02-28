/*****************************************************************//**
 * @file   Circle.cpp
 * @brief  円クラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "Circle.h"

namespace AppFrame {
  namespace Math {

    Circle::Circle(const Vector4& center, const float radius) {
      _center = center;
      _radius = radius;
    }

    void Circle::Process(const Vector4& move) {
      _center.Add(move); // 中心座標に移動量を加算する
    }

  } // namespace Math
} // namespaece AppFrame
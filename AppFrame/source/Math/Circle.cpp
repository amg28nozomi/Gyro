/*****************************************************************//**
 * @file   Circle.cpp
 * @brief  �~�N���X�̒�`
 * 
 * @author ��؊�C
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
      _center.Add(move); // ���S���W�Ɉړ��ʂ����Z����
    }

  } // namespace Math
} // namespaece AppFrame
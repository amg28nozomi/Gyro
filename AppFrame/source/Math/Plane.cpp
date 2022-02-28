/*****************************************************************//**
 * @file   Plane.cpp
 * @brief  ���ʃN���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "Plane.h"

namespace AppFrame{
  namespace Math {

    Plane::Plane(const Vector4& a, const Vector4& b, const Vector4& c) {
      auto ab = b - a;
      auto ac = c - a;
      // �v�Z�����x�N�g�������ɖ@�����Z�o����
      _normal = Vector4::Cross(ab, ac);
      _normal.Normalize();
      _mDistance = -Vector4::Dot(a, _normal);
    }

    float Plane::SignedDist(const Vector4& point) const {
      return Vector4::Dot(point, _normal) - _mDistance;
    }
  }
} // namespace AppFrame
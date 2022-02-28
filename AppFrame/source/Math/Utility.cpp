/*****************************************************************//**
 * @file   Utility.cpp
 * @brief  �Z�p�����p�̕⏕�@�\�N���X�̒�`
 *
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "Utility.h"
#include "Matrix44.h"
#include "Vector4.h"

namespace AppFrame{
  namespace Math {

    template <typename T>
    static T Utility::Min(const T a, const T b) {
      return a;
    }

    template <>
    static float Utility::Min(const float a, const float b) {
      return (a < b) ? a : b;
    }

    template <>
    static int Utility::Min(const int a, const int b) {
      return (a < b) ? a : b;
    }

    template <typename T>
    static T Utility::Max(const T a, const T b) {
      return a;
    }

    template<>
    static int Utility::Max(const int a, const int b) {
      return (b < a) ? a : b;
    }

    template<>
    static float Utility::Max(const float a, const float b) {
      return (b < a) ? a : b;
    }

    Matrix44 Utility::ToWorldMatrix(const Vector4& position, Vector4 rotation, const Vector4& scale, const bool angle) {
      // rotation���f�O���[�l�̏ꍇ�̓��W�A���l�ɕϊ�����
      if (angle) {
        rotation = RotationToRadian(rotation);
      }
      // �P�ʍs��̎擾
      auto worldMatrix = Matrix44::Identity();
      worldMatrix.MulScaling(scale); // �X�P�[�����O
      worldMatrix.RotateZ(rotation.GetZ()); // Z����]
      worldMatrix.RotateY(rotation.GetY()); // Y����]
      worldMatrix.RotateX(rotation.GetX()); // X����]
      worldMatrix.MulTranslate(position); // ���s�ړ�
      return worldMatrix;
    }

    float Utility::ToPlus(float value) {
      // �Ώۂ�0�����̏ꍇ�͐����ɒ������l��Ԃ�
      return (value < 0.0f) ? value * -1.0f : value;
    }

    Vector4 Utility::RotationToRadian(const Vector4& rotation) {
      // �e�퐬���̎擾
      auto [x, y, z] = rotation.GetVector3();
      // �e���������W�A���ɕϊ�����
      x = DegreeToRadian(x);
      y = DegreeToRadian(y);
      z = DegreeToRadian(z);
      return Vector4(x, y, z);
    }
  } // namespace Math
} // namespace AppFrame
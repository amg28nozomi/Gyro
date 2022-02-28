/*****************************************************************//**
 * @file   Utility.cpp
 * @brief  算術処理用の補助機能クラスの定義
 *
 * @author 鈴木希海
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
      // rotationがデグリー値の場合はラジアン値に変換する
      if (angle) {
        rotation = RotationToRadian(rotation);
      }
      // 単位行列の取得
      auto worldMatrix = Matrix44::Identity();
      worldMatrix.MulScaling(scale); // スケーリング
      worldMatrix.RotateZ(rotation.GetZ()); // Z軸回転
      worldMatrix.RotateY(rotation.GetY()); // Y軸回転
      worldMatrix.RotateX(rotation.GetX()); // X軸回転
      worldMatrix.MulTranslate(position); // 平行移動
      return worldMatrix;
    }

    float Utility::ToPlus(float value) {
      // 対象が0未満の場合は正数に直した値を返す
      return (value < 0.0f) ? value * -1.0f : value;
    }

    Vector4 Utility::RotationToRadian(const Vector4& rotation) {
      // 各種成分の取得
      auto [x, y, z] = rotation.GetVector3();
      // 各成分をラジアンに変換する
      x = DegreeToRadian(x);
      y = DegreeToRadian(y);
      z = DegreeToRadian(z);
      return Vector4(x, y, z);
    }
  } // namespace Math
} // namespace AppFrame
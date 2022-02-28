/*****************************************************************//**
 * @file   Vector4.cpp
 * @brief  四次元ベクトルクラスの定義
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#include "Vector4.h"
#include <cmath>

namespace AppFrame {
  namespace Math {

    Vector4::Vector4() : _x(0), _y(0), _z(0), _w(1.0) {
    }

    Vector4::Vector4(float x, float y) {
      _x = x;
      _y = y;
      _z = 0;
      _w = 0;
    }

    Vector4::Vector4(int x, int y) {
      _x = static_cast<float>(x);
      _y = static_cast<float>(y);
      _z = 0;
      _w = 0;
    }

    Vector4::Vector4(float x, float y, float z, float w) {
      _x = x;
      _y = y;
      _z = z;
      _w = w;
    }

    void Vector4::Zero() {
      Fill(0); // 各種成分を0にする
    }

    void Vector4::Add(const Vector4 vector) {
      _x += vector._x;
      _y += vector._y;
      _z += vector._z;
    }

    void Vector4::Add(const float x, const float y, const float z) {
      _x += x;
      _y += y;
      _z += z;
    }

    void Vector4::Scale(const Vector4& vector) {
      _x *= vector._x;
      _y *= vector._y;
      _z *= vector._z;
    }

    Vector4 Vector4::Scale(const Vector4& left, const Vector4& right) {
      return Vector4(left._x * right._x, left._y * right._y, left._z * right._z);
    }

    Vector4 Vector4::AddVectorX(const float x) const {
      return Vector4(_x + x, _y, _z);
    }

    Vector4 Vector4::AddVectorY(const float y) const {
      return Vector4(_x, _y + y, _z);
    }

    Vector4 Vector4::AddVectorZ(const float z) const {
      return Vector4(_x, _y, _z + z);
    }

    void Vector4::Sub(const Vector4 vector) {
      _x -= vector._x;
      _y -= vector._y;
      _x -= vector._z;
    }

    void Vector4::Sub(const float x, const float y, const float z) {
      _x -= x;
      _y -= y;
      _z -= z;
    }

    void Vector4::Set(const Vector4 vector) {
      _x = vector.GetX();
      _y = vector.GetY();
      _z = vector.GetZ();
      _w = vector.GetW();
    }

    void Vector4::Set(const float x, const float y, const float z) {
      _x = x;
      _y = y;
      _z = z;
    }

    Vector4 Vector4::operator+(const Vector4& vector) const {
      auto x = _x + vector._x;
      auto y = _y + vector._y;
      auto z = _z + vector._z;
      return Vector4(x, y, z);
    }

    Vector4 Vector4::operator-(const Vector4& vector) const {
      auto [x, y, z] = vector.GetVector3();
      return Vector4(_x - x, _y - y, _z - z);
    }

    Vector4 Vector4::operator*(const float scalar) const {
      auto x = _x * scalar;
      auto y = _y * scalar;
      auto z = _z * scalar;
      return Vector4(x, y, z);
    }

    Vector4 Vector4::operator/(const float scalar) const {
      auto x = _x / scalar;
      auto y = _y / scalar;
      auto z = _z / scalar;
      return Vector4(x, y, z);
    }

    float Vector4::Length() const {
      return std::sqrt(_x * _x + _y * _y + _z * _z);
    }

    float Vector4::Length(const Vector4& vector) {
      auto [x, y, z] = vector.GetVector3();
      return std::sqrt(x * x + y * y + z * z);
    }

    float Vector4::Length2D() const {
      return std::sqrt(_x * _x + _y * _y);
    }

    float Vector4::LengthSquared() const {
      return _x * _x + _y * _y + _z * _z;
    }

    float Vector4::LengthSquared(const Vector4& vector) {
      auto [x, y, z] = vector.GetVector3();
      return x * x + y * y + z * z;
    }

    float Vector4::LengthSquared2D() const {
      return _x * _x + _y * _y;
    }

    void Vector4::Normalize() {
      // 全ての値が0の場合
      if (LengthSquared() == 0.0f) {
        Zero();
        return;
      }
      auto length = Length();
      _x /= length;
      _y /= length;
      _z /= length;
    }

    Vector4 Vector4::Normalize(const Vector4& vector) {
      // 元から長さが0の場合は空のベクトルを返す
      if (vector.LengthSquared() == 0.0f) {
        return Vector4();
      }
      auto length = vector.Length();
      auto x = vector._x / length;
      auto y = vector._y / length;
      auto z = vector._z / length;
      return Vector4(x, y, z);
    }

    float Vector4::Dot(const Vector4& vector) const {
      return _x * vector._x + _y * vector._y + _z * vector._z;
    }

    float Vector4::Dot(const Vector4& right, const Vector4& left) {
      return right.Dot(left);
    }

    Vector4 Vector4::Cross(const Vector4& vector) const {
      auto x = _y * vector._z - _z * vector._y;
      auto y = _z * vector._x - _x * vector._z;
      auto z = _x * vector._y - _y * vector._x;
      return Vector4(x, y, z);
    }

    Vector4 Vector4::Cross(const Vector4& left, const Vector4& right) {
      return left.Cross(right);
    }

    bool Vector4::IsParallel(const Vector4& left, const Vector4& right) {
      return Cross(left, right).LengthSquared() == 0.1f;
    }

    void Vector4::Fill(const float value) {
      _x = value;
      _y = value;
      _z = value;
    }

    bool Vector4::NearZero(const Vector4& vector) {
      return vector.LengthSquared() == 0.0f;
    }

    Vector4 Vector4::Direction(const Vector4& vector) const {
      return vector - *this;
    }
  }
}
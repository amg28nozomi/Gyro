/*****************************************************************//**
 * @file   Vector4.h
 * @brief  �l�����x�N�g���N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <tuple>

/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �Z�p�x�[�X
   */
  namespace Math {

    class Matrix44;
    /**
     * @class Vector4
     * @brief �l�����x�N�g��
     */
    class Vector4 {
    public:
      /**
       * @brief ��x�N�g���̐���
       */
      Vector4();
      /**
       * @brief 2�����x�N�g���̐���
       * @param x x����
       * @param y y����
       */
      Vector4(float x, float y);
      /**
       * @brief �^�ϊ������L��
       * @param x x����(����)
       * @param y y����(����)
       */
      Vector4(int x, int y);
      /**
       * @brief �x�N�g���̐���
       * @param x x����
       * @param y y����
       * @param z z����
       * @param w w����(�f�t�H���g�ł�1.0)
       */
      Vector4(float x, float y, float z, float w = 1.0);
      /**
       * @brief �[���x�N�g����
       */
      void Zero();
      /**
       * @brief �x�N�g�����m�̉��Z
       * @param vector �x�N�g��(����)
       */
      void Add(const Vector4 vector);
      /**
       * @brief �x�N�g���̉��Z
       * @param x x����
       * @param y y����
       * @param z z����
       */
      void Add(const float x, const float y, const float z);
      /**
       * @brief �x�N�g�����m�̌��Z
       * @param vector �x�N�g��(����)
       */
      void Sub(const Vector4 vector);
      /**
       * @brief �x�N�g���̌��Z
       * @param x x����
       * @param y y����
       * @param z z����
       */
      void Sub(const float x, const float y, const float z);
      /**
       * @brief �x�N�g�����m�̊e��������Z����
       * @param vector �Ώۃx�N�g��
       */
      void Scale(const Vector4& vector);
      /**
       * @brief  �x�N�g�����m�̊e��������Z����
       * @param  left  ����
       * @param  rigth �E��
       * @return ��Z�����x�N�g��
       */
      static Vector4 Scale(const Vector4& left, const Vector4& right);
      /**
       * @brief �x�N�g���̐ݒ�
       * @param vector �Z�b�g����x�N�g��
       */
      void Set(const Vector4 vector);
      /**
       * @brief �w�肵���l���x�N�g���ɃZ�b�g����
       * @param x x�����ɃZ�b�g����l
       * @param y y�����ɃZ�b�g����l
       * @param z z�����ɃZ�b�g����l
       */
      void Set(const float x, const float y = 0.0f, const float z = 0.0f);
      /**
       * @brief �w�肵���l��x�����ɃZ�b�g����
       * @param x
       */
      inline void SetX(const float x) {
        _x = x;
      }
      /**
       * @brief �w�肵���l��y�����ɃZ�b�g����
       * @param y �Z�b�g����l
       */
      inline void SetY(const float y) {
        _y = y;
      }
      /**
       * @brief �w�肵���l��z�����ɃZ�b�g����
       * @param z �Z�b�g����l
       */
      inline void SetZ(const float z) {
        _z = z;
      }
      /**
       * @brief x�����̉��Z
       * @param x ����
       */
      inline void AddX(const float x) {
        _x += x;
      }
      /**
       * @brief  x�����݂̂����Z�����x�N�g���̎擾
       * @param  x x�����ɉ��Z����l
       * @return x�����݂̂����Z�����x�N�g��
       */
      Vector4 AddVectorX(const float x) const;
      /**
       * @brief  y�����݂̂����Z�����x�N�g���̎擾
       * @param  y y�����ɉ��Z����l
       * @return y�����݂̂����Z�����x�N�g��
       */
      Vector4 AddVectorY(const float y) const;
      /**
       * @brief  z�����݂̂����Z�����x�N�g���̎擾
       * @param  z z�����ɉ��Z����l
       * @return z�����݂̂����Z�����x�N�g��
       */
      Vector4 AddVectorZ(const float z) const;
      /**
       * @brief y�����̉��Z
       * @param x ����
       */
      inline void AddY(const float y) {
        _y += y;
      }
      /**
       * @brief z�����̉��Z
       * @param z ����
       */
      inline void AddZ(const float z) {
        _z += z;
      }
      /**
       * @brief  2�����x�N�g���̎擾
       * @return xy������Ԃ�
       */
      inline const std::pair<float, float> GetVector2() const {
        return {_x, _y};
      }
      /**
       * @brief  3�����x�N�g���̎擾
       * @return xyz������Ԃ�
       */
      inline const std::tuple<float, float, float> GetVector3() const {
        return {_x, _y, _z};
      }
      /**
       * @brief  4�����x�N�g���̎擾
       * @return xyzw����
       */
      inline const std::tuple<float, float, float, float> GetVector4() const {
        return {_x, _y, _z, _w};
      }
      /**
       * @brief  x�����̎擾
       * @return x����
       */
      inline const float GetX() const {
        return _x;
      }
      /**
       * @brief  y�����̎擾
       * @return y����
       */
      inline const float GetY() const {
        return _y;
      }
      /**
       * @brief  z�����̎擾
       * @return z����
       */
      inline const float GetZ() const {
        return _z;
      }
      /**
       * @brief  w�����̎擾
       * @return w����
       */
      inline const float GetW() const {
        return _w;
      }
      /**
       * @brief  �x�N�g���̒����̎擾
       * @return �x�N�g���̒���
       */
      float Length() const;
      /**
       * @brief  �w�肵���x�N�g���̒������擾
       * @param  vector �x�N�g��
       * @return �Ώۃx�N�g���̒���
       */
      static float Length(const Vector4& vector);
      /**
       * @brief  �x�N�g���̒����̎擾(2����)
       * @return �x�N�g���̒���
       */
      float Length2D() const;
      /**
       * @brief  �x�N�g���̒����̓��̎擾
       * @return �x�N�g���̒����̓��
       */
      float LengthSquared() const;
      /**
       * @brief  �w�肵���x�N�g���̒����̓����擾
       * @param  vector �x�N�g��
       * @return �Ώۃx�N�g���̒����̓��
       */
      static float LengthSquared(const Vector4& vector);
      /**
       * @brief  �x�N�g���̒����̓��̎擾(�񎟌�)
       * @return �x�N�g���̒����̓��(�񎟌�)
       */
      float LengthSquared2D() const;
      /**
       * @brief  �x�N�g���̐��K��
       */
      void Normalize();
      /**
       * @brief  �P�ʃx�N�g���̎擾
       * @param  vector �x�N�g��
       * @return �P�ʃx�N�g��
       */
      static Vector4 Normalize(const Vector4& vector);
      /**
       * @brief  �x�N�g�����m�̓���
       * @param  vector �x�N�g��
       * @return ����
       */
      float Dot(const Vector4& vecotr) const;
      /**
       * @brief  �x�N�g�����m�̓���
       * @param  left �x�N�g��(����)
       * @param  right �x�N�g��(�E��)
       * @return ����
       */
      static float Dot(const Vector4& right, const Vector4& left);
      /**
       * @brief  �x�N�g���̊O��
       * @param  vector �x�N�g��
       * @return �x�N�g��
       */
      Vector4 Cross(const Vector4& vector) const;
      /**
       * @brief  �x�N�g���̊O�ς����߂�
       * @param  left  �x�N�g��
       * @param  right �x�N�g��
       * @return �O��
       */
      static Vector4 Cross(const Vector4& left, const Vector4& right);
      /**
       * @brief  �x�N�g�����m�����s���̔���
       * @param  left  �x�N�g��
       * @param  right �x�N�g��
       * @return true:���s�ł��� false:���s�ł͂Ȃ�
       */
      static bool IsParallel(const Vector4& left, const Vector4& right);
      /**
       * @brief  �w�肵���l��xyz�����ɑ������
       * @param  value �l
       */
      void Fill(const float value);
      /**
       * @brief  �Ώۂ̃x�N�g����0���̔���
       * @param  vector �x�N�g��
       * @return true:�[�� false:�[���ł͂Ȃ�
       */
      static bool NearZero(const Vector4& vector);
      /**
       * @brief  ������x�N�g���̎擾
       * @return ������x�N�g��
       */
      static inline Vector4 Up() {
        return Vector4(0.0f, 1.0f, 0.0f);
      }
      /**
       * @brief  �Ώۂւƌ������x�N�g���̎擾
       * @param  vector �Ώۃx�N�g��
       * @return �����x�N�g��
       */
      Vector4 Direction(const Vector4& vector) const;
      /**
       * @brief  �x�N�g�����m�̉��Z
       * @param  vector �x�N�g��(����)
       * @return ���Z����4�����x�N�g��
       */
      Vector4 operator + (const Vector4& vector) const;
      /**
       * @brief  �x�N�g�����m�̌��Z
       * @param  vector �x�N�g��(����)
       * @return ���Z����4�����x�N�g��
       */
      Vector4 operator - (const Vector4& vector) const;
      /**
       * @brief  �x�N�g���̃X�J���[�{
       * @param  scalar �X�J���[�l
       * @return �X�J���[�{����4�����x�N�g��
       */
      Vector4 operator * (const float scalar) const;
      /**
       * @brief  �x�N�g���̃X�J���[����
       * @param  scalar �X�J���[�l
       * @return �X�J���[���肵��4�����x�N�g��
       */
      Vector4 operator/(const float scalar) const;
    private:
      float _x; //!< x����
      float _y; //!< y����
      float _z; //!< z����
      float _w; //!< w����
    };
  } // namespace Math
} // namespace AppFrame
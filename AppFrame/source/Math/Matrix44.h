/*****************************************************************//**
 * @file   Matrix44.h
 * @brief  4*4�s��N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <array>

/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �Z�p�x�[�X
   */
  namespace Math {
    class Vector4;
    constexpr auto MaxRow = 4;    //!< �s�̏��
    constexpr auto MaxColumn = 4; //!< ��̏��
    /**
     * @class Matrix4x4
     * @brief 4*4�s��N���X
     */
    class Matrix44 {
    private:
      /** float�^��4*4�s���\��2�����z�� */
      using MatrixArray = std::array<std::array<float, MaxColumn>, MaxRow>;
    public:
      /**
       * @brief ��̍s��𐶐�
       */
      Matrix44();
      /**
       * @brief �s��̃R�s�[
       * @param values 
       */
      Matrix44(const MatrixArray values);
      /**
       * @brief �s��̍폜
       */
      ~Matrix44() = default;
      /**
       * @brief  �s��̍Đݒ�
       * @param  matrix �s��N���X�̎Q��
       * @return �����������s���Ԃ�
       */
      static void Reset(MatrixArray& matrix);
      /**
       * @brief
       * @param matrix
       * @return 
       */
      static Matrix44 Identity(const Matrix44& matrix);
      /**
       * @brief  �P�ʍs��̍쐬
       * @return �P�ʍs��
       */
      static Matrix44 Identity();
      /**
       * @brief  ���s�ړ��s��̎擾
       * @param  x x�������x�N�g��
       * @param  y y�������x�N�g��
       * @param  z z�����s�x�N�g��
       * @return ���s�ړ��s��
       */
      static Matrix44 Translate(float x, float y, float z);
      /**
       * @brief  �x�N�g���𕽍s�ړ��s��ɕϊ�����
       * @param  vector �Ώۃx�N�g��
       * @return ���s�ړ��s��
       */
      static Matrix44 Translate(const Vector4& vector);
      /**
       * @brief  �g��k���s��̎擾
       * @param  x
       * @param  y
       * @param  z
       * @return �g��k���s��
       */
      static Matrix44 Scaling(float x, float y, float z);
      /**
       * @brief  �x�N�g�����g��k���s��ɕϊ�����
       * @param  vector �x�N�g��
       * @return �g��k���s��
       */
      static Matrix44 Scaling(const Vector4& vector);
      /**
       * @brief �s��̕��s�ړ�
       * @param translate ���s�ړ��x�N�g��
       */
      void MulTranslate(const AppFrame::Math::Vector4 translate);
      /**
       * @brief �s��̃X�P�[�����O
       * @param scale �g�k�x�N�g��
       */
      void MulScaling(const AppFrame::Math::Vector4 scale);
      /**
       * @brief  ��]�s��(x��)
       * @param  radian �p�x(���W�A���l)
       */
      void RotateX(float angle);
      /**
       * @brief  ��]�s��(y��)
       * @param  radian �p�x(���W�A���l)
       */
      void RotateY(float radian);
      /**
       * @brief  ��]�s��(z��)
       * @param  radian �p�x(���W�A���l)
       */
      void RotateZ(float radian);
      /**
       * @brief  �s�񓯎m�̏�Z
       * @return 
       */
      Matrix44 operator* (const Matrix44 rhs) const;
      /**
       * @brief  �s��*�x�N�g���̏�Z
       * @param  vector �x�N�g��
       * @return 
       */
      Vector4 operator* (const Vector4& vector) const;
      /**
       * @brief  �w�肵���s��̒l���擾����
       * @param  row �s
       * @param  column ��
       * @return �w�肵���s��̒l
       */
      float GetValue(const int row, const int column) const;
      /**
       * @brief  �w�肵���s��̋t�s����擾����
       * @param  matrix �s��
       * @return �t�s��
       */
      static Matrix44 Inverse(const Matrix44 matrix);
      /**
       * @brief  �����s��̐���
       * @param  position �J�����̍��W
       * @param  target   �Ώە��̍��W
       * @param  up       ��x�N�g��
       * @return �����s��
       */
      static Matrix44 CreateLookAt(const Vector4 & position, const Vector4 & target, const Vector4 & up);
    private:
      MatrixArray _rowColumn; //!< �s��
    };
  } // namespace Math
} // namespace AppFrame
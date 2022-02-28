/*****************************************************************//**
 * @file   Plane.h
 * @brief  ���ʃN���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "Vector4.h"
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �Z�p�x�[�X
   */
  namespace Math {
    /**
     * @class Plane
     * @brief ���ʃN���X
     */
    class Plane {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param a �_A
       * @param b �_B
       * @param c �_C
       */
      Plane(const Vector4& a, const Vector4& b, const Vector4& c);
      /**
       * @brief  
       * @param  point
       * @return 
       */
      float SignedDist(const Vector4& point) const;
      /**
       * @brief  �@���̎擾
       * @return �@��
       */
      Vector4 GetNormal() const {
        return _normal;
      }
      /**
       * @brief  �ŒZ�����̎擾
       * @return �ŒZ����
       */
      float GetDistance() const {
        return _mDistance;
      }
    private:
      Vector4 _normal;  //!< �@��
      float _mDistance; //!<�ŒZ����
    };
  } // namespace Math
} // namespace AppFrame
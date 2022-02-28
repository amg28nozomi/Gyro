/*****************************************************************//**
 * @file   Circle.h
 * @brief  �~�̏��N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "Vector4.h"
/**
 * @brief �t���[�����[�N
 */
namespace AppFrame {
  /**
   * @brief �Z�p�x�[�X
   */
  namespace Math {
    /**
     * @class Circle
     * @brief �~�̏��N���X
     */
    class Circle {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param center ���S���W
       * @param radius ���a
       */
      Circle(const Vector4& center, const float radius);
      /**
       * @brief ���S���W�̍X�V
       * @param move �ړ���
       */
      void Process(const Vector4& move);
      /**
       * @brief  ���S���W�̎擾
       * @return ���S���W
       */
      Vector4 GetCenter() const {
        return _center;
      }
      /**
       * @brief  ���a�̎擾
       * @return ���a
       */
      float GetRadius() const {
        return _radius;
      }
    private:
      Vector4 _center; //!< ���S���W
      float _radius;   //!< ���a
    };
  } // namespace Math
} // namespaece AppFrame
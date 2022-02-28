/*****************************************************************//**
 * @file   GravityBase.h
 * @brief  �d�͏������s���ÓI�N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �Z�p�x�[�X
   */
  namespace Math {
    class Matrix44; //!< �O���錾
    constexpr auto DefaultAcceleration = -9.8f; //!< �f�t�H���g�̏d�͉����x
    /**
     * @class GravityBase
     * @brief �d�͂̊��N���X
     */
    class GravityBase {
    public:
      /**
       * @brief  �d�̓X�P�[���̎擾
       * @param  speed �Ώۂ̉����x
       * @param  mass  �Ώۂ̎���
       * @return �Ώۂ̏d�̓X�P�[��
       */
      static float GravityScale(float speed, float mass);
      /**
       * @brief  �d�͉����x�̐ݒ�
       * @param  scale �ݒ肷������x
       */
      static void SetScale(const float scale) {
        _acceleration;
      }
      /**
       * @brief  �d�͉����x�̎擾
       * @return �d�͉����x
       */
      static inline float Acceleration() {
        return _acceleration;
      }
    protected:
      static inline float _acceleration{DefaultAcceleration}; //!< �d�͉����x
    };
  } // namespace Math
} // namespace AppFrame
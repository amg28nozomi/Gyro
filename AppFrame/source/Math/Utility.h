/*****************************************************************//**
 * @file   Utility.h
 * @brief  �Z�p�����p�̕⏕�@�\�N���X
 *
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <numbers>
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �Z�p�����x�[�X
   */
  namespace Math {
    class Vector4;  // �O���錾
    class Matrix44; // �O���錾
    constexpr auto Degree = true;  //!< �f�O���[�t���O
    constexpr auto Radian = false; //!< ���W�A���t���O
    /**
     * @class Utility
     * @brief �Z�p�����p�̕⏕�@�\���܂Ƃ߂��N���X
     */
    class Utility {
    public:
      //!< �~����PI�̒萔
      static constexpr float _pi{ static_cast<float>(std::numbers::pi) };
      //!< 
      static constexpr float _degrees180{ 180.0f };
      /**
       * @brief  ��̒l���r���čŏ��l��Ԃ�
       * @tparam T ��r����f�[�^�̌^
       * @param  a ����1
       * @param  b ����2
       * @return �ŏ��l
       */
      template <typename T>
      static T Min(const T a, const T b);
      /**
       * @brief  ��̒l���r���čő�l��Ԃ�
       * @tparam T ��r����f�[�^�̌^
       * @param  a ����1
       * @param  b ����2
       * @return   �ő�l
       */
      template <typename T>
      static T Max(const T a, const T b);
      /**
       * @brief  ���[���h���W�ϊ�
       * @param  position ���[�J�����W
       * @param  rotatin  ��]�x�N�g��
       * @param  scale    �X�P�[��
       * @param  angle    ���[�e�[�V�����t���O(true:�f�O���[�l false:���W�A���l)
       * @return ���[���h���W
       */
      static Matrix44 ToWorldMatrix(const Vector4& position, Vector4 rotation, const Vector4& scale , const bool angle = Radian);
      /**
       * @brief  �Ώۂ̒l�𐳐��ɕϊ�����
       * @param  value �ϊ��Ώ�
       * @return �����𐳐��ɕϊ������l
       */
      static float ToPlus(float value);
      /**
       * @brief  �f�O���[�l�����W�A���l�ɕϊ�����
       * @param  degree �f�O���[�l
       * @return ���W�A���l
       */
      static inline float DegreeToRadian(float degree) {
        return degree * _pi / _degrees180;
      }
      /**
       * @brief  ���W�A���l���f�O���[�l�ɕϊ�����
       * @param  radian ���W�A���l
       * @return �f�O���[�l
       */
      static inline float RadianToDegree(float radian) {
        return radian * _degrees180 / _pi;
      }
      /**
       * @brief  ��]�x�N�g��(�f�O���[�l)�̊e���������W�A���l�ɕϊ�����
       * @param  rotation ��]�x�N�g��(�f�O���[�l)
       * @return �e���������W�A���l�ɕϊ������x�N�g����Ԃ�
       */
      static Vector4 RotationToRadian(const Vector4& rotation);
    };
  } // namespace Math
} // namespace AppFrame
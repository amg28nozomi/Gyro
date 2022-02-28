/*****************************************************************//**
 * @file   Arithmetic.h
 * @brief  �Z�p�����N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <string>
#include <vector>

/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �Z�p�x�[�X
   */
  namespace Math {
    constexpr auto Binary = 2;       //!< 2�i��
    constexpr auto Decimal = 10;     //!< 10�i��
    constexpr auto Hexadecimal = 16; //!< 16�i��
    /**
     * @class Arithmetic
     * @brief �Z�p�����p�N���X
     */
    class Arithmetic {
    public:
      /**
       * @brief  �����l�̃N�����v����
       * @param  value  �N�����v����l
       * @param  low    ����
       * @param  height ���
       * @return �N�����v�����l
       * @throw  std::logic_error std::invalid_argument
       */
      static int Clamp(const int value, const int low, const int height);
      /**
       * @brief  
       * @param  value  �P���x���������_����
       * @param  low    �N�����v����
       * @param  height �N�����v���
       * @return �N�����v�����l
       */
      static float Clamp(const float value, const float low, const float height);
      /**
       * @brief  �Ώۂ̐����l���͈͓��Ɏ��܂��Ă��邩�̔���
       * @param  value  �Ώےl
       * @param  low    ����
       * @param  height ���
       * @return true:�͈͓��Ɏ��܂��Ă��� false:�͈͊O
       */
      static bool IsRange(const int value, const int low, const int height);
      /**
       * @brief  �Ώۂ�float�l���͈͓��Ɏ��܂��Ă��邩�̔���
       * @param  value  �Ώےl
       * @param  low    ����
       * @param  height ���
       * @return true:�͈͓��Ɏ��܂��Ă��� false:�͈͊O
       */
      static bool IsRange(const float value, const float low, const float height);
      /**
       * @brief  ��̒l�̒������擾
       * @param  x �l1
       * @param  y �l2
       * @return ����
       */
      static float Length(const float x, const float y);
      /**
       * @brief  ��̒l�̒����̓����擾
       * @param  x �l1
       * @param  y �l2
       * @return �����̓��
       */
      static float LengthSquared(const float x, const float y);
      /**
       * @brief  �w�肵�������l���������̔���
       * @param  value ����Ώ�
       * @return true:���� false:�����ł͂Ȃ�
       */
      static bool IsPositive(const int value);
      /**
       * @brief  10�i���l��2�i���l�ɕϊ�
       * @param  num 10�i���l
       * @return ������2�i���ŕ\����������
       */
      static std::string ToBinary(int num);
      /**
       * @brief  10�i���l��16�i���l�ɕϊ�
       * @param  num  10�i���l
       * @param  flag true:������Ŏ擾(�f�t�H���g) false:�����l�Ŏ擾 
       * @return num��16�i���ɕϊ������l
       */
      static std::string ToHexadecimal(int num);
      /**
       * @brief  �����������int�^�̐��l�ɕϊ�����
       * @param  num ����������
       * @return ���l
       */
      static int ToInteger(std::string_view num);
      /**
       * @brief  �N�����v�����ɑΉ����Ă���^�̎擾
       * @return �Ή����Ă���^�𕶎���ŕێ�����R���e�i
       */
      static inline auto GetClampType() {
        return _clampType;
      }
      /**
       * @brief  ������0���̔���
       * @param  value �l
       * @return true:0 false:0�ł͂Ȃ�
       */
      static inline bool NearZero(const float value) {
        return value == 0.0f;
      }
    private:
      static std::vector<std::string> _clampType; //!< Clamp���\�b�h�ɑΉ����Ă���^
      /**
       * @brief  �]����w�肵��16�i��������ɕϊ�����
       * @param  remainder ��]
       * @return 16�i��������
       */
      static std::string ToRemainder16(const int remainder);
    };
  } // namespace Math
} // namespace AppFrame
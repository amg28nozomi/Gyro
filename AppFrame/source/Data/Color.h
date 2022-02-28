/*****************************************************************//**
 * @file   Color.h
 * @brief  RGBA�J���[���f���N���X
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
   * @brief �f�[�^�x�[�X
   */
  namespace Data {
    constexpr auto MaxColor = 255; //!< �F�̏��
    constexpr auto MinColor = 0;   //!< �F�̉���
    /**
     * @class Color
     * @brief RGBA�J���[���
     */
    class Color {
    public:
      /**
       * @brief RGBA�J���[���̐ݒ�
       */
      Color();
      /**
       * @brief RGBA�J���[���̐���
       * @param red   ��
       * @param green ��
       * @param blue  ��
       * @param alpha ���ߓx(�f�t�H���g�ł�255)
       */
      Color(const int red, const int green, const int blue, const int alpha = MaxColor);
      /**
       * @brief �J���[���̐ݒ�
       * @param red   �P�x(��)
       * @param green �P�x(��)
       * @param blue  �P�x(��)
       * @param alpha �����x(�f�t�H���g�ł�255)
       */
      void SetColor(const int red, const int green, const int blue, const int alpha = MaxColor);
      /**
       * @brief �����x�̐ݒ�
       * @param alpha �����x
       */
      void SetAlpha(const int alpha);
      /**
       * @brief �P�x�̉��Z����
       * @param red   ��
       * @param green ��
       * @param blue  ��
       */
      void AddColor(const int red = MinColor, const int green = MinColor, const int blue = MinColor);
      /**
       * @brief ���l�̉��Z
       * @param add ����
       */
      void AddAlpha(const int add);
      /**
       * @brief �P�x�̌��Z����
       * @param red   ��
       * @param green ��
       * @param blue  ��
       */
      void SubColor(const int red = MinColor, const int green = MinColor, const int blue = MinColor);
      /**
       * @brief �����x�̌��Z����
       * @param sub ����
       */
      void SubAlpha(const int sub);
      /**
       * @brief  �J���[�R�[�h�̎擾
       * @param  red   �P�x(��)
       * @param  green �P�x(��)
       * @param  blue  �P�x(��)
       * @return �J���[�R�[�h
       */
      static int GetColor(const int red, const int green, const int blue);
      /**
       * @brief  �e�P�x�̎擾
       * @return RGB�l
       */
      inline const std::tuple<int, int, int> GetLuminace() const {
        return std::make_tuple(_red, _green, _blue);
      }
      /**
       * @brief  RGBA�l�̎擾
       * @return �e�P�x�Ɠ����x
       */
      inline const std::tuple<int, int, int, int> GetRgba() const {
        return std::make_tuple(_red, _green, _blue, _alpha);
      }
      /**
       * @brief  �P�x�l(��)�̎擾
       * @return �Ԃ̋P�x�l
       */
      inline const int GetRed() const {
        return _red;
      }
      /**
       * @brief  �P�x�l(��)�̎擾
       * @return �΂̋P�x�l
       */
      inline const int GetGreen() const {
        return _green;
      }
      /**
       * @brief  �P�x�l(��)�̎擾
       * @return �̋P�x�l
       */
      inline const int GetBlue() const {
        return _blue;
      }
      /**
       * @brief  �A���t�@�l�̎擾
       * @return �A���t�@�l
       */
      inline const int GetAlpha() const {
        return _alpha;
      }
      /**
       * @brief  �J���[�R�[�h�̎擾
       * @return �J���[�R�\�h
       */
      inline const int GetColorCode() const {
        return _code;
      }
      /**
       * @brief  +���Z�q�ł̃J���[��񓯎m�̉��Z����
       * @param  color �J���[���(����)
       * @return ���Z�����J���[���
       */
      Color operator +(const Color color) const;
      /**
       * @brief  -���Z�q�ł̃J���[��񓯎m�̌��Z����
       * @param  color �J���[���(����)
       * @return ���Z�����J���[���
       */
      Color operator -(const Color color) const;
    private:
      int _red;   //!< �P�x�l(��)
      int _green; //!< �P�x�l(��)
      int _blue;  //!< �P�x�l(��)
      int _alpha; //!< �����x
      int _code;  //!< �J���[�R�[�h
      /**
       * @brief RGBA�l�̃N�����v����
       * @param red   �P�x(��)
       * @param green �P�x(��)
       * @param blue  �P�x(��)
       * @param alpha �����x(�f�t�H���g�ł�255)
       */
      void Clamp(const int red, const int green, const int blue, const int alpha = MaxColor);
    };
  } // namespace Data
} // namespace AppFrame
/*****************************************************************//**
 * @file   Color.cpp
 * @brief  RGBA�J���[���f���N���X�̒�`
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#include "Color.h"
#include <algorithm>
#ifdef _DEBUG
#include <stdexcept>
#endif
#include <Windows.h>
#include "../Math/Arithmetic.h"

namespace AppFrame {
  namespace Data {

    Color::Color() {
      _red = 0;
      _green = 0;
      _blue = 0;
      _alpha = MaxColor;
      _code = GetColor(_red, _green, _blue);
    }

    Color::Color(const int red, const int green, const int blue, const int alpha) {
      Clamp(red, green, blue, alpha);
    }

    void Color::SetColor(const int red, const int green, const int blue, const int alpha) {
      Clamp(red, green, blue, alpha);
    }

    void Color::SetAlpha(const int alpha) {
      _alpha = std::clamp(alpha, MinColor, MaxColor);
    }

    void Color::AddColor(const int red, const int green, const int blue) {
      Clamp(_red + red, _green + green, blue + blue, _alpha);
    }

    void Color::AddAlpha(const int add) {
      _alpha = std::clamp(_alpha + add, MinColor, MaxColor);
    }

    void Color::SubColor(const int red, const int green, const int blue) {
      Clamp(_red - red, _green - green, blue - blue, _alpha);
    }

    void Color::SubAlpha(const int sub) {
      _alpha = std::clamp(_alpha - sub, MinColor, MaxColor);
    }

    Color Color::operator+(const Color color) const {
      auto red = std::clamp(_red + color._red, MinColor, MaxColor);
      auto green = std::clamp(_green + color._green, MinColor, MaxColor);
      auto blue = std::clamp(_blue + color._blue, MinColor, MaxColor);
      return Color(red, green, blue);
    }

    Color Color::operator-(const Color color) const {
      auto red = std::clamp(_red - color._red, MinColor, MaxColor);
      auto green = std::clamp(_green - color._green, MinColor, MaxColor);
      auto blue = std::clamp(_blue - color._blue, MinColor, MaxColor);
      return Color(red, green, blue);
    }

    void Color::Clamp(const int red, const int green, const int blue, const int alpha) {
#ifndef _DEBUG
      // �l�̃N�����v
      _red = std::clamp(red, MinColor, MaxColor);
      _green = std::clamp(green, MinColor, MaxColor);
      _blue = std::clamp(blue, MinColor, MaxColor);
      _alpha = std::clamp(alpha, MinColor, MaxColor);
#else
      try {
        // �f�o�b�O�r���h���͈������s���ł͂Ȃ����̔�����s��
        _red = Math::Arithmetic::Clamp(red, MinColor, MaxColor);
        _green = Math::Arithmetic::Clamp(blue, MinColor, MaxColor);
        _blue = Math::Arithmetic::Clamp(green, MinColor, MaxColor);
        _alpha = Math::Arithmetic::Clamp(alpha, MinColor, MaxColor);
      } catch (std::logic_error error) {
        OutputDebugString(error.what()); // ���W�J���ɖ��L��
      }
#endif
      // �J���[�R�[�h�̎擾
      _code = GetColor(_red, _green, _blue);
    }

    int Color::GetColor(const int red, const int green, const int blue) {
      // ���ꂼ��̋P�x��16�i���ɕϊ�
      auto r = Math::Arithmetic::ToHexadecimal(red);
      auto g = Math::Arithmetic::ToHexadecimal(green);
      auto b = Math::Arithmetic::ToHexadecimal(blue);
      // ����
      auto colorCode = r + g + b;
      // 16�i��������𐮐��ɕϊ�����
      return std::stoi(colorCode, nullptr, Math::Hexadecimal);
    }

  } // namespace Data
} // namespace AppFrame
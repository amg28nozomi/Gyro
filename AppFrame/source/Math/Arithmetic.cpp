/*****************************************************************//**
 * @file   Arithmetic.cpp
 * @brief  算術処理クラスの定義
 *
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#include "Arithmetic.h"
#include <cmath>
#include <algorithm>
#include <charconv>
#include <stdexcept>
#include <vector>

namespace AppFrame {
  namespace Math {

    int Arithmetic::Clamp(const int value, const int low, const int height) {
#ifndef _DEBUG
      // 下限が上限を超過していないか？
      if (height <= low) {
        return -1; // 元の値を返す
      }
#else
      if (height <= low) {
        throw std::out_of_range("Arithmetic::Clamp:下限値が上限値を超過、または一致しています\n");
        return value;
      }
      // 値は範囲内に収まっているか
      if (value < low) {
        throw std::out_of_range("Arithmetic::値が下限を下回りました value:" + std::to_string(value) + " low:" + std::to_string(low));
      }
      else if (height < value) {
        throw std::out_of_range("Arithmetic::値が上限を超過しました value:" + std::to_string(value) + " height:" + std::to_string(height));
      }
#endif
      return std::clamp(value, low, height);
    }

    float Arithmetic::Clamp(const float value, const float low, const float height) {
#ifndef _DEBUG
      // 下限が上限を超過していないか？
      if (height <= low) {
        return value; // 元の値を返す
      }
#else
      if (height <= low) {
        throw std::out_of_range("Arithmetic::Clamp:下限値が上限値を超過、または一致しています\n");
        return value;
      }
      // 値は範囲内に収まっているか
      if (value < low) {
        throw std::out_of_range("Arithmetic::値が下限を下回りました value:" + std::to_string(value) + " low:" + std::to_string(low));
      }
      else if (height < value) {
        throw std::out_of_range("Arithmetic::値が上限を超過しました value:" + std::to_string(value) + " height:" + std::to_string(height));
      }
#endif
      return std::clamp(value, low, height);
    }

    bool Arithmetic::IsRange(const int value, const int low, const int height) {
      // 対象は範囲内に収まっているか
      if (value < height || low < value) {
        return true; // 範囲内
      }
      return false;  // 範囲外
    }

    bool Arithmetic::IsRange(const float value, const float low, const float height) {
      // 対象は範囲内に収まっているか
      if (value <= height || low <= value) {
        return true; // 範囲内
      }
      return false;  // 範囲外
    }

    float Arithmetic::Length(const float x, const float y) {
      return std::sqrt(x * x + y * y);
    }

    float Arithmetic::LengthSquared(const float x, const float y) {
      return x * x + y * y;
    }

    bool Arithmetic::IsPositive(const int value) {
      // 値が0以上かの判定を行う
      return 0 <= value;
    }

    std::string Arithmetic::ToBinary(int num) {
      std::string binary; // 2進数
      while (num != 0) {
        // 余りが出るか？
        binary += (num % Binary == 0 ? "0" : "1");
        num /= Binary;
      }
      return binary;
    }

    std::string Arithmetic::ToHexadecimal(int num) {
      std::string hexadecimal; // 16進数
      // 値が0の場合は処理を変更
      if (num == 0) {
        return "00";
      }
      while (num != 0) {
        auto param = num % Hexadecimal;      // 余剰
        hexadecimal += ToRemainder16(param); // 文字列に変換した余剰を末尾に追加
        num /= Hexadecimal; // 16で割る(端数切り捨て)
      }
      // 数字文字列が1文字の場合は先頭に0を追加
      if (hexadecimal.size() == 1) {
        hexadecimal.insert(0, "0");
      }
      return hexadecimal;
    }

    int Arithmetic::ToInteger(std::string_view num) {
      return 0;
    }

    std::string Arithmetic::ToRemainder16(const int remainder) {
#ifdef _DEBUG
      // 引数は対象範囲に収まっているか？
      if (Hexadecimal <= remainder) {
        throw std::logic_error("Arithmetic::ToRemainder16:引数の値が対象範囲外です\n");
      }
#endif
      // 値を対応範囲内に修正
      auto num = std::clamp(remainder, 0, 15);
      // 10以上の場合はそれぞれ対応するアルファベット
      // 10未満の場合は文字列に変換した値を返す
      switch (num) {
      case 15:
        return "f";
      case 14:
        return "e";
      case 13:
        return "d";
      case 12:
        return "c";
      case 11:
        return "b";
      case 10:
        return "a";
      default:
        return std::to_string(num);
      }
    }
  } // namespace Math
} // namespace AppFrame
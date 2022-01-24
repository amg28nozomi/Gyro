/*****************************************************************//**
 * @file   UtilityDX.cpp
 * @brief  
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "UtilityDX.h"
#include <appframe.h>

namespace Gyro {

  VECTOR UtilityDX::ToVECTOR(AppFrame::Math::Vector4& vector) {
    return VECTOR(vector.GetX(), vector.GetY(), vector.GetZ());
  }

  AppFrame::Math::Vector4 UtilityDX::ToVector(VECTOR& vector) {
    return AppFrame::Math::Vector4(vector.x, vector.y, vector.z);
  }

  MATRIX UtilityDX::ToMATRIX(AppFrame::Math::Matrix44 matrix) {
    MATRIX matrixDX;
    for (auto row = 0; row < AppFrame::Math::MaxRow; ++row) {
      for (auto column = 0; column < AppFrame::Math::MaxColumn; ++column) {
        // 値をコピーする
        matrixDX.m[row][column] = matrix.GetValue(row, column);
      }
    }
    return std::move(matrixDX);
  }
} // namespace Gyro
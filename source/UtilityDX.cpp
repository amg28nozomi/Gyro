/*****************************************************************//**
 * @file   UtilityDX.cpp
 * @brief  
 * 
 * @author —é–ØŠóŠC
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
} // namespace Gyro
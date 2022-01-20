/*****************************************************************//**
 * @file   UtilityDX.cpp
 * @brief  
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "UtilityDX.h"
#include <appframe.h>

namespace Gyro {

  VECTOR UtilityDX::ToVECTOR(AppFrame::Math::Vector4 vector) {
    return VECTOR(vector.GetX(), vector.GetY(), vector.GetZ());
  }
} // namespace Gyro
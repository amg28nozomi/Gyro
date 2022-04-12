/*****************************************************************//**
 * @file   WirePoint.cpp
 * @brief  ワイヤーアクション情報クラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "WirePoint.h"

namespace Gyro {
  namespace Object {
    
    WirePoint::WirePoint(const AppMath::Vector4& point, WirePoint& target) : _target(target) {
      _position = point;
    }
  } // namespace Object
} // namespace Gyro
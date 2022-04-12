/*****************************************************************//**
 * @file   WirePoint.cpp
 * @brief  ���C���[�A�N�V�������N���X�̒�`
 * 
 * @author ��؊�C
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
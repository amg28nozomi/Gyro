/*****************************************************************//**
 * @file   CameraBase.cpp
 * @brief  �J�����x�[�X�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "CameraBase.h"
#include <DxLib.h>
#include "ObjectBase.h"

namespace Gyro {
  namespace Application {

    CameraBase::CameraBase(Object::ObjectBase& owner) : _owner(owner) {

    }
  } // namespace Application
} // namespace Gyro
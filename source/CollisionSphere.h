/*****************************************************************//**
 * @file   CollisionSphere.h
 * @brief  �R���W�����x�[�X�̃T�u�N���X
 *         ���̓����蔻��N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "CollisionBase.h"
#include <Dxlib.h>

namespace AppFrame::Math {
  class Vector4;
}

namespace Gyro {
  namespace Object {
    /**
     * @class CollisionSphere
     * @brief ���̓����蔻��N���X
     */
    class CollisionSphere : public CollisionBase {
    public:
      /**
       * @brief ��̃R���X�g���N�^
       */
      CollisionSphere();
    };

  } // namespace Object
} // namespace Gyro
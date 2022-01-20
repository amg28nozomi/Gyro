/*****************************************************************//**
 * @file   CollisionSphere.h
 * @brief  コリジョンベースのサブクラス
 *         球の当たり判定クラス
 * 
 * @author 鈴木希海
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
     * @brief 球の当たり判定クラス
     */
    class CollisionSphere : public CollisionBase {
    public:
      /**
       * @brief 空のコンストラクタ
       */
      CollisionSphere();
    };

  } // namespace Object
} // namespace Gyro
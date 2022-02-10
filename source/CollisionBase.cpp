/*****************************************************************//**
 * @file   CollisionBase.cpp
 * @brief  衝突判定用情報の基底クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "CollisionBase.h"
#include "ObjectBase.h"

namespace Gyro {
  namespace Object {

    CollisionBase::CollisionBase(ObjectBase& owner) : _owner(owner) {
      _position = AppMath::Vector4();
    }

    void CollisionBase::Process() {
    }

    void CollisionBase::Process(AppMath::Vector4 vector) {
    }

#ifdef _DEBUG
    void CollisionBase::Draw() {
    }
#endif

    bool CollisionBase::IsHit() {
      return _hit; // 衝突フラグがtrueではない場合、処理を行わない
    }
  } // namespace Object
} // namespace Gyro
/*****************************************************************//**
 * @file   CollisionComponent.cpp
 * @brief  衝突判定処理を行うコンポーネントクラスの定義
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "CollisionComponent.h"
#include "CollisionBase.h"
#include "ObjectBase.h"

namespace Gyro {
  namespace Object {

    CollisionComponent::CollisionComponent(ObjectBase& obj) : _owner(obj) {
      // 当たり判定の設定を行う

    }
    

    bool CollisionComponent::SetCollision(std::unique_ptr<CollisionBase> collision) {
      // 引数がnullの場合は登録を行わない
      if (collision == nullptr) {
        return false; // 設定失敗
      }
      // 実体がある場合は登録する
      _collision = std::move(collision);
      return true;    // 設定完了
    }
  } // namespace Object
} // namespace Gyro
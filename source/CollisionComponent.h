/*****************************************************************//**
 * @file   CollisionComponent.h
 * @brief  衝突判定処理を行うコンポーネントクラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <memory>
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class ObjectBase;    //!< オブジェクトベースの前方宣言
    class CollisionBase; //!< コリジョンベースの前方宣言
    /**
     * @class CollisionComponent
     * @brief 当たり判定処理を行うコンポーネント
     */
    class CollisionComponent {
    public:
      /**
       * @brief コンストラクタ
       * @param owner 対象オブジェクトの参照
       */
      CollisionComponent(ObjectBase& owner);
      /**
       * @brief 当たり判定の登録
       * @param collision CollisionBaseのユニークポインタ
       */
      bool SetCollision(std::unique_ptr<CollisionBase> collision);
    private:
      ObjectBase& _owner; //!< 所有者の参照
      std::unique_ptr<CollisionBase> _collision{nullptr}; //!< 衝突判定情報
    };
  }
} // namespace Gyro
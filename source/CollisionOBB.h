/*****************************************************************//**
 * @file   CollisionOBB.h
 * @brief  有向バウンディングボックスの衝突判定クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "CollisionBase.h"
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    /**
     * @class 
     * @brief
     */
    class CollisionOBB : public CollisionBase {
      /**
       * @brief コンストラクタ
       * @param  owner    所有者の参照
       * @param  position 座標
       * @param  rotation 向き
       * @param  scale    スケール
       */
      CollisionOBB(ObjectBase& owner, AppMath::Vector4 position, AppMath::Vector4 rotation, AppMath::Vector4 scale);

      bool CheckLineSegment(const AppMath::LineSegment& segment);
    private:
      AppMath::Matrix44 _matrix;  //!< 行列
      AppMath::Matrix44 _inverse; //!< 逆行列
    };
  } // namespace Object
} // namespace Gyro
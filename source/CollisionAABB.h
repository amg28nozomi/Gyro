/*****************************************************************//**
 * @file   CollisionAABB.h
 * @brief  軸平行バウンディングボックスの衝突判定クラス
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
     * @class CollisionAABB
     * @brief 軸平行バウンディングボックスの衝突判定クラス
     */
    class CollisionAABB : public CollisionBase {
      /**
       * @brief コンストラクタ
       * @param owner 所有者の参照
       * @param min   最小点ベクトル
       * @param max   最大点ベクトル
       */
      CollisionAABB(ObjectBase& owner, const AppMath::Vector4& min, const AppMath::Vector4& max);
      /**
       * @brief 当たり判定の更新
       * @param point 中心座標
       */
      void Process(const AppMath::Vector4& point);

#ifdef _DEBUG
      /**
       * @brief 当たり判定の描画
       */
       // void Draw() override;
#endif
      /**
       * @brief  点座標の包含判定
       * @param  point 点座標
       */
      bool CheckPoint(const AppMath::Vector4& point);
      /**
       * @brief  線分との衝突判定
       * @param  segment 線分の参照
       * @return true:衝突 false:衝突していない
       */
      bool CheckLineSegment(const AppMath::LineSegment& segment);
    private:
      AppMath::Vector4 _max; // 最大点
    };
  } // namespace Object
} // namespace Gyro
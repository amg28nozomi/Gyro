/*****************************************************************//**
 * @file   CollisionCapsule.h
 * @brief  コリジョンベースのサブクラス
 *         カプセルの衝突判定処理クラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "CollisionBase.h"

namespace AppFrame::Math {
  class Plane;
}

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class CollisionSphere; //!< 前方宣言
    /**
     * @class CollisionCapsule
     * @brief カプセルの衝突判定処理クラス
     */
    class CollisionCapsule : public CollisionBase {
    public:
      /**
       * @brief コンストラクタ
       * @param owner 所有者の参照
       * @param center 中心座標(足)
       * @param line   線分の長さ
       * @param radius 半径
       */
      CollisionCapsule(ObjectBase& owner, AppMath::Vector4 center, float line, float radius);
      /**
       * @brief 当たり判定の更新処理
       */
      void Process(AppMath::Vector4 move) override;
#ifdef _DEBUG
      /**
       * @brief 当たり判定の描画処理
       */
      void Draw() override;
#endif
      /**
       * @brief  カプセルと線分の衝突判定
       * @param  line 衝突判定を行う線分の参照
       * @return true:衝突 false:衝突していない
       */
      bool IntersectLine(const AppMath::LineSegment& line);
      /**
       * @brief  カプセルと球の衝突判定
       * @param  sphere 衝突判定を行う球コリジョン
       * @return true:衝突 false:衝突していない
       */
      bool IntersectSphere(const CollisionSphere& sphere);
      /**
       * @brief  カプセルとカプセルの衝突判定
       * @param  capsule 衝突判定を行うカプセルコリジョン
       * @return true:衝突 false:衝突していない
       */
      bool IntersectCapsule(const CollisionCapsule& capsule);
      /**
       * @brief  平面との衝突判定(線分)
       * @param  plane
       * @return 
       */
      bool IntersectPlane(const AppFrame::Math::Plane& plane);
      /**
       * @brief  半径の取得
       * @return 半径
       */
      float GetRadius() const {
        return _radius;
      }
    private:
      float _length; //!< 線分の長さ
      float _radius; //!< 半径
      /**
       * @brief  線分の取得
       * @return 線分を返す
       */
      AppMath::LineSegment LineSegment() const;
    };
  } // namespace Object
} // namespace Gyro
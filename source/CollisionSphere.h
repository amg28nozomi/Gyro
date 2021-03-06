/*****************************************************************//**
 * @file   CollisionSphere.h
 * @brief  コリジョンベースのサブクラス
 *         球の衝突判定クラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "CollisionBase.h"
#include <Dxlib.h>

/**
 * @brief 
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    /**
     * @class CollisionSphere
     * @brief 球の当たり判定クラス
     */
    class CollisionSphere : public CollisionBase {
    public:
      /**
       * @brief コンストラクタ
       * @param owner  所有者の参照
       * @param center 中心座標
       * @param radius 円の半径
       */
      CollisionSphere(ObjectBase& owner, AppMath::Vector4 center, float radius);
      /**
       * @brief 当たり判定の設定
       */
      void Process() override;
      /**
       * @brief 更新処理
       * @param move 移動量
       */
      void Process(AppMath::Vector4 move) override;
#ifdef _DEBUG
      void Draw() override;

      inline void HitOn() {
        _collision = true;
      }
#endif
      /**
       * @brief  衝突判定
       * @return 
       */
      bool IsHit() override;
      /**
       * @brief  球と球の衝突判定
       * @param  sphere ターゲット
       * @return true:衝突 false:衝突していない
       */
      bool IntersectSphere(const CollisionSphere& sphere);
      /**
       * @brief  球と点の当たり判定
       * @param  point 点の座標
       * @return true:衝突 false:衝突していない
       */
      bool IntersectPoint(const AppMath::Vector4& point);
      /**
       * @brief  半径の取得
       * @return 半径
       */
      float Radius() const {
        return _radius;
      }
      /**
       * @brief  半径の二乗を取得
       * @return 半径の二乗
       */
      inline float RadiusSquared() const {
        return _radius * _radius;
      }
    private:
      float _radius{0.0f}; //!< 円の半径
    };

  } // namespace Object
} // namespace Gyro
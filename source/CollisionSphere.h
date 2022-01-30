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

namespace Gyro {
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
       * @brief 当たり判定の更新処理
       */
      void Process() override;
      /**
       * @brief 更新処理
       * @param vector 移動量
       */
      void Process(AppMath::Vector4 vector) override;
#ifdef _DEBUG
      void Draw() override;
#endif
      /**
       * @brief  衝突判定
       * @return 
       */
      bool IsHit() override;
    private:
      float _radius{0.0f}; //!< 円の半径
      /**
       * @brief  球と球の衝突判定
       * @param  sphere ターゲット
       * @return 
       */
      bool IntersectSphere(const CollisionSphere& sphere);
    };

  } // namespace Object
} // namespace Gyro
#pragma once
#include <appframe.h>
#include "CollisionAABB.h"

namespace Gyro {
  namespace Object {
    namespace AppMath = AppFrame::Math; //!< 名前空間の省略
    /**
     * @class WirePoint
     * @brief ワイヤーアクション用の座標
     */
    class WirePoint {
    public:
      /**
       * @brief コンストラクタ
       * @param point 中心座標
       * @param target 対応するポイント情報
       */
      WirePoint(const AppMath::Vector4& point, WirePoint& target);
      /**
       * @brief  点座標の取得
       * @return 点座標情報
       */
      AppMath::Vector4 Point() const {
        return _position;
      }
      /**
       * @brief  コリジョン情報の取得
       * @return 判定用ボックス
       */
      CollisionAABB& Collision() const {
        return *_box;
      }
    private:
      //!< 対となる座標
      WirePoint& _target;
      //!< ワールド座標
      AppMath::Vector4 _position;
      //!< 判定用ボックス
      std::unique_ptr<CollisionAABB> _box;
    };
  } // namespace Object
} // namespace Gyro
/*****************************************************************//**
 * @file   CollisionBase.h
 * @brief  当たり判定用情報の基底クラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once

namespace AppFrame::Math {
  class Vector4;
}

 /**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    namespace AppMath = AppFrame::Math;
    /**
     * @class CollisionBase
     * @brief 当たり判定情報
     */
    class CollisionBase {
    public:
      /**
       * @brief 当たり判定の基底クラス
       */
      CollisionBase();
      /**
       * @brief 当たり判定の更新
       */
      virtual void Process();
      /**
       * @brief 当たり判定の描画
       */
      virtual void Draw();
    protected:
    };
  } // namespace Object
} // namespace Gyro
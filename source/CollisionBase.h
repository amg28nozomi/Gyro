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
    class ObjectBase;
    /**
     * @class CollisionBase
     * @brief 当たり判定情報の基底クラス
     */
    class CollisionBase {
    public:
      /**
       * @brief 当たり判定の基底クラス
       * @param owner 所有者の参照
       */
      CollisionBase(ObjectBase& owner);
      /**
       * @brief 当たり判定の更新
       */
      virtual void Process();
      /**
       * @brief 当たり判定の描画
       */
      virtual void Draw();
      /**
       * @brief  衝突判定
       * @return true:衝突有り false:衝突なし
       */
      virtual bool IsHit();
      /**
       * @brief 衝突判定フラグの設定
       * @param flag 処理フラグ(true:衝突判定を行う false:衝突判定を行わない)
       */
      void SetHitFlag(const bool flag) {
        _hit = flag;
      }
    protected:
      ObjectBase& _owner; //!< 所有者の参照
      AppMath::Vector4 _position{}; //!< ローカル座標
      bool _hit{true}; //!< 衝突判定フラグ(true:有効 false:非有効)
    };
  } // namespace Object
} // namespace Gyro


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
  class Matrix44;
}
 /**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    namespace AppMath = AppFrame::Math; //!< 名前空間の省略
    class ObjectBase; //!< 前方宣言
    /**
     * @class CollisionBase
     * @brief 当たり判定情報
     */
    class CollisionBase {
    public:
      /**
       * @brief コリジョンの種類を表す列挙型クラス
       */
      enum class CollisionType {
        Null,  // 該当なし
        Line,  // 線分
        Sphere // 球
      };
      /**
       * @brief コンストラクタ
       * @param owner 所有者の参照
       */
      CollisionBase(ObjectBase& owner);
      /**
       * @brief 当たり判定の更新
       */
      virtual void Process();
#ifdef _DEBUG
      /**
       * @brief デバッグ用の当たり判定描画
       */
      virtual void Draw();
#endif
      /**
       * @brief  コリジョン同士の衝突判定
       * @tparam Collision コリジョンクラスの参照
       * @param  left  判定コリジョンの参照
       * @param  right 判定コリジョンの参照
       * @return true:衝突した false:衝突していない
       */
      template <class Collision>
      bool IsHit(Collision& left, Collision& right);
      /**
       * @brief  当たり判定の種類を取得する
       * @return コリジョンタイプ
       */
      inline CollisionType GetCollisionType() const {
        return _type;
      }
    protected:
      //!< コリジョンタイプ
      CollisionType _type{CollisionType::Null};
      ObjectBase& _owner;  //!< 所有者の参照
      AppMath::Vector4 _position; //!< ローカル座標
      AppMath::Vector4 _rotation; //!< 向き
      AppMath::Vector4 _scale;    //!< 拡大率
      /**
       * @brief  ワールド座標行列の取得
       * @return ワールド座標行列
       */
      AppMath::Matrix44 WorldMatrix() const;
    };

    template <class Collision>
    bool CollisionBase::IsHit(Collision& left, Collision& right) {
      return true;
    }
  } // namespace Object
} // namespace Gyro
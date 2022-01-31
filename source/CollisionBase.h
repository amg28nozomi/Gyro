/*****************************************************************//**
 * @file   CollisionBase.h
 * @brief  当たり判定用情報の基底クラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

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
       * @brief 当たり判定の種類を表す列挙型クラス
       */
      enum class CollisionType {
        None,   // 該当なし
        Line,   // 線分
        Sphere, // 球
        Capsule // カプセル
      };
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
       * @brief 当たり判定の更新
       * @param vector 
       */
      virtual void Process(AppMath::Vector4 vector);
#ifdef _DEBUG
      /**
       * @brief 当たり判定の描画
       */
      virtual void Draw();
      /**
       * @brief デバッグ出力フラグを切り替える
       * @param flag true:描画を行う false:描画を行わない
       */
      static inline void SetDebugFlag(const bool flag) {
        _debug = flag;
      }
#endif
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
      /**
       * @brief  コリジョンタイプの取得
       * @return コリジョンタイプを返す
       */
      CollisionType GetType() const {
        return _type;
      }
    protected:
      //!< コリジョンの種類
      CollisionType _type{CollisionType::None};
      //!< 所有者の参照
      ObjectBase& _owner;
      //!< ローカル座標
      AppMath::Vector4 _position;
      //!< 衝突判定フラグ(true:有効 false:非有効)
      bool _hit{true};
#ifdef _DEBUG
      //!< デバッグ描画フラグ
      static inline bool _debug{false};
      //!< 衝突判定
      bool _collision{false}; //!< 衝突判定
#endif
    };
  } // namespace Object
} // namespace Gyro


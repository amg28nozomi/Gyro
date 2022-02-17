/*****************************************************************//**
 * @file   AttackComponent.h
 * @brief  攻撃用コンポーネントクラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"
#include "CollisionBase.h"

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class ObjectBase; //!< オブジェクトベース
    /**
     * @class AttackComponent
     * @brief 攻撃用コンポーネント
     */
    class AttackComponent : public ObjectComponent {
    public:
      /**
       * @brief 攻撃状態を表す列挙型クラス
       */
      enum class AttackState {
        NonActive, // ノーアクション
        Active,    // 活動状態
      };
      /**
       * @brief  コンストラクタ
       * @param  owner     所有者の参照
       * @param  key       モデルサーバに紐づけられた所有者の
       * @param  collision 当たり判定のシェアードポインタ
       */
      AttackComponent(ObjectBase& owner, std::shared_ptr<CollisionBase> collision);
      /**
       * @brief 攻撃判定の開始
       */
      virtual inline void Start() override {
        _state = AttackState::Active;
      }
      /**
       * @brief 攻撃判定の終了
       */
      virtual void Finish() override;
      /**
       * @brief  攻撃判定の更新
       * @param  localPosition ローカル座標
       * @return true:正常終了 false:攻撃状態ではない
       */
      virtual bool Process(const AppMath::Vector4& localPosition);
#ifdef _DEBUG
      /**
       * @brief 当たり判定の描画処理(デバッグ専用)
       */
      void Draw() const;
#endif
      /**
       * @brief  攻撃状態の取得
       * @return 攻撃状態
       */
      const AttackState& GetState() {
        return _state;
      }
      /**
       * @brief  当たり判定情報の取得
       * @return 当たり判定情報
       */
      const std::shared_ptr<CollisionBase>& GetCollision()  {
        return _collision;
      }
    protected:
      //!< 所有者の参照
      ObjectBase& _owner;
      //!< オブジェトのキー
      std::string _objectKey;
      //!< 攻撃状態
      AttackState _state;
      //!< 攻撃用当たり判定情報
      std::shared_ptr<CollisionBase> _collision;
      //!< 攻撃判定時間
      float _time{0.0f};
      /**
       * @brief ローカル座標をワールド座標に変換する
       */
      AppMath::Matrix44 LocalToWorld(const AppMath::Vector4& local) const;
    };
  } // mamespace Object
} // namespace Gyro
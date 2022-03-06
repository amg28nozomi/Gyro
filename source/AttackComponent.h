/*****************************************************************//**
 * @file   AttackComponent.h
 * @brief  攻撃用コンポーネントクラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"
#include <memory>
#include <vector>
#include <appframe.h>
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class ObjectBase;
    class CollisionBase;
    namespace AppMath = AppFrame::Math;
    constexpr auto DefaultSpeed = 10.0f;
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
        Interval   // インターバル
      };
      /**
       * @brief  コンストラクタ
       * @param  owner     所有者の参照
       * @param  key       モデルサーバに紐づけられた所有者の
       * @param  collision 当たり判定のシェアードポインタ
       */
      AttackComponent(ObjectBase& owner, std::shared_ptr<CollisionBase> collision);
      /**
       * @brief  コンストラクタ
       * @param  owner     所有者の参照
       * @param  key       モデルサーバに紐づけられた所有者の
       * @param  collision 当たり判定を格納した動的配列
       */
      AttackComponent(ObjectBase& owner, std::vector<std::shared_ptr<CollisionBase>> collision);
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
      /**
       * @brief  攻撃判定の修正処理
       * @return true:正常終了 false:問題発生
       */
      virtual bool Process();
      /**
       * @brief  当たり判定に使用するフレームの設定
       * @param  frames     フレーム番号
       * @param  collisions コリジョン情報
       */
      void SetFrame(std::vector<int> frames, std::vector<std::shared_ptr<CollisionBase>> collisions);
#ifdef _DEBUG
      /**
       * @brief 当たり判定の描画処理(デバッグ専用)
       */
      void Draw() const;
#endif
      /**
       * @brief  インターバル時間の設定
       * @param  time  インターバル時間
       * @param  speed 経過時間(デフォルトだと10.0f)
       */
      void SetInterval(const float time, const float speed = DefaultSpeed);
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
        return _collision.front();
      }
      /**
       * @brief  当たり判定情報の取得
       * @return 当たり判定が格納されたコンテナを返す
       */
      const std::vector<std::shared_ptr<CollisionBase>>& GetCollisions() {
        return _collision;
      }
      /**
       * @brief  攻撃状態かの判定
       * @return true:攻撃状態 false:非攻撃状態
       */
      inline bool IsAttack() const {
        return _state == AttackState::Active;
      }
      /**
       * @brief  インターバル状態かの判定
       * @return true:インターバル状態 false:それ以外の状態
       */
      inline bool IsInterval() const {
        return _state == AttackState::Interval;
      }
      /**
       * @brief  攻撃状態に遷移できるかの判定
       * @return true:遷移可能 false:不可
       */
      inline bool ToAttack() const {
        return _state == AttackState::NonActive;
      }
    protected:
      //!< オブジェクトの所有者
      ObjectBase& _owner;
      //!< オブジェトキー
      std::string _objectKey;
      //!< 攻撃状態
      AttackState _state;
      //!< 攻撃判定用のコリジョン情報を格納した動的配列
      std::vector<std::shared_ptr<CollisionBase>> _collision;
      //!< ワールド座標を格納するためのコンテナ
      std::vector<int> _indexs;
      //!< インターバル時間
      float _time{0.0f};
      //!< 経過時間
      float _speed{0.0f};
      /**
       * @brief ローカル座標をワールド座標に変換する
       */
      AppMath::Matrix44 LocalToWorld(const AppMath::Vector4& local) const;
      /**
       * @brief インターバル処理
       */
      void Interval();
    };
  } // mamespace Object
} // namespace Gyro
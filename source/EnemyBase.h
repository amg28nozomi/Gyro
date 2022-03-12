/*****************************************************************//**
 * @file    EnemyBase.h
 * @brief   敵の基底クラス
 *
 * @author  宮澤耀生
 * @date    January 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"
#include "ObjectBase.h"
#include "InvincibleComponent.h"
#include "CollisionSphere.h"
#include "CollisionCapsule.h"
#include "GaugeEnemy.h"
#include "ModelAnimComponent.h"

 /**
  * @brief ゲームベース
  */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class CollisionCapsule;
    class SpawnEnemy;
  } // namespace Object
  /**
   * @brief 敵ベース
   */
  namespace Enemy {
    /**
     * @class EnemyBase
     * @brief 敵の基底クラス
     */
    class EnemyBase : public Object::ObjectBase {
    public:
      /**
       * @enum class  EnemyState
       * @brief  敵の状態遷移用定数
       */
      enum class EnemyState {
        Idle,        //!< 待機
        Move,        //!< 移動
        AttackReady, //!< 攻撃準備
        Attack,      //!< 攻撃
        Damage,      //!< 被ダメ
        Dead         //!< 死亡
      };
      /**
       * @brief  コンストラクタ
       */
      EnemyBase(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      virtual ~EnemyBase();
      /**
       * @brief  初期化
       */
      virtual bool Init();
      /**
       * @brief  更新
       */
      virtual bool Process();
      /**
       * @brief  描画
       */
      bool Draw() const override;
      /**
       * @brief  スポーン情報の読み取り
       * @param  スポーン情報の参照
       */
      void Set(Object::SpawnEnemy& spawn);
      /**
       * @brief  球の当たり判定の取得
       * @return 球の当たり判定
       */
      Object::CollisionSphere& GetCollision() {
        return *_sphere;
      }
      /**
       * @brief  カプセルの当たり判定の取得
       * @return カプセルの当たり判定
       */
      Object::CollisionCapsule& GetCapsule() {
        return *_capsule;
      }
      /**
       * @brief  無敵処理の参照を取得
       * @return 無敵処理の参照
       */
      virtual Object::InvincibleComponent& GetInvincibleComponent() {
        return *_invincible;
      }

      virtual unsigned short GetThis() const {
        return 0;
      }
      /**
       * @brief  対象と自身が同一オブジェクトかの判定
       * @param  handle ハンドル
       * @return true:一致
       *         false:不一致
       */
      inline bool Equals(const int handle) const {
        return _mHandle == handle;
      }
      /**
       * @brief  状態の取得
       * @return 状態
       */
      EnemyState GetEnemyState() const {
        return _enemyState;
      }
    protected:
      /**
       * @brief  モデルの読み込み
       */
      virtual void LoadModel();
      /**
       * @brief  パラメータの設定
       */
      virtual void SetParameter();
      /**
       * @brief  当たり判定情報の設定
       */
      virtual void SetCollision();
      /**
       * @brief  移動処理
       */
      virtual void Move();
      /**
       * @brief  攻撃処理
       */
      virtual void Attack();
      /**
       * @brief  ノックバック処理
       * @author 土橋峡介
       */
      virtual void NockBack();
      /**
       * @brief  探索処理
       * @author 土橋峡介
       */
      virtual void Search();
      /**
       * @brief  衝突処理
       */
      virtual void Hit();
      /**
       * @brief  アニメーション切り替え
       */
      virtual void ChangeAnim();
      /**
       * @brief  エフェクト再生
       */
      virtual void PlayEffect();
      /**
       * @brief  オブジェクトの死亡処理
       */
      virtual void Dead();
      /**
       * @brief  ダメージを受けたかの判定
       * @return true:衝突 false:ダメージ無し
       */
      virtual bool IsDamege();
      /**
       * @brief  Processを行うか判定する
       * @return true:Processを行う false:Processを行わない
       */
      virtual bool ProcessFlag();
      /**
       * @brief  地形との衝突判定
       * @return true:床に立っている
       *         false:床に立っていない
       */
      bool IsStand() override;
      /**
       * @brief  状態遷移したか
       * @param  前の状態
       * @return true:状態遷移あり
       *         false:状態遷移なし
       */
      bool IsChangeState(const EnemyState old) {
        return old != _enemyState;
      }

      int _cnt{ 0 };        //!< カウント
      int _mHandle{ -1 };   //!< モデルハンドル
      int _enemyHP{ 0 };    //!< 敵体力
      float _serchRadius{ 0.0f };  //!< 索敵範囲(円)の半径
      float _attackRadius{ 0.0f }; //!< 攻撃範囲(円)の半径
      float _flagRadius{ 700.0f }; //!< Processを行うかどうか
       //!< 球の当たり判定
      std::unique_ptr<Object::CollisionSphere> _sphere{ nullptr };
      //!< カプセル当たり判定
      std::unique_ptr<Object::CollisionCapsule> _capsule{ nullptr };
      //!< 無敵コンポーネント
      std::unique_ptr<Object::InvincibleComponent> _invincible{ nullptr };
      //!< 敵の状態保持変数
      EnemyState _enemyState;
      //!< 体力ゲージ
      std::shared_ptr<Gauge::GaugeEnemy> _gaugeHp{ nullptr };
      //!< モデルアニメ
      ModelAnim::ModelAnimComponent _modelAnim;
    };
  } // namespace Enemy
} // namespace Gyro
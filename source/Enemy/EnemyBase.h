/*****************************************************************//**
 * @file    EnemyBase.h
 * @brief   敵の基底クラス
 *
 * @author  宮澤耀生
 * @date    January 2022
 *********************************************************************/
#pragma once
#include "../ObjectBase.h"
#include "../ModelAnim/ModelAnimComponent.h"
#include "../CollisionSphere.h"
#include "../CollisionCapsule.h"
#include "../InvincibleComponent.h"


 /** 作品用名前空間 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class CollisionCapsule;
    class SpawnEnemy;
  } // namespace Object
    /** 敵用名前空間 */
    namespace Enemy {
        /**
         * @class EnemyBase
         * @brief 敵の基底クラス
         */
        class EnemyBase : public Object::ObjectBase {
        public:
            /**
             * @brief   コンストラクタ
             */
            EnemyBase(Application::ApplicationMain& app);
            /**
             * @brief   デストラクタ
             */
            virtual ~EnemyBase();
            /**
             * @brief   初期化
             */
            virtual bool Init();
            /**
             * @brief   更新
             */
            virtual bool Process();
            /**
             * @brief   描画
             */
            bool Draw() const override;
            /**
             * @brief  スポーン情報の読み取り
             * @param  スポーン情報の参照
             */
            void Set(Object::SpawnEnemy& spawn);

            Object::CollisionSphere& GetCollision() {
              return *_sphere;
            }

            Object::CollisionCapsule& GetCapsule() {
              return *_capsule;
            }

            virtual unsigned short GetThis() const {
              return 0;
            }
            /**
             * @brief  無敵処理の参照を取得
             * @return 無敵処理の参照
             */
            virtual Object::InvincibleComponent& GetInvincibleComponent() {
              return *_invincible;
            }
            /**
             * @brief  対象と自身が同一オブジェクトかの判定
             * @param  handle ハンドル
             * @return true:一致 false:不一致
             */
            inline bool Equals(const int handle) const {
              return _mHandle == handle;
            }
        protected:
            /**
             * @enum class  EnemyState
             * @brief   敵の状態遷移用定数
             */
            enum class EnemyState {
                Idle,   //!<待機
                Move,   //!<移動
                Attack, //!<攻撃
                Dead    //!<死亡
            };

            int _mHandle;           //!< モデルハンドル
            float _enemyMoveSpeed;  //!< 敵移動速度
            std::unique_ptr<Object::CollisionSphere> _sphere{nullptr}; //!< 球の当たり判定
            //!< カプセル当たり判定
            std::unique_ptr<Object::CollisionCapsule> _capsule{ nullptr }; //!< カプセルの当たり判定
            //!< 無敵コンポーネント
            std::unique_ptr<Object::InvincibleComponent> _invincible{nullptr};
            EnemyState _enemyState; //!< 敵の状態保持変数
            ModelAnim::ModelAnimComponent _modelAnim;
            /**
             * @brief 当たり判定情報の設定
             */
            virtual void SetCollision();
            /**
             * @brief  地形との衝突判定
             * @return 
             */
            bool IsStand() override;
            /**
             * @brief  オブジェクトの死亡処理
             */
            virtual void Dead();
        };
    } // namespace Enemy
} // namespace Gyro
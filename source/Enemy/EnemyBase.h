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
#include "../Effect/SampleEffect.h"
#include "../CollisionCapsule.h"

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
            void Set(Object::SpawnBase spawn) override;
            /**
             * @brief   敵位置の設定
             * @param   vPos 敵位置
             */
            virtual void SetEnemyPos(const VECTOR vPos) {
                _enemyPos = vPos;
            }
            /**
             * @brief   敵移動先の設定
             * @param   vTarget 敵移動先
             */
            virtual void SetEnemyTarget(const VECTOR vTarget) {
                _enemyTarget = vTarget;
            }

            Object::CollisionSphere& GetCollision() {
              return *_sphere;
            }

            Object::CollisionCapsule& GetCapsule() {
              return *_capsule;
            }
        protected:
            /**
             * @enum class  EnemyState
             * @brief   敵の状態遷移用定数
             */
            enum class EnemyState {
                WAIT,   //!<待ち
                WALK,   //!<歩き
                ATTACK, //!<攻撃
                DEAD    //!<死亡
            };

            int _mHandle;           //!< モデルハンドル
            float _enemyMoveSpeed;  //!< 敵移動速度
            VECTOR _enemyPos;       //!< 敵位置
            VECTOR _enemyDir;       //!< 敵向き
            VECTOR _enemyTarget;    //!< 敵移動先
            std::unique_ptr<Object::CollisionSphere> _sphere{nullptr}; //!< 球の当たり判定
            std::unique_ptr<Object::CollisionCapsule> _capsule{ nullptr }; //!< カプセルの当たり判定

            EnemyState _enemyState; //!< 敵の状態保持変数
            ModelAnim::ModelAnimComponent _modelAnim;
            Effect::SampleEffect _eff;
            /**
             * @brief 当たり判定情報の設定
             */
            virtual void SetCollision();
        };
    } // namespace Enemy
} // namespace Gyro
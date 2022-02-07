/*****************************************************************//**
 * @file    EnemyBase.cpp
 * @brief   敵の基底クラス
 *
 * @author  宮澤耀生
 * @date    January 2022
 *********************************************************************/
#include "EnemyBase.h"
#include "../ApplicationMain.h"
#include "../SpawnEnemy.h"

namespace Gyro {
    namespace Enemy {
        EnemyBase::EnemyBase(Application::ApplicationMain& app) : Object::ObjectBase(app) {
            // 初期化
            Init();
        }

        EnemyBase::~EnemyBase() {

        }

        bool EnemyBase::Init() {
            // 初期化
            _mHandle = -1;
            _enemyMoveSpeed = 0.0f;
            _id = ObjectId::Enemy;
            _enemyState = EnemyState::WAIT;
            return true;
        }

        bool EnemyBase::Process() {
            _eff.Process();
            return true;
        }

        bool EnemyBase::Draw() const {
            // 描画
            MV1DrawModel(_mHandle);
            _eff.Draw();
#ifdef _DEBUG
            if (_app.GetDebugFlag()) {
              // _sphere->Draw();
            }
#endif
            return true;
        }

        void EnemyBase::Set(Object::SpawnBase spawn) {
          // 座標情報をセットする
          ObjectBase::Set(spawn);
          // 当たり判定の設定
          SetCollision();
          // auto enemy = dynamic_cast<Object::SpawnEnemy*>(&spawn);
        }

        void EnemyBase::SetCollision() {
        }
    } // namespace Enemy
} // namespace Gyro
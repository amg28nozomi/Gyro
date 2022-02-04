/*****************************************************************//**
 * @file    EnemyBase.cpp
 * @brief   GĖîęNX
 *
 * @author  {āVsķ
 * @date    January 2022
 *********************************************************************/
#include "EnemyBase.h"
#include "../ApplicationMain.h"

namespace Gyro {
    namespace Enemy {
        EnemyBase::EnemyBase(Application::ApplicationMain& app) : Object::ObjectBase(app) {
            // úŧ
            Init();
        }

        EnemyBase::~EnemyBase() {

        }

        bool EnemyBase::Init() {
            // úŧ
            _mHandle = -1;
            _enemyMoveSpeed = 0.0f;
            _enemyPos = VGet(0, 0, 0);
            _enemyDir = VGet(0, 0, 0);
            _enemyTarget = VGet(0, 0, 0);
            _id = ObjectId::Enemy;
            _enemyState = EnemyState::WAIT;
            return true;
        }

        bool EnemyBase::Process() {
            _eff.Process();
            return true;
        }

        bool EnemyBase::Draw() const {
            // `æ
            MV1DrawModel(_mHandle);
            _eff.Draw();
#ifdef _DEBUG
            if (_app.GetDebugFlag()) {
              // _sphere->Draw();
            }
#endif
            return true;
        }
    } // namespace Enemy
} // namespace Gyro
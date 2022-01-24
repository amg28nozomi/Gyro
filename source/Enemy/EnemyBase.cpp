/*****************************************************************//**
 * @file    EnemyBase.cpp
 * @brief   GĖîęNX
 *
 * @author  {āVsķ
 * @date    January 2022
 *********************************************************************/
#include "EnemyBase.h"

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
            _enemyState = EnemyState::WAIT;
            return true;
        }

        bool EnemyBase::Process() {
            return true;
        }

        bool EnemyBase::Draw() const {
            // ĘuÝč
            MV1SetPosition(_mHandle, _enemyPos);
            // üŦĐįYēņ]ðZo
            VECTOR vRot = { 0,0,0 };
            vRot.y = atan2(_enemyDir.x * 1, _enemyDir.z * 1);
            MV1SetRotationXYZ(_mHandle, vRot);
            // `æ
            MV1DrawModel(_mHandle);
            return true;
        }
    } // namespace Enemy
} // namespace Gyro
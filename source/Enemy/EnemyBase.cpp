/*****************************************************************//**
 * @file    EnemyBase.cpp
 * @brief   “G‚ÌŠî’êƒNƒ‰ƒX
 *
 * @author  ‹{àV—s¶
 * @date    January 2022
 *********************************************************************/
#include "EnemyBase.h"
#include "../ApplicationMain.h"
#include "../SpawnEnemy.h"

namespace Gyro {
    namespace Enemy {
        EnemyBase::EnemyBase(Application::ApplicationMain& app) : Object::ObjectBase(app) {
            // ‰Šú‰»
            Init();
        }

        EnemyBase::~EnemyBase() {

        }

        bool EnemyBase::Init() {
            // ‰Šú‰»
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
            // •`‰æ
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
          // À•Wî•ñ‚ğƒZƒbƒg‚·‚é
          ObjectBase::Set(spawn);
          // “–‚½‚è”»’è‚Ìİ’è
          SetCollision();
          // auto enemy = dynamic_cast<Object::SpawnEnemy*>(&spawn);
        }

        void EnemyBase::SetCollision() {
        }
    } // namespace Enemy
} // namespace Gyro
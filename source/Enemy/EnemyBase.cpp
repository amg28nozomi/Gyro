/*****************************************************************//**
 * @file    EnemyBase.cpp
 * @brief   �G�̊��N���X
 *
 * @author  �{�V�s��
 * @date    January 2022
 *********************************************************************/
#include "EnemyBase.h"
#include "../ApplicationMain.h"
#include "../SpawnEnemy.h"
#include "../UtilityDX.h"
#include "../Player.h"
#include "../ObjectServer.h"

namespace Gyro {
    namespace Enemy {
        EnemyBase::EnemyBase(Application::ApplicationMain& app) : Object::ObjectBase(app) {
            // ������
            Init();
        }

        EnemyBase::~EnemyBase() {

        }

        bool EnemyBase::Init() {
            // ������
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
            // �`��
            MV1DrawModel(_mHandle);
            _eff.Draw();
#ifdef _DEBUG
            if (_app.GetDebugFlag()) {
              // _sphere->Draw();
            }
#endif
            return true;
        }

        void EnemyBase::Set(Object::SpawnEnemy& spawn) {
          // ���W�����Z�b�g����
          ObjectBase::Set(spawn.GetInstance());
          // �����蔻��̐ݒ�
          SetCollision();
          // auto enemy = dynamic_cast<Object::SpawnEnemy*>(&spawn);
        }

        void EnemyBase::SetCollision() {
        }

        bool EnemyBase::IsStand() {
          // �V�������W
          auto newPos = _position.AddVectorY(_gravityScale);
          // �V�����J�v�Z��
          auto newCapsule = *_capsule;
          // �J�v�Z�����W���Z�b�g
          newCapsule.SetPosition(newPos);
          // �����̎擾
          auto [start, end] = newCapsule.LineSegment().GetVector();
          // 
          const auto player = _app.GetObjectServer().GetPlayer();
          // �n�`(��)�Ɛ����̏Փ˔���
          auto hit = MV1CollCheck_Line(player->StageHandle(), 2, UtilityDX::ToVECTOR(end), UtilityDX::ToVECTOR(start));
          // �Փ˃t���O���Ȃ��ꍇ
          if (hit.HitFlag == 0) {
            // �V�������W���Z�b�g
            _position = newPos;
            // �R���W�������ɍX�V��������
            _capsule->SetPosition(_position);
            return false; // ���ɗ����Ă��Ȃ�
          }
          // �Փˍ��W�����W�ɑ��
          _position = UtilityDX::ToVector(hit.HitPosition);
          // �V�������W���R���W�����ɔ��f
          _capsule->SetPosition(_position);
          return true; // ���ɗ����Ă���
        }
    } // namespace Enemy
} // namespace Gyro
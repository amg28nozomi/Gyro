/*****************************************************************//**
 * @file    EnemyWheel.cpp
 * @brief   �G�N���X
 *
 * @author  �{�V�s��
 * @date    January 2022
 *********************************************************************/
#include "EnemyWheel.h"
#include "../CollisionSphere.h"
#include "../UtilityDX.h"
#include "../ApplicationMain.h"

namespace Gyro {
    namespace Enemy {
        EnemyWheel::EnemyWheel(Application::ApplicationMain& app) : EnemyBase(app) {
            // ������
            Init();
        }

        EnemyWheel::~EnemyWheel() {

        }

        bool EnemyWheel::Init() {
          // ���f���ǂݍ���
          auto[handle, key] = _app.GetModelServer().GetModel("enemy", 0);
          _mHandle = handle; // �n���h���ݒ�
          // MV1SetScale(_mHandle, VGet(1.0f, 1.0f, 1.0f));
          // �A�j���[�V�����A�^�b�`
          _modelAnim.SetMainAttach(_mHandle, 1, 1.0f, true);
          // ������
          MV1SetScale(_mHandle, VGet(2,2,2));
          SetEnemyPos(VGet(100, 0, 100));
          _position = UtilityDX::ToVector(_enemyPos);
          auto center = UtilityDX::ToVector(_enemyPos);
          center.AddY(100.0f);
          _sphere = std::make_unique<Object::CollisionSphere>(*this, center, 50.0f);
          _enemyDir = VGet(0, 0, 1);
          _enemyMoveSpeed = 5.0f;
          // �J�v�Z���R���W�����̐ݒ�
          _capsule = std::make_unique<Object::CollisionCapsule>(*this, _position, 200.0f, 20.0f);
          return true;
        }

        bool EnemyWheel::Process() {
            EnemyState oldEnemyState = _enemyState;
            VECTOR target = VGet(0, 0, 0);
            VECTOR forword = VSub(target, _enemyPos);
            forword = VNorm(forword);
            VECTOR move = VScale(forword, _enemyMoveSpeed);
            // _sphere->Process();

            if (CheckHitKey(KEY_INPUT_A)) {
                _enemyState = EnemyState::WALK;
                _enemyPos = VAdd(_enemyPos, move);
                _enemyDir = forword;
            }
            else {
                _enemyState = EnemyState::WAIT;
            }

            // �A�j���[�V�����ύX
            if (oldEnemyState != _enemyState) {
                switch (_enemyState) {
                case EnemyState::WAIT:
                    _modelAnim.SetBlendAttach(1, 10.0f, 1.0f, true);
                    break;
                case EnemyState::WALK:
                    _modelAnim.SetBlendAttach(2, 10.0f, 1.0f, true);
                    break;
                case EnemyState::ATTACK:
                    _modelAnim.SetBlendAttach(0, 10.0f, 1.0f, false);
                    break;
                case EnemyState::DEAD:
                    //_modelAnim.SetBlendAttach(1, 10.0f, 1.0f, false);
                    break;
                default:
                    break;
                }
            }

            _modelAnim.Process();
            return true;
        }

        bool EnemyWheel::Draw() const {
          EnemyBase::Draw(); // ��ꑤ�̕`������s
#ifdef _DEBUG
          // �f�o�b�O�t���O������ꍇ�̂ݕ`�揈�����s��
          if (_app.GetDebugFlag()) {
            _capsule->Draw(); // �����蔻��̕`��
          }
#endif
          return true; // �`��
        }
    } // namespace Enemy
} // namespace Gyro
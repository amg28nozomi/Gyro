/*****************************************************************//**
 * @file    EnemyWheel.cpp
 * @brief   �G�N���X
 *
 * @author  �{�V�s��
 * @date    January 2022
 *********************************************************************/
#include "EnemyWheel.h"

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
            _mHandle = MV1LoadModel("res/Spider_3.mv1");
            MV1SetScale(_mHandle, VGet(1.0f, 1.0f, 1.0f));
            // �A�j���[�V�����A�^�b�`
            _modelAnim.SetMainAttach(_mHandle, 14, 1.0f, true);
            // ������
            _enemyDir = VGet(0, 0, 1);
            _enemyMoveSpeed = 5.0f;
            return true;
        }

        bool EnemyWheel::Process() {
            EnemyState oldEnemyState = _enemyState;
            VECTOR target = VGet(0, 0, 0);
            VECTOR forword = VSub(target, _enemyPos);
            forword = VNorm(forword);
            VECTOR move = VScale(forword, _enemyMoveSpeed);

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
                    _modelAnim.SetBlendAttach(14, 10.0f, 1.0f, true);
                    break;
                case EnemyState::WALK:
                    _modelAnim.SetBlendAttach(7, 10.0f, 1.0f, true);
                    break;
                case EnemyState::ATTACK:
                    _modelAnim.SetBlendAttach(0, 10.0f, 1.0f, false);
                    break;
                case EnemyState::DEAD:
                    _modelAnim.SetBlendAttach(1, 10.0f, 1.0f, false);
                    break;
                default:
                    break;
                }
            }

            _modelAnim.Process();
            return true;
        }
    } // namespace Enemy
} // namespace Gyro
/*****************************************************************//**
 * @file    EnemyWheel.cpp
 * @brief   �G�N���X
 *
 * @author  �{�V�s��
 * @date    January 2022
 *********************************************************************/
#include "EnemyWheel.h"
#include <DxLib.h>
#include "../CollisionSphere.h"
#include "../UtilityDX.h"
#include "../ApplicationMain.h"
#include "../ObjectServer.h"
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
          //MV1SetScale(_mHandle, VGet(2,2,2));
          _scale = { 2.0f, 2.0f, 2.0f };
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
            AppMath::Vector4 target = AppMath::Vector4();
            AppMath::Vector4 prot = AppMath::Vector4();
            _app.GetObjectServer().GetPlayerTransForm(target, prot);
            AppMath::Vector4 forword = target-(_position);
            forword.Normalize();
            AppMath::Vector4 move = forword*(_enemyMoveSpeed);
            // _sphere->Process();

                            // ���W�A���𐶐�(z���͔��]������)
            auto radian = std::atan2(move.GetX(), -move.GetZ());

            if (_app.GetOperation().GetXBoxState().GetButton(XINPUT_BUTTON_LEFT_THUMB, true)) {
                _enemyState = EnemyState::WALK;
                _position.Add(move);
                _capsule->Process(move);
#ifndef _DEBUG
                _rotation.SetY(radian); // y���̉�]�ʂ��Z�b�g����
#else
                // �f�O���[�l���Z�b�g����(�f�o�b�O�p)
                _rotation.SetY(AppMath::Utility::RadianToDegree(radian));
#endif

        }
            else {
                _enemyState = EnemyState::WAIT;
            }

            WorldMatrix(); // ���[���h���W�̍X�V
                  // ���[���h���W�̐ݒ�
            MV1SetMatrix(_mHandle, UtilityDX::ToMATRIX(_world));

            // �A�j���[�V�����ύX
            if (oldEnemyState != _enemyState) {
                switch (_enemyState) {
                case EnemyState::WAIT:
                    _modelAnim.SetBlendAttach(1, 10.0f, 1.0f, true);
                    break;
                case EnemyState::WALK:
                    _modelAnim.SetBlendAttach(2, 10.0f, 1.0f, true);
                    _eff.PlayEffect();
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
            _eff.SetPosition(_position);
            _eff.SetDirection(radian);
            _eff.Process();
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
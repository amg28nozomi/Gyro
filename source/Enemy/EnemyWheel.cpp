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
#include "../Player.h"

namespace {
    // �A�j���[�V�����L�[
    constexpr std::string_view IdleKey = "EnemyIdle";       //!< �ҋ@
    constexpr std::string_view MoveKey = "EnemyMove";       //!< �ړ�
    constexpr std::string_view AttackKey = "EnemyAttack";   //!< �U��
}

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
          auto[handle, key] = _app.GetModelServer().GetModel("enemy", _number);
          ++_number;
          _mHandle = handle; // �n���h���ݒ�
          _this = key;
          // �A�j���[�V�����A�^�b�`
          _modelAnim.SetMainAttach(_mHandle, IdleKey, 1.0f, true);
          _enemyMoveSpeed = 5.0f;
          return true;
        }

        bool EnemyWheel::Process() {
          // ���N���X�̍X�V�������Ăяo��
          EnemyBase::Process();
          // �O�t���[���̏��
          EnemyState oldEnemyState = _enemyState;
          // �댯�֐�
          ImageMove();
//            if (_iMove) {
//                _enemyState = EnemyState::Move;
//                _position.Add(move);
//                _capsule->Process(move);
//#ifndef _DEBUG
//                _rotation.SetY(radian); // y���̉�]�ʂ��Z�b�g����
//#else
//                // �f�O���[�l���Z�b�g����(�f�o�b�O�p)
//                _rotation.SetY(AppMath::Utility::RadianToDegree(radian));
//#endif
//
//        }
//            else {
//                _enemyState = EnemyState::Idle;
//            }
            Hit();         // �Փ˔���
            WorldMatrix(); // ���[���h���W�̍X�V
            // ���[���h���W�̐ݒ�
            MV1SetMatrix(_mHandle, UtilityDX::ToMATRIX(_world));

            // �A�j���[�V�����ύX
            if (oldEnemyState != _enemyState) {
              auto ePos = _position;
#ifndef _DEBUG
              auto eRad = -_rotation.GetY();
#else
              auto eRad = -AppMath::Utility::DegreeToRadian(_rotation.GetY());
#endif
              switch (_enemyState) {
                case EnemyState::Idle:
                    _modelAnim.SetBlendAttach(IdleKey, 10.0f, 1.0f, true);
                    break;
                case EnemyState::Move:
                    _modelAnim.SetBlendAttach(MoveKey, 10.0f, 1.0f, false);
                    ePos.AddY(135.0f);
                    _app.GetEffect().PlayEffect(Effect::eEyeLight, ePos, eRad);
                    break;
                case EnemyState::Attack:
                    _modelAnim.SetBlendAttach(AttackKey, 10.0f, 1.0f, false);
                    _app.GetEffect().PlayEffect(Effect::eGroundAttack, ePos, eRad);
                    break;
                case EnemyState::Dead:
                    //_modelAnim.SetBlendAttach(1, 10.0f, 1.0f, false);
                  _app.GetEffect().PlayEffect(Effect::eExprosion, ePos, eRad);
                    break;
                default:
                    break;
                }
            }
            _gaugeHp.Process();

            _modelAnim.Process();
            // ���G��Ԃł͂Ȃ��ꍇ�A�_���[�W������s��
            if (!_invincible->Invincible()) {
              IsDamege();
            }
            return true;
        }

        bool EnemyWheel::Draw() const {
          EnemyBase::Draw(); // ��ꑤ�̕`������s
          _gaugeHp.Draw();
#ifdef _DEBUG
          // �f�o�b�O�t���O������ꍇ�̂ݕ`�揈�����s��
          if (_app.GetDebugFlag()) {
            _capsule->Draw(); // �����蔻��̕`��
          }
#endif
          return true; // �`��
        }

        void EnemyWheel::SetCollision() {
          // ���̓����蔻��ݒ�
          _sphere = std::make_unique<Object::CollisionSphere>(*this, _position.AddVectorY(100.0f), 50.0f);
          // �J�v�Z���R���W�����̐ݒ�
          _capsule = std::make_unique<Object::CollisionCapsule>(*this, _position, 200.0f, 30.0f);
        }

        void EnemyWheel::Hit() {
          auto objects = _app.GetObjectServer().GetObjects(); // �I�u�W�F�N�g�̃R�s�[
          // �Փ˔�����s��
          for (auto obj : objects) {
            // �G�̏ꍇ�̂ݏ������s��
            if (obj->GetId() != ObjectId::Enemy) continue;
            // ��v���Ă���ꍇ�͏��O
            if (std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->Equals(_mHandle)) {
              continue; // ����I�u�W�F�N�g�̂��ߏ��O
            }
            // ���Ƌ��̏Փ˔���
            if (_sphere->IntersectSphere(std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCollision())) {
              // �Փ˂����ꍇ�͉����o���������s��
            }
            // �J�v�Z���ƃJ�v�Z���̏Փ˔���
            if (_capsule->IntersectCapsule(std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCapsule())) {
              // �Փ˂��Ă���ꍇ�͉����o���������s��
              auto y = _position.GetY(); // Y���W�͕ύX���s��Ȃ�
              // ��̍��W���牟���o���͂��Z�o����
              auto mPos = _capsule->GetPosition();
              auto ePos = std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCapsule().GetPosition();
              auto v = (mPos - ePos);   // ���S����
              auto length2 = v.LengthSquared(); // ��_�Ԃ̒������Z�o
              auto radius2 = _capsule->GetRadius() + std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCapsule().GetRadius();

              auto l7 = radius2 - std::sqrtf(v.GetX() * v.GetX() + v.GetZ() * v.GetZ());
              v.Normalize();
              AppMath::Vector4 vv(v.GetX() * l7, 0.0f, v.GetZ());
              _position.Add(vv);
              _capsule->SetPosition(_position);
            }
          }
        }

        bool EnemyWheel::IsDamege() {
          // ���G��Ԃ��̔���

          // ���@�̎擾
          const auto player = _app.GetObjectServer().GetPlayer();
          // �U���R���|�[�l���g�̎擾
          auto attack = player->AttackComponent();
          using AtkComponent = Object::AttackComponent;
          // �Ώۂ͍U����Ԃ��H
          if (attack.GetState() == AtkComponent::AttackState::NonActive) {
            return false; // �U����Ԃł͂Ȃ�
          }
          // �U����Ԃ̏ꍇ�͍U���R���W�����Ɠ����蔻����s��
          if (_capsule->IntersectSphere(*std::dynamic_pointer_cast<Object::CollisionSphere>(attack.GetCollision()))) {
#ifdef _DEBUG
            if (_app.GetDebugFlag()) {
              // ���S��ԂɑJ�ڂ���
              _state = ObjectState::Dead;
            }
            // �Փˎ��ɑΏۋ��̐F��ς���
            std::dynamic_pointer_cast<Object::CollisionSphere>(attack.GetCollision())->HitOn();
#endif
            _gaugeHp.Add(11.0f);
            // �Փ˃t���O������ꍇ�͖��G���Ԃ��J�n����
            _invincible->Start();
            return true; // �Փ˔���
          }
          return false;  // �Փ˂Ȃ�
        }

        // ���\�p�K������
        void EnemyWheel::ImageMove() {
          // �^�[�Q�b�g���W
          auto target = AppMath::Vector4();
          auto prot = AppMath::Vector4();
          _app.GetObjectServer().GetPlayerTransForm(target, prot);
          AppMath::Vector4 forword = target - (_position);
          forword.Normalize();
          AppMath::Vector4 move = forword * (_enemyMoveSpeed);
          // _sphere->Process();

          // ���W�A���𐶐�(z���͔��]������)
          auto radian = std::atan2(move.GetX(), -move.GetZ());
          // ���͏���������ꍇ�A�X�V���s��
          if (_app.GetOperation().GetXBoxState().GetButton(XINPUT_BUTTON_LEFT_THUMB, false)) {
            _iMove = true;
            _enemyState = EnemyState::Move;
          }

          if (_iMove) {
            if (_enemyState == EnemyState::Attack) {
              if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
                _enemyState = EnemyState::Idle;
                _iMove = false;
              }
            }
            if (_enemyState == EnemyState::Move) {
              if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
                _enemyState = EnemyState::Attack;
              }
              _position.Add(move);
              _capsule->Process(move);
#ifndef _DEBUG
              _rotation.SetY(radian); // y���̉�]�ʂ��Z�b�g����
#else
              // �f�O���[�l���Z�b�g����(�f�o�b�O�p)
              _rotation.SetY(AppMath::Utility::RadianToDegree(radian));
#endif
            }
          }
          else {
            _enemyState = EnemyState::Idle;
          }
        }
    } // namespace Enemy
} // namespace Gyro
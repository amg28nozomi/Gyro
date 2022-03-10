/*****************************************************************//**
 * @file    EnemyDrone.cpp
 * @brief   �󒆓G�N���X
 *
 * @author  �y������
 * @date    March 2022
 *********************************************************************/
#include "EnemyDrone.h"
#include "UtilityDX.h"
#include "ObjectServer.h"
#include "Player.h"

namespace {
  // �e��萔
  constexpr int DroneHP = 8500;           //!< �n��G�ő�̗�
  constexpr float DroneMoveSpead = 5.0f;  //!< �n��I�ړ����x
  constexpr float Height = 380.0f;        //!< ����
  // �A�j���[�V�����L�[
  constexpr std::string_view IdleKey = "Move";      //!< �ҋ@
  constexpr std::string_view MoveKey = "Move";      //!< �ړ�
  constexpr std::string_view AttackKey = "Attack";  //!< �U��
  constexpr std::string_view DamageKey = "Damage";  //!< �_���[�W
  constexpr std::string_view DeadKey = "Destroy1";  //!< ���S
}

namespace Gyro {
  namespace Enemy {
    EnemyDrone::EnemyDrone(Application::ApplicationMain& app) : EnemyBase(app) {
      // ������
      Init();
      _gravity = true;
    }

    EnemyDrone::~EnemyDrone() {

    }

    bool EnemyDrone::Init() {
      // ���f���ǂݍ���
      LoadModel();
      // �p�����[�^�̐ݒ�
      SetParameter();
      // �A�j���[�V�����A�^�b�`
      _modelAnim.SetMainAttach(_mHandle, IdleKey, 1.0f, true);

      return true;
    }

    bool EnemyDrone::Process() {
      // ���N���X�̍X�V�������Ăяo��
      EnemyBase::Process();
      // �O�t���[���̏��
      EnemyState oldEnemyState = _enemyState;
      // ���G�͈͂ɓ��������Ԃ�Move�ɕω�
      // ��Ԃ��ǂ�
      switch (_enemyState) {
      case Gyro::Enemy::EnemyBase::EnemyState::Move:
        Move();  //!< �ړ�
        Sercth(); //!< �T��
        break;
      case Gyro::Enemy::EnemyBase::EnemyState::Attack:
        Attack();  //!< �U��
        break;
      case EnemyState::Damage:
        NockBack(); //!< �m�b�N�o�b�N
        break;
      case Gyro::Enemy::EnemyBase::EnemyState::Dead:
        Dead();  //!< ���S
        break;
      default:
        _enemyState = EnemyState::Idle;
        Sercth(); //!< �T��
        break;
      }
      // �Փ˔���
      Hit();
      // ���G��Ԃł͂Ȃ��ꍇ�A�_���[�W������s��
      if (!_invincible->Invincible()) {
        IsDamege();
      }
      // ���[���h���W�̍X�V
      WorldMatrix();
      // ���[���h���W�̐ݒ�
      MV1SetMatrix(_mHandle, UtilityDX::ToMATRIX(_world));
      // �n�`�Ƃ̓����蔻��
      //IsStand();
      // ��O�ɏo�������S����悤�ɂ���
      if (_position.GetY() < -100.0f) {
        _enemyHP -= 50000;
        _gaugeHp->Sub(50000);
      }
      if (_enemyHP <= 0) {
        _enemyState = EnemyState::Dead;
      }
      // ��ԑJ�ڂ�����
      if (IsChangeState(oldEnemyState)) {
        // �A�j���[�V�����ύX
        ChangeAnim();
        // �G�t�F�N�g�Đ�
        PlayEffect();
      }
      // �̗̓Q�[�W�̍X�V
      _gaugeHp->Process();
      // ���f���A�j���̍X�V
      _modelAnim.Process();

      return true;
    }

    bool EnemyDrone::Draw() const {
      // ��ꑤ�̕`��
      EnemyBase::Draw();
      // �̗̓Q�[�W�̕`��
      _gaugeHp->Draw(_position, Height);
#ifdef _DEBUG
      // �f�o�b�O�t���O������ꍇ�̂ݕ`�揈�����s��
      if (_app.GetDebugFlag()) {
        // �����蔻��̕`��
        if (_enemyState == EnemyState::Attack) {
          _sphere->Draw();
        }
        _capsule->Draw();
        auto pos = _position.AddVectorY(10.0f);
        DrawCone3D(UtilityDX::ToVECTOR(pos), UtilityDX::ToVECTOR(_position), _attackRadius, 16, GetColor(255, 0, 0), GetColor(255, 255, 255), false);
        DrawCone3D(UtilityDX::ToVECTOR(pos), UtilityDX::ToVECTOR(_position), _serchRadius, 16, GetColor(0, 0, 255), GetColor(255, 255, 255), false);
      }
#endif
      return true;
    }

    void EnemyDrone::LoadModel() {
      // ���f���n���h���̎擾
      auto [handle, key] = _app.GetModelServer().GetModel("enemyDrone", _number);
      // ���f���f�[�^�ݒ�
      ++_number;
      _mHandle = handle;
      _this = key;
    }

    void EnemyDrone::SetParameter() {
      // �e��ݒ�
      _enemyHP = DroneHP;
      _gaugeHp = std::make_shared<Gauge::GaugeEnemy>(_app);
      _gaugeHp->Init(DroneHP);
      _serchRadius = 300.0f;
      _attackRadius = 100.0f;
      _sort = 0;
      _gravity = false;
    }

    void EnemyDrone::SetCollision() {
      // ���̓����蔻��ݒ�
      _sphere = std::make_unique<Object::CollisionSphere>(*this, _position.AddVectorY(100.0f), 50.0f);
      // �J�v�Z���R���W�����̐ݒ�
      _capsule = std::make_unique<Object::CollisionCapsule>(*this, _position, 300.0f, 50.0f);
    }

    void EnemyDrone::Move() {
      using Vector4 = AppMath::Vector4;
      // �^�[�Q�b�g���W
      auto target = Vector4();
      auto prot = AppMath::Vector4();
      _app.GetObjectServer().GetPlayerTransForm(target, prot);
      auto forward = _position.Direction(target);
      // ����������Ȃ��̂ŕ�������y�ȊO�����o��
      auto [x, y, z] = forward.GetVector3();
      auto efor = AppMath::Vector4(x, 0.0f, z);
      // ���K��
      efor.Normalize();
      auto move = efor * (DroneMoveSpead);
      // _sphere->Process();
      // ���W�A���𐶐�(z���͔��]������)
      auto radian = std::atan2(move.GetX(), -move.GetZ());
      _position.Add(move);
      _capsule->Process(move);
#ifndef _DEBUG
      _rotation.SetY(radian); // y���̉�]�ʂ��Z�b�g����
#else
      // �f�O���[�l���Z�b�g����(�f�o�b�O�p)
      _rotation.SetY(AppMath::Utility::RadianToDegree(radian));
#endif
      if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
        _enemyState = EnemyState::Idle;
      }
    }

    void EnemyDrone::Attack() {
      // �A�j���[�V��������w�肵���{�[���̃��[�J�����W���擾
      auto attachIndex = _modelAnim.GetMainAttachIndex();
      auto rPos = MV1GetFramePosition(_mHandle, 4);
      _sphere->SetPosition(UtilityDX::ToVector(rPos));
      _sphere->Process();
      _oldPosition = _position;
      // �A�j���[�V�����I����Idle�ֈڍs
      if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
        _enemyState = EnemyState::Idle;
        _iMove = false;
      }
    }

    void EnemyDrone::NockBack() {
      if (_cnt > 0) {
        // ���@�̎擾
        const auto player = _app.GetObjectServer().GetPlayer();
        // �m�b�N�o�b�N�x�N�g����ݒ�
        auto knockBackVector = _position - player.get()->GetPosition();
        // ����������Ȃ��̂ł��ȊO�𕪉����Ď��o��
        auto [x, y, z] = knockBackVector.GetVector3();
        auto knockBack = AppMath::Vector4(x, 0.0f, z);
        knockBack.Normalize();
        auto kB = knockBack * 10;
        _position.Add(kB);
        _capsule->SetPosition(_position);
      }
      else {
        _enemyState = EnemyState::Idle;
      }
    }

    void EnemyDrone::Hit() {
      // �I�u�W�F�N�g�̃R�s�[
      auto objects = _app.GetObjectServer().GetObjects();
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

    void EnemyDrone::ChangeAnim() {
      // �Ή��A�j���[�V�����؂�ւ�
      switch (_enemyState) {
      case EnemyState::Idle:    //!< �ҋ@
        _modelAnim.SetBlendAttach(IdleKey, 10.0f, 1.0f, true);
        break;
      case EnemyState::Move:    //!< �ړ�
        _modelAnim.SetBlendAttach(MoveKey, 10.0f, 1.0f, false);
        break;
      case EnemyState::Attack:  //!< �U��
        _modelAnim.SetBlendAttach(AttackKey, 10.0f, 1.0f, false);
        break;
      case EnemyState::Damage:  //!< ��_��
        _modelAnim.SetBlendAttach(DamageKey, 10.0f, 1.0f, false);
        break;
      case EnemyState::Dead:    //!< ���S
        _modelAnim.SetBlendAttach(DeadKey, 10.0f, 1.0f, false);
        break;
      default:
        break;
      }
    }

    void EnemyDrone::PlayEffect() {
      // �p�����[�^�ݒ�
      auto ePos = _position;
#ifndef _DEBUG
      auto eRad = -_rotation.GetY();
#else
      auto eRad = -AppMath::Utility::DegreeToRadian(_rotation.GetY());
#endif
      // �Ή��G�t�F�N�g�Đ�
      switch (_enemyState) {
      case EnemyState::Idle:    //!< �ҋ@
        break;
      case EnemyState::Move:    //!< �ړ�
        ePos.AddY(300.0f);
        _app.GetEffectServer().MakeEffect(EffectNum::EnemyEyeLight, ePos, eRad);
        break;
      case EnemyState::Attack:  //!< �U��
        _app.GetEffectServer().MakeEffect(EffectNum::EnemyAirAttack, ePos, eRad);
        break;
      case EnemyState::Damage:  //!< ��_��
        ePos.AddY(100.0f);
        _app.GetEffectServer().MakeEffect(EffectNum::EnemyHit, ePos, eRad);
        break;
      case EnemyState::Dead:    //!< ���S
        ePos.AddY(100.0f);
        _app.GetEffectServer().MakeEffect(EffectNum::EnemyExprosion, ePos, eRad);
        break;
      default:
        break;
      }
    }

    bool EnemyDrone::IsDamege() {
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
        // �Փˎ��ɑΏۋ��̐F��ς���
        std::dynamic_pointer_cast<Object::CollisionSphere>(attack.GetCollision())->HitOn();
#endif
        _enemyHP -= 1000;
        _gaugeHp->Sub(1000);
        if (_enemyHP <= 0) {
          _enemyState = EnemyState::Dead;
        }
        else {
          _enemyState = EnemyState::Damage;
          _cnt = 20;
        }
        // �Փ˃t���O������ꍇ�͖��G���Ԃ��J�n����
        //_invincible->Start();
        return true; // �Փ˔���
      }
      return false;  // �Փ˂Ȃ�
    }
  } // namespace Enemy
} // namespace Gyro
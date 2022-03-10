/*****************************************************************//**
 * @file    EnemyWheel.cpp
 * @brief   �n��G�{�X�N���X
 *
 * @author  �y������
 * @date    March 2022
 *********************************************************************/
#include "EnemyWheelBoss.h"
#include "UtilityDX.h"
#include "ObjectServer.h"
#include "Player.h"
#include <algorithm>

namespace {
  // �e��萔
  constexpr int WheelHP = 10000;          //!< �n��G�ő�̗�
  constexpr float WheelMoveSpead = 5.0f;  //!< �n��I�ړ����x
  constexpr float WheelAttackSpead = 10.0f;  //!< �n��I�U���ړ����x
  constexpr float Height = 530.0f;        //!< ����
  // �A�j���[�V�����L�[
  constexpr std::string_view IdleKey = "idle";      //!< �ҋ@
  constexpr std::string_view MoveKey = "idle";      //!< �ړ�
  constexpr std::string_view AttackKey = "attack";  //!< �U��
  constexpr std::string_view AttackReadyKey = "attack_ready";  //!< �U������
  constexpr std::string_view AttackFinishKey = "attack_finish"; //!< �U���I��
  constexpr std::string_view DamageKey = "damage";  //!< �_���[�W
  constexpr std::string_view DeadKey = "dead";      //!< ���S
}

namespace Gyro {
  namespace Enemy {
    EnemyWheelBoss::EnemyWheelBoss(Application::ApplicationMain& app) : EnemyBase(app) {
      // ������
      Init();
      _gravity = true;
    }

    EnemyWheelBoss::~EnemyWheelBoss() {
    }

    bool EnemyWheelBoss::Init() {
      // ���f���ǂݍ���
      LoadModel();
      // �p�����[�^�̐ݒ�
      SetParameter();
      // �A�j���[�V�����A�^�b�`
      _modelAnim.SetMainAttach(_mHandle, IdleKey, 1.0f, true);

      return true;
    }

    bool EnemyWheelBoss::Process() {
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
      case Gyro::Enemy::EnemyBase::EnemyState::AttackReady:
        AttackReady();
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

    bool EnemyWheelBoss::Draw() const {
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

    void EnemyWheelBoss::LoadModel() {
      // ���f���n���h���̎擾
      auto [handle, key] = _app.GetModelServer().GetModel("enemyWheelBoss", _number);
      // ���f���f�[�^�ݒ�
      ++_number;
      _mHandle = handle;
      _this = key;
    }

    void EnemyWheelBoss::SetParameter() {
      // �e��ݒ�
      _enemyHP = WheelHP;
      _gaugeHp = std::make_shared<Gauge::GaugeEnemy>(_app);
      _gaugeHp->Init(WheelHP);
      _serchRadius = 350.0f;
      _attackRadius = 200.0f;
      _sort = 0;
      _gravity = false;
    }

    void EnemyWheelBoss::SetCollision() {
      // ���̓����蔻��ݒ�
      _sphere = std::make_unique<Object::CollisionSphere>(*this, _position.AddVectorY(100.0f), 50.0f);
      // �J�v�Z���R���W�����̐ݒ�
      _capsule = std::make_unique<Object::CollisionCapsule>(*this, _position, 450.0f, 70.0f);
    }

    void EnemyWheelBoss::Move() {
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
      auto move = efor * (WheelMoveSpead);
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

    void EnemyWheelBoss::AttackReady() {
      // �^�[�Q�b�g���W
      auto target = AppMath::Vector4();
      auto prot = AppMath::Vector4();
      _app.GetObjectServer().GetPlayerTransForm(target, prot);
      auto forward = _position.Direction(target);
      // ����������Ȃ��̂ŕ�������y�ȊO�����o��
      auto [x, y, z] = forward.GetVector3();
      auto efor = AppMath::Vector4(x, 0.0f, z);
      auto move = efor * (WheelMoveSpead);
      // ���W�A���𐶐�(z���͔��]������)
      auto radian = std::atan2(move.GetX(), -move.GetZ());
      _rotation.SetY(radian); // y���̉�]�ʂ��Z�b�g����
      // �A�j���[�V�����I����Attack�ֈڍs
      if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
        _enemyState = EnemyState::Attack;
        _iMove = false;
      }
    }


    void EnemyWheelBoss::Attack() {
      if (_iMove != true) {
        _iMove = true;
        // �A�j���[�V��������w�肵���{�[���̃��[�J�����W���擾
        auto attachIndex = _modelAnim.GetMainAttachIndex();
        auto rPos = MV1GetFramePosition(_mHandle, 13);
        _sphere->SetPosition(UtilityDX::ToVector(rPos));
        _sphere->Process();
        // �^�[�Q�b�g���W
        auto target = AppMath::Vector4();
        auto prot = AppMath::Vector4();
        _app.GetObjectServer().GetPlayerTransForm(target, prot);
        auto forward = _position.Direction(target);
        // ����������Ȃ��̂ŕ�������y�ȊO�����o��
        auto [x, y, z] = forward.GetVector3();
        auto efor = AppMath::Vector4(x, 0.0f, z);
        // ���K��
        efor.Normalize();
        _move = efor * (WheelAttackSpead);
        _position.Add(_move);
        _capsule->Process(_move);
      }
      else {
        // �A�j���[�V��������w�肵���{�[���̃��[�J�����W���擾
        auto attachIndex = _modelAnim.GetMainAttachIndex();
        auto rPos = MV1GetFramePosition(_mHandle, 13);
        _sphere->SetPosition(UtilityDX::ToVector(rPos));
        _sphere->Process();
        _position.Add(_move);
        _capsule->Process(_move);
      }
      // �A�j���[�V�����I����Idle�ֈڍs
      if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
        _enemyState = EnemyState::Idle;
        _iMove = false;
      }
    }

    void EnemyWheelBoss::NockBack() {
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

    void EnemyWheelBoss::Sercth() {
      auto objects = _app.GetObjectServer().GetObjects(); // �I�u�W�F�N�g�̃R�s�[
      for (auto pla : objects) {
        if (pla->GetId() != ObjectId::Player) continue;
        auto position = pla->GetPosition();
        // �~�Ɠ_�̋���
        auto a = position.GetX() - _position.GetX();
        auto b = position.GetZ() - _position.GetZ();
        auto c = sqrt(a * a + b * b);
        // �����Ɣ��a���r���ď�ԕω�
        if (c < _attackRadius) {
          _enemyState = EnemyState::AttackReady;
          break;
        }
        else if (c < _serchRadius) {
          _enemyState = EnemyState::Move;
          break;
        }
        else {
          _enemyState = EnemyState::Idle;
          break;
        }
      }
    }

    void EnemyWheelBoss::Hit() {
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

    void EnemyWheelBoss::ChangeAnim() {
      // �Ή��A�j���[�V�����؂�ւ�
      switch (_enemyState) {
      case EnemyState::Idle:    //!< �ҋ@
        _modelAnim.SetBlendAttach(IdleKey, 10.0f, 1.0f, true);
        break;
      case EnemyState::Move:    //!< �ړ�
        _modelAnim.SetBlendAttach(MoveKey, 10.0f, 1.0f, false);
        break;
      case EnemyState::AttackReady:  //!< �U������
        _modelAnim.SetBlendAttach(AttackReadyKey, 10.0f, 1.0f, false);
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

    void EnemyWheelBoss::PlayEffect() {
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
        ePos.AddY(350.0f);
        _app.GetEffectServer().MakeEffect(EffectNum::EnemyBossEyeLight, ePos, eRad);
        break;
      case EnemyState::Attack:  //!< �U��
        ePos.AddY(0.0f);
        _app.GetEffectServer().MakeEffect(EffectNum::EnemyBossGroundAttack, ePos, eRad);
        break;
      case EnemyState::Damage:  //!< ��_��
        ePos.AddY(100.0f);
        _app.GetEffectServer().MakeEffect(EffectNum::EnemyBossHit, ePos, eRad);
        break;
      case EnemyState::Dead:    //!< ���S
        ePos.AddY(100.0f);
        _app.GetEffectServer().MakeEffect(EffectNum::EnemyBossExprosion, ePos, eRad);
        break;
      default:
        break;
      }
    }

    void EnemyWheelBoss::Dead() {
      // ��Ԃ�Paused�ɂ���
      _state = ObjectState::Paused;
      // �I�u�W�F�N�g�̃R�s�[
      auto objects = _app.GetObjectServer().GetObjects();
      // ���I�z��Ɉ�v����v�f�����邩���肷��
      auto activeBoss = std::any_of(objects.begin(), objects.end(),
        [](std::shared_ptr<Object::ObjectBase>& obj) {
          // ������Ԃ̓G�͂��邩
          return (obj->GetId() == Object::ObjectBase::ObjectId::Enemy) && obj->GetState() == ObjectState::Active; });
      // �A�j���[�V�����I����Dead�ֈڍs
      if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
        _state = ObjectState::Dead;
        // ������Ԃ̓G�����Ȃ���
        if (!activeBoss) {
          // �Q�[���N���A����
          _app.SetGameClear(true);
        }
      }
    }

    bool EnemyWheelBoss::IsDamege() {
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
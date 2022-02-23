/*****************************************************************//**
 * @file    EnemyBase.cpp
 * @brief   �G�̊��N���X
 *
 * @author  �{�V�s��
 * @date    January 2022
 *********************************************************************/
#include "EnemyBase.h"
#include "UtilityDX.h"
#include "ApplicationMain.h"
#include "ObjectServer.h"
#include "SpawnEnemy.h"
#include "Player.h"

namespace {
  // ���G����(�t���[��)
  constexpr auto InvincibleTime = 120;
}

namespace Gyro {
  namespace Enemy {
    EnemyBase::EnemyBase(Application::ApplicationMain& app) : Object::ObjectBase(app), _gaugeHp(app) {
      // ������
      Init();
    }

    EnemyBase::~EnemyBase() {

    }

    bool EnemyBase::Init() {
      // ������
      SetParameter();
      // ���G�����̐���
      _invincible = std::make_unique<Object::InvincibleComponent>(_app);
      // ���G���Ԃ̐ݒ�
      _invincible->Set(InvincibleTime);

      return true;
    }

    bool EnemyBase::Process() {
      // ���N���X�̍X�V�������Ăяo��
      ObjectBase::Process();
      // ���G��Ԃ�
      if (_invincible->Invincible()) {
        // ���G���Ԃ̌o�ߏ������Ăяo��
        _invincible->Process();
      }
      // �J�E���g��1�ȏ゠�邩�H
      if (_cnt > 0) {
          _cnt--;
      }

      return true;
    }

    bool EnemyBase::Draw() const {
      // ���S��Ԃ̏ꍇ�͕`����s��Ȃ�
      if (_state != ObjectState::Dead) {
        // �`��
        MV1DrawModel(_mHandle);
      }
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

    void EnemyBase::LoadModel() {

    }

    void EnemyBase::SetParameter() {
      _id = ObjectId::Enemy;
      _enemyState = EnemyState::Idle;
    }

    void EnemyBase::SetCollision() {

    }

    void EnemyBase::Move() {

    }

    void EnemyBase::Attack() {

    }

    void EnemyBase::Sercth(const float radius) {
      auto objects = _app.GetObjectServer().GetObjects(); // �I�u�W�F�N�g�̃R�s�[
      for (auto pla : objects) {
          if (pla->GetId() != ObjectId::Player) continue;
          auto position = pla->GetPosition();
          auto a = position.GetX() - _position.GetX();
          auto b = position.GetZ() - _position.GetZ();
          auto c = sqrt(a * a + b * b);
          if (c < radius) {
              _enemyState = EnemyState::Move;
          }
      }
    }

    void EnemyBase::Hit() {
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

    void EnemyBase::ChangeAnim() {
      // �Ή��A�j���[�V�����؂�ւ�
      switch (_enemyState) {
      case EnemyState::Idle:    //!< �ҋ@
        break;
      case EnemyState::Move:    //!< �ړ�
        break;
      case EnemyState::Attack:  //!< �U��
        break;
      case EnemyState::Damage:  //!< ��_��
        break;
      case EnemyState::Dead:    //!< ���S
        break;
      default:
        break;
      }
    }

    void EnemyBase::PlayEffect() {
      // �Ή��G�t�F�N�g�Đ�
      switch (_enemyState) {
      case EnemyState::Idle:    //!< �ҋ@
        break;
      case EnemyState::Move:    //!< �ړ�
        break;
      case EnemyState::Attack:  //!< �U��
        break;
      case EnemyState::Damage:  //!< ��_��
        break;
      case EnemyState::Dead:    //!< ���S
        break;
      default:
        break;
      }
    }

    void EnemyBase::Dead() {
      _state = ObjectState::Dead;
      // �I�u�W�F�N�g�T�[�o�Ɏ��S�������s��
      // _app.GetObjectServer().
    }

    bool EnemyBase::IsDamege() {
      // �e��f�[�^�̎擾
      const auto player = _app.GetObjectServer().GetPlayer();
      auto attack = player->AttackComponent();
      using AtkComponent = Object::AttackComponent;
      // �Ώۂ͍U����Ԃ��H
      if (attack.GetState() == AtkComponent::AttackState::NonActive) {
        return false; // �U����Ԃł͂Ȃ�
      }
      // �U����Ԃ̏ꍇ�͍U���R���W�����Ɠ����蔻����s��
      if (_capsule->IntersectCapsule(*std::dynamic_pointer_cast<Object::CollisionCapsule>(attack.GetCollision()))) {
        return true; // �Փ˔���
      }
      return false;  // �Փ˂Ȃ�
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
      // �v���C���[�̎擾
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
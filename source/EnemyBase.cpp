/*****************************************************************//**
 * @file    EnemyBase.cpp
 * @brief   �G�̊��N���X
 *
 * @author  �y������
 * @date    January 2022
 *********************************************************************/
#include "EnemyBase.h"
#include "ApplicationMain.h"
#include "UtilityDX.h"
#include "ObjectServer.h"
#include "SpawnEnemy.h"
#include "Player.h"
#include "StageComponent.h"

namespace {
  // ���G����(�t���[��)
  constexpr auto InvincibleTime = 120;
}

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
      // �����W
      _oldPosition = _position;
      // ���G��Ԃ�
      if (_invincible->Invincible()) {
        // ���G���Ԃ̌o�ߏ������Ăяo��
        _invincible->Process();
      }
      // �J�E���g��1�ȏ゠�邩�H
      if (_cnt > 0) {
          _cnt--;
      }
      // ��O�ɏo�������S����悤�ɂ���
      if (_position.GetY() < -100.0f) {
        _enemyHP -= 50000;
        _gaugeHp->Sub(50000);
      }
      if (_enemyHP <= 0) {
        _enemyState = EnemyState::Dead;
      }
      return true;
    }

    bool EnemyBase::Draw() const {
      // ���S��Ԃ̏ꍇ�͕`����s��Ȃ�
      if (_state != ObjectState::Dead) {
        // �`��
        MV1DrawModel(_modelHandle);
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

      _oldPosition = _position;
      // �����蔻��̐ݒ�
      SetCollision();
      // auto enemy = dynamic_cast<Object::SpawnEnemy*>(&spawn);
    }

    void EnemyBase::LoadModel() {
    }

    void EnemyBase::SetParameter() {
      _id = ObjectId::Enemy;
      _enemyState = EnemyState::Idle;
      _oldPosition = _position;
    }

    void EnemyBase::SetCollision() {
    }

    void EnemyBase::Move() {
    }

    void EnemyBase::Attack() {
    }

    void EnemyBase::NockBack() {
    }

    void EnemyBase::Search() {
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
          _enemyState = EnemyState::Attack; // �U����
          break;
        }
        else if (c < _serchRadius) {
          _enemyState = EnemyState::Move; // �ړ���
          break;
        }
        else {
          _enemyState = EnemyState::Idle; // �ҋ@��
          break;
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
        if (std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->Equals(_modelHandle)) {
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

    void EnemyBase::EffectInit() {
    }

    void EnemyBase::EffectProcess() {
    }

    void EnemyBase::EffectPlay() {
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

    void EnemyBase::EffectDead() {
    }

    void EnemyBase::Dead() {
      // �A�j���[�V�����I����Dead�ֈڍs
      if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
        _state = ObjectState::Dead;
      }
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

      auto flag = false;
      // �n�`(��)�Ɛ����̏Փ˔���
      for (int i = 0; i < _app.GetStageComponent().GetStageModel().size(); i++) {
        auto handleMap = _app.GetStageComponent().GetStageModel()[i];
        auto hit = MV1CollCheck_Line(handleMap, 2, UtilityDX::ToVECTOR(end), UtilityDX::ToVECTOR(start));
        // �Փ˃t���O���Ȃ��ꍇ
        if (hit.HitFlag == 0) {
          continue;
        }
        // �Փˍ��W�����W�ɑ��
        _position = UtilityDX::ToVector(hit.HitPosition);
        // �V�������W���R���W�����ɔ��f
        _capsule->SetPosition(_position);
        flag = true;
        break;
      }
      // �Փ˃t���O��false�̎�����
      if (flag == false) {
        // �V�������W���Z�b�g
        _position = newPos;
        // �R���W�������ɍX�V��������
        _capsule->SetPosition(_position);
      }
      return flag;
    }

    void EnemyBase::Extrude() {
      // �n�`�Ƃ̏Փ˔���
      auto newPosition = _position;
      // �R���W�����ƕǂ̉����o���������s��
      auto newCapsule = *_capsule;
      newCapsule.SetPosition(newPosition);
      auto radius = newCapsule.GetRadius(); // ���a�̎擾
      // ���f���n���h���̎擾
      auto stageMap = _app.GetStageComponent().GetStageModel();
      // �����o���t���O
      auto flag = false;
      // �n�`���f��(��)�Ƃ̏Փ˔���
      for (auto model : stageMap) {
        // �����̎擾
        auto [start, end] = newCapsule.LineSegment().GetVector();
        // �n�`�Ƃ̏Փ˔�����s��
        auto hit = MV1CollCheck_Capsule(model, 1, UtilityDX::ToVECTOR(start), UtilityDX::ToVECTOR(end), radius);
        // �ڐG�ӏ����Ȃ��ꍇ
        if (!hit.HitNum) {
          // �Փ˗p���̌�n�����s��
          MV1CollResultPolyDimTerminate(hit);
          continue;
        }
        // �X�V�t���O
        if (!flag) flag = true;
        // �q�b�g�����|���S���������o��
        //for (auto i = 0; i < hit.HitNum; ++i) {
        //  // �@���x�N�g�����x�N�g���N���X��
        //  auto v = Vector4(hit.Dim[i].Normal.x, hit.Dim[i].Normal.y, hit.Dim[i].Normal.z);
        //  // �@���x�N�g����
        //  newPosition.Add(v);
        //}
        // �ʖ���`
        using Vector4 = AppMath::Vector4;
        // �q�b�g�����|���S���񕪉����o��
        for (auto i = 0; i < hit.HitNum; ++i) {
          // �@���x�N�g���̎擾
          auto normal = Vector4(hit.Dim[i].Normal.x, hit.Dim[i].Normal.y, hit.Dim[i].Normal.z);
          // �X���C�h�x�N�g��
          auto slide = Vector4::Cross(normal, Vector4::Cross(_position - _oldPosition, normal));
          slide = Vector4::Scale(slide, Vector4(-1.0, 0.0f, -1.0f));
          // slide.SetY(0.0f);
          newPosition.Add(slide);
          newCapsule.SetPosition(newPosition);
        }
        // �Փ˔�����̌�n�����s��
        MV1CollResultPolyDimTerminate(hit);
      }
      // ���W���X�V����
      if (flag) {
        _position = newPosition;
        _capsule->SetPosition(newPosition);
      }
    }

    bool EnemyBase::ProcessFlag() {
      auto objects = _app.GetObjectServer().GetObjects(); // �I�u�W�F�N�g�̃R�s�[
      for (auto pla : objects) {
        if (pla->GetId() != ObjectId::Player) continue;
        auto position = pla->GetPosition();
        // �~�Ɠ_�̋���
        auto a = position.GetX() - _position.GetX();
        auto b = position.GetZ() - _position.GetZ();
        auto c = sqrt(a * a + b * b);
        // �����Ɣ��a���r����flag�ω�
        if (c < _flagRadius) {
          _gravity = true;
          return true;
          break;
        }
      }
      _gravity = false;
      return false;
    }
  } // namespace Enemy
} // namespace Gyro
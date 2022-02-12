/*****************************************************************//**
 * @file   Player.cpp
 * @brief  �I�u�W�F�N�g�x�[�X�̃T�u�N���X�̒�`
 *
 * @author �y������
 * @date   January 2022
 *********************************************************************/
#include "Player.h"
#include "ApplicationMain.h"
#include "UtilityDX.h"
#include "ObjectServer.h"
#include "Enemy/EnemyBase.h"
#include "CollisionCapsule.h"
#include "SpawnBase.h"
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )

namespace {
  constexpr auto NoAnimation = -1; //!< �A�j���[�V�����̓A�^�b�`����Ă��Ȃ�
  constexpr auto InputMin = 2000.0f;  //!< ���͂��󂯕t����Œ�l
  constexpr auto InputMax = 32767.0f;

  constexpr auto MoveSpeed = 5.0f; //!< �f�t�H���g�̈ړ���
  constexpr auto MoveZero = 0.0f;
  // �v���C���[�̃A�j���[�V�����L�[
  constexpr auto Idle = "GyroIdle";                     //!< �A�C�h��
  constexpr auto Walk = "GyroWalk";                     //!< ����
  constexpr auto Run = "GyroDash";                      //!< ����
  constexpr auto Step = "Gyro step";                    //!< �X�e�b�v
  constexpr auto JumpUp = "GyroJUp";                    //!< �W�����v�A�b�v
  constexpr auto JumpDown = "GyroJDown";                //!< �W�����v�_�E��(������)
  constexpr auto JumpLanding = "GyroJLand";             //!< �W�����v�����h(���n)
  constexpr auto GroundLightAttack1 = "GyroLaw1";       //!< �n���U��1
  constexpr auto GroundLightAttack2 = "GyroLaw2";       //!< �n���U��2
  constexpr auto GroundLightAttack3 = "GyroLaw3";       //!< �n���U��3
  constexpr auto GroundLightAttackEX = "GyroLawEx";     //!< �n��EX�U��(��́Y)
  constexpr auto GroundHeavyAttack1 = "GyroHigh1";      //!< �n�㋭�U��1
  constexpr auto GroundHeavyAttack2 = "GyroHigh2";      //!< �n�㋭�U��2
  constexpr auto GroundHeavyAttack3 = "GyroHigh3";      //!< �n�㋭�U��3
  constexpr auto AirLightAttack1 = "GyroJLaw1";         //!< �󒆎�U��1
  constexpr auto AirLightAttack2 = "GyroJLaw2";         //!< �󒆎�U��2
  constexpr auto AirLightAttack3 = "GyroJLaw3";         //!< �󒆎�U��3
  constexpr auto AirHeavyAttack1 = "GyroJHigh1";        //!< �󒆋��U��1
  constexpr auto AirHeavyAttack2 = "GyroJHigh2";        //!< �󒆋��U��2
  constexpr auto Damage1 = "Gyro damage1";              //!< ���_���[�W
  constexpr auto Damage2 = "Gyro damage2";              //!< ��_���[�W
  // �W�����v�t���O
  constexpr auto JumpPowe = 3.0f;
  constexpr auto JumpMax = 300.0f;
}

namespace Gyro {
  namespace Player {

    Player::Player(Application::ApplicationMain& app) : ObjectBase(app) {
      LoadResource(); // ���\�[�X�̓ǂݎ��
      Init();
    }

    bool Player::Init() {
      SetCamera(); // �J�����̐ݒ�
      SetState();  // �p�����[�^�̐ݒ�
      _modelAnim.SetMainAttach(_model, Idle, 1.0f, true);
      _gaugeHp.Init();
      _gaugeTrick.Init();
      return true;
    }

    bool Player::Process() {
      // �X�V�����Ăяo��
      ObjectBase::Process();
      // ���O��Ԃ̏ȗ�
      namespace App = AppFrame::Application;
      // ���͏�Ԃ̎擾
      auto input = _app.GetOperation().GetXBoxState();
      auto [lX, lY] = input.GetStick(false); // ���X�e�B�b�N
      auto [rX, rY] = input.GetStick(true);  // �E�X�e�B�b�N
      auto [leftTrigger, rightTrigger] = input.GetTrigger(); // �g���K�[�{�^��
      // �O�t���[�����W
      auto oldPosition = _position;
      // ���W�X�V
      _position = Move(AppMath::Vector4(lX, lY)); 
      // �J�����̍X�V
      // _app.GetCamera().Process(AppMath::Vector4(rX, rY), _position, _move);
      // �O�t���[���̏�Ԃ�ێ�
      auto oldState = _playerState;

      // �W�����v�����̓�������
      if (input.GetButton(XINPUT_BUTTON_A, false) && !_jump) {
        Jump(); // �W�����v����
      }


      // ��Ԃ̍X�V
      if (_playerState == PlayerState::Idle && _attackFlugY == false && input.GetButton(XINPUT_BUTTON_Y, false)) {
          _playerState = PlayerState::Attack1;
          _gaugeTrick.Add(-50.f);
          _attackFlugY = true;
          _cnt = 0;
      }else if (_playerState == PlayerState::Attack1 && _attackFlugY == true && input.GetButton(XINPUT_BUTTON_Y, false)) {
          _playerState = PlayerState::Attack2;
          _gaugeTrick.Add(-50.f);
          _cnt = 0;
      }else if (_playerState == PlayerState::Attack2 && _attackFlugY == true && input.GetButton(XINPUT_BUTTON_Y, false)) {
          _playerState = PlayerState::Attack3;
          _gaugeTrick.Add(-50.f);
          _cnt = 0;
      }
      if (_playerState == PlayerState::Idle && _attackFlugX == false && input.GetButton(XINPUT_BUTTON_X, false)) {
          _playerState = PlayerState::Attack1;
          _gaugeTrick.Add(-50.f);
          _attackFlugX = true;
          _cnt = 0;
      }else if (_playerState == PlayerState::Attack1 && _attackFlugX == true && input.GetButton(XINPUT_BUTTON_X, false)) {
          _playerState = PlayerState::Attack2;
          _gaugeTrick.Add(-50.f);
          _cnt = 0;
      }else if (_playerState == PlayerState::Attack2 && _attackFlugX == true && input.GetButton(XINPUT_BUTTON_X, false)) {
          _playerState = PlayerState::Attack3;
          _gaugeTrick.Add(-50.f);
          _cnt = 0;
      }
      if (_modelAnim.GetMainAnimEnd() == true && _attackFlugY == true) {
          _attackFlugY = false;
      }else if (_modelAnim.GetMainAnimEnd() == true && _attackFlugX == true) {
          _attackFlugX = false;
      }else if (_attackFlugX == false && _attackFlugY == false) {
          SetRotation(_move);
      }
      _cnt++;
      _gaugeHp.Process();
      _gaugeTrick.Process();
      Animation(oldState);      // �A�j���[�V�����̐ݒ�
      _modelAnim.Process();     // �A�j���[�V�����̍Đ�
      WorldMatrix();            // ���[���h���W�̍X�V
      _sphere->Process(_move);  // �ړ��ʂ̉��Z
      _capsule->Process(_move); // �J�v�Z���̍X�V
      Hit();
      // �J�����̍X�V
      _app.GetCamera().Process(AppMath::Vector4(rX, rY), _position, _move);
      // ���[���h���W�̐ݒ�
      MV1SetMatrix(_model, UtilityDX::ToMATRIX(_world));
      // ���f���̌�����ݒ肷��
      // MV1SetRotationXYZ(_model, UtilityDX::ToVECTOR(rotationY));
      // �X�J�C�X�t�B�A�̍��W
      auto skypos = AppMath::Utility::ToWorldMatrix(_position, AppMath::Vector4(0, 0, 0), AppMath::Vector4(1.0f, 1.0f, 1.0f));
      MV1SetMatrix(_handleSkySphere, UtilityDX::ToMATRIX(skypos));
      // MV1SetPosition(_handleSkySphere, UtilityDX::ToVECTOR(_position));
      auto stage = AppMath::Utility::ToWorldMatrix(AppMath::Vector4(0, -1500.0f, 0), AppMath::Vector4(0, 0, 0), AppMath::Vector4(1.0f, 1.0f, 1.0f));
      // �X�e�[�W�̍��W
      MV1SetMatrix(_handleMap, UtilityDX::ToMATRIX(stage));
      return true;
    }

    bool Player::Draw() const {
      // �v���C���[�̕`��
      MV1DrawModel(_model);
      // �X�J�C�X�t�B�A�̕`��
      MV1DrawModel(_handleSkySphere);
      // MV1DrawModel(_handleMap);
      _gaugeHp.Draw();
      _gaugeTrick.Draw();
#ifdef _DEBUG
      DebugDraw(); // �f�o�b�O�`��
#endif
      return true;
    }

    void Player::Set(Object::SpawnBase& spawn) {
      ObjectBase::Set(spawn);
      // �����蔻��̐ݒ���s��
      auto m = _position.AddVectorY(100.0f);
      // �e��R���W�����̐ݒ�
      _sphere = std::make_unique<Object::CollisionSphere>(*this, m, 100.0f);
      _capsule = std::make_unique<Object::CollisionCapsule>(*this, _position, 150.0f, 20.0f);
    }

    void Player::Input() {

    }

    AppMath::Vector4 Player::Move(AppMath::Vector4 move) {
        _move.Zero(); // �ړ��ʏ�����
        // �ړ��ʂ͂��邩
        if (move.LengthSquared() == 0.0f) {
          // ���ݍ��W�ɏd�̓X�P�[�������Z�����l��Ԃ�
          return _position;
        }
        auto x = (move.GetX() / 30000) * MoveSpeed; // x���̈ړ���
        auto z = (move.GetY() / 30000) * MoveSpeed; // y���̈ړ���
        _move.Set(x, _gravityScale, z); // �ړ��ʂ�ݒ�
        // ���W�A���𐶐�(y���͔��]������)
        auto radian = std::atan2(move.GetX(), -move.GetY());
#ifndef _DEBUG
        _rotation.SetY(radian); // y���̉�]�ʂ��Z�b�g����
#else
        // �f�O���[�l���Z�b�g����(�f�o�b�O�p)
        _rotation.SetY(AppMath::Utility::RadianToDegree(radian));
#endif
        return _position + _move;
    }

    void Player::LoadResource() {
      // �e�탊�\�[�X�̓ǂݎ�菈��
      auto [model, key1] = _app.GetModelServer().GetModel("player", 0);
      _model = model;     // ���f���n���h����o�^
      auto [handle, key2] = _app.GetModelServer().GetModel("sky", 0);
      _handleSkySphere = handle; // �X�J�C�X�t�B�A
      auto [stage , key3] = _app.GetModelServer().GetModel("stage", 0);
      _handleMap = stage; // �X�e�[�W�n���h��
    }

    void Player::SetCamera() {

    }


    void Player::SetState() {
      // ��Ԃ̐ݒ�
      _id = ObjectId::Player;
      _state = ObjectState::Active;
      _gravity = true; // �d�͏������s��
      // ���W�E�����̐ݒ�
      // �A�j���[�V�����̏�����
      _animaIndex = NoAnimation;
      _animaTime = 0.0f;
      _totalTime = 0.0f;
      // �n�`�̏Փ˔����ݒ�
      using Vector = AppFrame::Math::Vector4;
      // ���ʂ̐ݒ�
      auto a = Vector(0.0f, 0.0f, 100.0f);
      auto b = Vector(-100.0f, 0.0f, -100.0f);
      auto c = Vector(100.0f, 0.0f, -100.0f);
      _plane = std::make_unique<AppFrame::Math::Plane>(a, b, c);
    }

    void Player::CameraUpdate(const AppFrame::Math::Vector4 stick) {
      
    }

    void Player::SetRotation(const AppFrame::Math::Vector4 move) {
      // �ړ��ʂ�����ꍇ�͕������[�V�����ɑJ��
      // ����ړ��ʂɉ����ĕ����E�_�b�V�����[�V�����؂�ւ�
      if (move.LengthSquared()) {
        _playerState = PlayerState::Walk;
        _gaugeHp.Add(3.f);
      }
      else {
        _playerState = PlayerState::Idle;
      }
    }

    void Player::Animation(PlayerState old) {
        // ���@�̏�Ԃɍ��킹�ăA�j���[�V�����ω�
        if (old != _playerState) {
            switch (_playerState) {
            case PlayerState::Idle: // �ҋ@
                _modelAnim.SetBlendAttach(Idle, 10.0f, 1.0f, true);
                break;
            case PlayerState::Walk: // ����
                _modelAnim.SetBlendAttach(Walk, 10.0f, 1.0f, true);
                break;
            case PlayerState::Run: // ����
                _modelAnim.SetBlendAttach(Run, 10.0f, 1.0f, true);
                break;
            case PlayerState::Attack1: // �U��1
                if (_attackFlugY == true) {
                    _modelAnim.SetBlendAttach(GroundLightAttack1, 10.0f, 1.3f, false);
                }
                else if (_attackFlugX == true) {
                    _modelAnim.SetBlendAttach(GroundHeavyAttack1, 10.0f, 1.0f, false);
                }
                break;
            case PlayerState::Attack2: // �U��2
                if (_attackFlugY == true) {
                    _modelAnim.SetBlendAttach(GroundLightAttack2, 10.0f, 1.3f, false);
                }
                else if (_attackFlugX == true) {
                    _modelAnim.SetBlendAttach(GroundHeavyAttack2, 10.0f, 1.0f, false);
                }
                break;
            case PlayerState::Attack3: // �U��3
                if (_attackFlugY == true) {
                    _modelAnim.SetBlendAttach(GroundLightAttack3, 10.0f, 1.0f, false);
                }
                else if (_attackFlugX == true) {
                    _modelAnim.SetBlendAttach(GroundHeavyAttack3, 10.0f, 1.0f, false);
                }
                break;
            case PlayerState::Jump: // �W�����v
                _modelAnim.SetBlendAttach(JumpUp, 10.0f, 1.0f, false);
                break;
            default:
                break;
            }
        }
    }

    void Player::GravityScale() {
      // �W�����v�t���O�������Ă���ꍇ
      if (_jump) {
        // �V�����d�͉����x��ݒ肷��
        auto gScale = _gravityScale + (_jumpPower / 60.0f);
        // �����x���W�����v�͂𒴉߂��Ă��Ȃ����H
        if (gScale <= _jumpPower) {
          // �d�͉����x���Z�b�g����
          _gravityScale = gScale;
          return;
        }
        _jump = false;
      }
      using Gravity = AppFrame::Math::GravityBase;
      // �d�͉����x�����Z����
      _gravityScale += Gravity::Acceleration();
    }

    bool Player::IsStand() {
      // �V�������W
      auto newPos = _position.AddVectorY(_gravityScale);
      // �V�����J�v�Z��
      auto newCapsule = *_capsule;
      // �J�v�Z�����W���Z�b�g
      newCapsule.SetPosition(newPos);
      // �����̎擾
      auto [start, end] = newCapsule.LineSegment().GetVector();
      // �n�`(��)�Ɛ����̏Փ˔���
      auto hit = MV1CollCheck_Line(_handleMap, 2, UtilityDX::ToVECTOR(end), UtilityDX::ToVECTOR(start));
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
      // �W�����v�t���O�������Ă���ꍇ�̓I�t�ɂ���
      _jump = false;
      _jumpPower = 0.0f;
      return true; // ���ɗ����Ă���
    }

#ifdef _DEBUG
    bool Player::DebugDraw() const {
      // �t���O�������Ă���ꍇ�̂ݕ`����s��
      if (!ObjectBase::DebugDraw()) {
        return false; // �o�͂��s��Ȃ�
      }
      DebugString(); // ���W���̏o��
      _app.GetCamera().Draw(_position, _move); // �J�������̏o�͏���
      // _sphere->Draw(); // �����蔻��̕`��
      _capsule->Draw(); // �J�v�Z���̕`��
      return true;
    }

    void Player::DebugString() const {
      // ���W���o�͂���
      auto[x, y, z] = _position.GetVector3();
      DrawFormatString(0, 0, 255, "x:%f  y:%f, z:%f", x, y, z);
      auto [lx, ly] = _app.GetOperation().GetXBoxState().GetStick(false);
      DrawFormatString(0, 20, 255, "lx:%d  ly:%d", lx, ly);
      auto [rx, ry] = _app.GetOperation().GetXBoxState().GetStick(true);
      DrawFormatString(300, 20, 255, "lx:%d  ly:%d", rx, ry);
      // ��]���̏o��
      auto [rX, rY, rZ] = _rotation.GetVector3();
      DrawFormatString(0, 40, 255, "rotationX:%f  rotationY:%f rotationZ:%f", rX, rY, rZ);
      auto [moveX, moveY, moveZ] = _move.GetVector3();
      DrawFormatString(0, 60, 255, "moveX:%f  moveY:%f moveZ:%f", moveX, moveY, moveZ);
    }
#endif

    void Player::Hit() {
      auto objects = _app.GetObjectServer().GetObjects(); // �I�u�W�F�N�g�̃R�s�[
      // �Փ˔�����s��
      for (auto obj : objects) {
        // �G�̏ꍇ�̂ݏ������s��
        if (obj->GetId() != ObjectId::Enemy) continue;
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
          // auto l = radius2 - v.Length();
          // _position = (AppMath::Vector4::Normalize(v) * l);
          // _position.SetY(y);
          _capsule->SetPosition(_position);
        }
      }
    }

    void Player::Jump() {
      // �W�����v�̃C���^�[�o������
      if (_jump) {
        return; // �C���^�[�o�����Ȃ��ꍇ�͏������s��Ȃ�
      }
      _gravityScale = 0.0f;
      _jump = true;           // �W�����v�t���O
      _jumpInterval = 300.0f; // �C���^�[�o����ݒ�
      _jumpPower = 100.0f;    // �W�����v�͂��Z�b�g
    }
  } // namespace Player
}// namespace Gyro
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
#include "StageComponent.h"
#include "AttackBone.h"

namespace {
  constexpr auto NoAnimation = -1; //!< �A�j���[�V�����̓A�^�b�`����Ă��Ȃ�
  constexpr auto InputMin = 2000.0f;  //!< ���͂��󂯕t����Œ�l
  constexpr auto InputMax = 32767.0f;

  constexpr auto MoveSpeed = 5.0f; //!< �f�t�H���g�̈ړ���
  constexpr auto MoveZero = 0.0f;

  constexpr auto WireSpeed = 10.0f; //!< ���C���[�ړ����x
  // �v���C���[�̃A�j���[�V�����L�[
  constexpr auto Idle = "GyroIdle";                            //!< �A�C�h��
  constexpr auto Walk = "GyroWalk";                            //!< ����
  constexpr auto Run = "GyroDash";                             //!< ����
  constexpr auto Step = "GyroStep";                            //!< �X�e�b�v
  constexpr auto JumpUp = "GyroJUp";                           //!< �W�����v�A�b�v
  constexpr auto JumpDown = "GyroJDown";                       //!< �W�����v�_�E��(������)
  constexpr auto JumpLanding = "GyroJLand";                    //!< �W�����v�����h(���n)
  constexpr auto GroundLightAttack1 = "GyroLaw1";              //!< �n���U��1
  constexpr auto GroundLightAttack2 = "GyroLaw2";              //!< �n���U��2
  constexpr auto GroundLightAttack3 = "GyroLaw3";              //!< �n���U��3
  constexpr auto GroundLightAttackEX = "GyroLawEx";            //!< �n��EX�U��(��́Y)
  constexpr auto GroundHeavyAttack1 = "Gyro High1";            //!< �n�㋭�U��1
  constexpr auto GroundHeavyAttack2 = "GyroHigh2";             //!< �n�㋭�U��2
  constexpr auto GroundHeavyAttack3 = "GyroHigh3";             //!< �n�㋭�U��3
  constexpr auto AirLightAttack1 = "GyroJLaw1";                //!< �󒆎�U��1
  constexpr auto AirLightAttack2 = "GyroJLaw2";                //!< �󒆎�U��2
  constexpr auto AirLightAttack3 = "GyroJLaw3";                //!< �󒆎�U��3
  constexpr auto AirHeavyAttack1 = "GyroJHigh1";               //!< �󒆋��U��1
  constexpr auto AirHeavyAttack2 = "GyroJHigh2";               //!< �󒆋��U��2
  constexpr auto ExciteTrickActive = "GyroExciteTrickActive";  //!< �K�E�Z
  constexpr auto ExciteTrick1 = "GyroExciteTrickDirect1";      //!< �K�E�Z
  constexpr auto ExciteTrick2 = "GyroExciteTrickDirect2";      //!< �K�E�Z
  constexpr auto Damage1 = "GyroDamage1";                      //!< ���_���[�W
  constexpr auto Damage2 = "GyroDamage2";                      //!< ��_���[�W
  // �W�����v�t���O
  constexpr auto JumpPowe = 3.0f;
  constexpr auto JumpMax = 300.0f;

  constexpr auto RunPower = 3.8f;
}

namespace Gyro {
  namespace Player {

    /**
     * @brief ���@�̏�Ԃ��L�[�Ƃ��ď�Ԃ��Ǘ�����A�z�z��N���X
     */
    const std::unordered_map<Player::PlayerState, std::pair<int, int>> chaneMap{
      {Player::PlayerState::Attack1, {60, 90}}, // �U��1
      {Player::PlayerState::Attack2, {60, 90}}, // �U��2
    };

    const std::unordered_map<Player::PlayerState, Player::PlayerState> stateMap{
      {Player::PlayerState::Attack1, Player::PlayerState::Attack2},
      {Player::PlayerState::Attack2, Player::PlayerState::Attack3},
      {Player::PlayerState::Attack3, Player::PlayerState::Idle}
    };

    /**
     * @brief ���@�̏�Ԃ��L�[�Ƃ��āA�����蔻����Z�b�g����{�[���ԍ����Ǘ�����A�z�z��
     */
    const std::unordered_map<Player::PlayerState, Object::AttackBone> BoneMap {
      {Player::PlayerState::Attack1, {15, 0}},
      {Player::PlayerState::Attack2, {20, 0}},
      {Player::PlayerState::Attack3, {54, 0}},
    };

    Player::Player(Application::ApplicationMain& app) : ObjectBase(app), _gaugeHp(app), _gaugeTrick(app) {
      LoadResource(); // ���\�[�X�̓ǂݎ��
      Init();
    }

    bool Player::Init() {
      _animationKey = Idle; //!< �A�C�h�����[�V������ݒ�
      SetCamera(); // �J�����̐ݒ�
      SetState();  // �p�����[�^�̐ݒ�
      // �W�����v�R���|�[�l���g�̐ݒ�
      _jump = std::make_unique<JumpComponent>();
      _jump->Set(300.0f, 120); // �W�����v�̐ݒ�
      // ���C���[�R���|�[�l���g�̐ݒ�
      _wire = std::make_unique<WireComponent>(*this);
      // �A�^�b�N�R���|�[�l���g�̐ݒ�
      // �����蔻��͋����Z�b�g����
      _attack = std::make_unique<Object::AttackComponent>(*this, std::move(std::make_shared<Object::CollisionSphere>(*this, _position, 30.0f)));
      // �C���r�W�u���R���|�[�l���g�̐ݒ�
      _invincible = std::make_unique<Object::InvincibleComponent>(_app);
      // �X�e�[�g�R���|�[�l���g�̐ݒ�
      _stateComponent = std::make_unique<Object::StateComponent>();
      // �A�j���[�V�����̐ݒ�
      _modelAnim.SetMainAttach(_model, Idle, 1.0f, true);
      // �Q�[�W�̐ݒ�
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
      //!< �ړ���
      AppMath::Vector4 move;

      //// ���C���[�A�N�V�����̓�������
      //if (input.GetButton(XINPUT_BUTTON_B, false)) {
      //  Wire(move);
      //}
      // 
      // ���C���[�t���O�������Ă��Ȃ��ꍇ�̂ݍX�V���s��
      if (!_wire->IsAction()) {
        // ��Ԃ̐؂�ւ�����
        auto f = StateChanege(input);
        // �ړ��ʂ̎擾
        move = Move(lX, lY);
        // 
        if (!f) {
          SetRotation(move);
        }
      }
      // ���C���[�t���O�������Ă���ꍇ�͈ړ��ʂ��g�p
      else {
        move = _wire->WireMove();
      }

      //// ���C���[�A�N�V�������s���͑��̃A�N�V���������s���Ȃ�
      //if (!_wire->IsAction()) {
      //  // �W�����v�����̓�������
      //  if (input.GetButton(XINPUT_BUTTON_A, false)) {
      //    Jump(); // �W�����v����
      //  }
        // �ړ��ʂ̎擾
        // move = Move(lX, lY);

        // ��ԑJ�ڏ���


      //  // ��Ԃ̍X�V
      //  if (State(PlayerState::Idle) && _attackFlugY == false && input.GetButton(XINPUT_BUTTON_Y, false)) {
      //    _attack->Start();
      //    ChangeState(PlayerState::Attack1, GroundLightAttack1);
      //    _gaugeTrick.Add(-50.f);
      //    _attackFlugY = true;
      //    _cnt = 0;
      //  }
      //  else if (State(PlayerState::Attack1) && _attackFlugY == true && input.GetButton(XINPUT_BUTTON_Y, false)) {
      //    ChangeState(PlayerState::Attack2, GroundLightAttack2);
      //    _gaugeTrick.Add(-50.f);
      //    _cnt = 0;
      //  }
      //  else if (State(PlayerState::Attack2) && _attackFlugY == true && input.GetButton(XINPUT_BUTTON_Y, false)) {
      //    ChangeState(PlayerState::Attack3, GroundLightAttack3);
      //    _gaugeTrick.Add(-50.f);
      //    _cnt = 0;
      //  }
      //  // ���U������
      //  if (State(PlayerState::Idle) && _attackFlugX == false && input.GetButton(XINPUT_BUTTON_X, false)) {
      //    _attack->Start();
      //    ChangeState(PlayerState::Attack1, GroundHeavyAttack1);
      //    _gaugeTrick.Add(-50.f);
      //    _attackFlugX = true;
      //    _cnt = 0;
      //  }
      //  else if (State(PlayerState::Attack1) && _attackFlugX == true && input.GetButton(XINPUT_BUTTON_X, false)) {
      //    ChangeState(PlayerState::Attack2, GroundHeavyAttack2);
      //    _gaugeTrick.Add(-50.f);
      //    _cnt = 0;
      //  }
      //  else if (State(PlayerState::Attack2) && _attackFlugX == true && input.GetButton(XINPUT_BUTTON_X, false)) {
      //    ChangeState(PlayerState::Attack3, GroundHeavyAttack3);
      //    _gaugeTrick.Add(-50.f);
      //    _cnt = 0;
      //  }
      //  if (_modelAnim.GetMainAnimEnd() == true && _attackFlugY == true) {
      //    _attackFlugY = false;
      //  }
      //  else if (_modelAnim.GetMainAnimEnd() == true && _attackFlugX == true) {
      //    _attackFlugX = false;
      //  }
      //  else if (_attackFlugX == false && _attackFlugY == false) {
      //    SetRotation(move);
      //  }
      //}
      //else {
      //  move = _wire->WireMove();
      //}
      // ���W�Ɍ��ݍ��W���X�V����
      _position.Add(move);
      _gaugeHp.Process();
      _gaugeTrick.Process();
      Animation(_oldState);    // �A�j���[�V�����̐ݒ�
      _modelAnim.Process();    // �A�j���[�V�����̍Đ�
      WorldMatrix();           // ���[���h���W�̍X�V
      Attack();                // �U������
      _sphere->Process(move);  // �ړ��ʂ̉��Z
      _capsule->Process(move); // �J�v�Z���̍X�V
      Hit(); //�Փ˔���
      // �J�����̍X�V
      _app.GetCamera().Process(AppMath::Vector4(rX, rY), _position, move);
      // ���[���h���W�̐ݒ�
      MV1SetMatrix(_model, UtilityDX::ToMATRIX(_world));
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
      MV1DrawModel(_handleMap);
      _gaugeHp.Draw();
      _gaugeTrick.Draw();
#ifdef _DEBUG
      DebugDraw();     // �f�o�b�O�`��
      _attack->Draw(); // �U������̕`��
#endif
      // �ړ������̌�n�����s��
      _move->Finish();
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

    bool Player::StateChanege(const AppFrame::Application::XBoxState& input) {
      // ���ɍU����Ԃ�
      if (IsAttackState()) {
        // �����Ŏg�p����L�[�̎擾
        auto key = NextKey();
        if (key != -1) {
          // �U����Ԃ̏ꍇ�͑J�ڃt���O�̔�����s��
          if (input.GetButton(key, false) && _stateComponent->Process(_modelAnim.GetMainPlayTime())) {
            _attack->Finish();
            // �����𖞂������̂ōX�V���s��
            SetStateParam(stateMap.at(_playerState));
            return true;
          }
        }
        // �A�j���[�V�������I�����Ă���ꍇ
        if (_modelAnim.GetMainAnimEnd()) {
          _playerState = PlayerState::Idle;
          _attack->Finish();
          _stateComponent->Finish();
        }
        return true;
      }
      // �U����ԂɑJ�ڂ��邩�̔���H
      if (_playerState == PlayerState::Idle || _playerState == PlayerState::Run || _playerState == PlayerState::Walk) {
        // Y�{�^���̓��͂��������ꍇ
        if (input.GetButton(XINPUT_BUTTON_Y, false)) {
          // ���U���ɑJ�ڂ���
          SetStateParam(PlayerState::Attack1);
          _attack->Start();
          _stateComponent->Start();
          _attackFlag = true;
          return true; // �J�ڂ���
        }
        // X�{�^���̓��͂��������ꍇ
        if (input.GetButton(XINPUT_BUTTON_X, false)) {
          // ��U���ɑJ�ڂ���
          SetStateParam(PlayerState::Attack1);
          _stateComponent->Start();
          _attack->Start();
          _attackFlag = false;
          return true; // �J�ڂ���
        }
        // A�{�^���̓��͂��������ꍇ�̓W�����v��ԂɑJ��
        if (input.GetButton(XINPUT_BUTTON_A, false)) {
          Jump(); // �W�����v����
          return true; // �J�ڂ���
        }
      }
      return false;
    }

    int Player::NextKey() const {
      // �U���t���O�ɉ����ĕԂ��L�[��؂�ւ���
      auto key = (_attackFlag) ? XINPUT_BUTTON_Y : XINPUT_BUTTON_X;
      // ���݂̏󋵂ɉ������L�[��Ԃ�
      switch (_playerState) {
      case PlayerState::Attack1:
      case PlayerState::Attack2:
        return key; // �Ή�����L�[��Ԃ�
      case PlayerState::Attack3:
        return -1;  // �����͔h�����Ȃ�
      default:
        return -2;  // �U����Ԃł͂Ȃ�
      }
    }

    void Player::Input() {

    }

    AppMath::Vector4 Player::Move(const float leftX, const float leftY) {
      // �ړ��x�N�g��
      auto move = AppMath::Vector4();
      // �ړ��ʂ̐���
      if (_move->Move(leftX, leftY)) {
        move = _move->MoveVector();
        // ���W�A���𐶐�(y���͔��]������)
        auto radian = std::atan2(move.GetX(), -move.GetZ());
#ifndef _DEBUG
        _rotation.SetY(radian); // y���̉�]�ʂ��Z�b�g����
#else
        // �f�O���[�l���Z�b�g����(�f�o�b�O�p)
        _rotation.SetY(AppMath::Utility::RadianToDegree(radian));
#endif
      }
      return move; // �ړ��ʂ�Ԃ�
    }

    void Player::LoadResource() {
      // �e�탊�\�[�X�̓ǂݎ�菈��
      auto [model, key1] = _app.GetModelServer().GetModel(_modelKey, 0);
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
      _move = std::make_unique<Object::MoveComponent>(*this);
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

      if (_playerState == PlayerState::Idle || _playerState == PlayerState::Run || _playerState == PlayerState::Walk) {
        // �ړ��ʂ̂����ꂩ����𒴂��Ă�����Run�ɑJ��
        if (IsRun(move)) {
          // �����ԂɑJ��
          _playerState = PlayerState::Run;
          return;
        }
        // �ړ��ʂ�����ꍇ�͕������[�V�����ɑJ��
        // ����ړ��ʂɉ����ĕ����E�_�b�V�����[�V�����؂�ւ�
        if (move.LengthSquared()) {
          _playerState = PlayerState::Walk;
          return;
        }
        // �ҋ@��ԂɑJ�ڂ���
        _playerState = PlayerState::Idle;
      }
    }

    bool Player::IsRun(const AppMath::Vector4& move) {
      // �ړ��ʂ̎擾
      auto [x, z] = move.GetVector2();
      if (RunPower <= x || x <= -RunPower || RunPower <= z || z <= -RunPower) {
        return true;
      }
      return false;
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
            // �A�j���[�V�����L�[�̐ݒ�
            _animationKey = (_attackFlag) ? GroundHeavyAttack1 : GroundLightAttack1;
              if (_attackFlag) {
                _modelAnim.SetBlendAttach(_animationKey, 10.0f, 1.0f, false);
                break;
              }
              _modelAnim.SetBlendAttach(_animationKey, 10.0f, 1.3f, false);
               break;
            case PlayerState::Attack2: // �U��2
              // �A�j���[�V�����L�[�̐ݒ�
              _animationKey = (_attackFlag) ? GroundHeavyAttack2 : GroundLightAttack2;
              if (_attackFlag) {
                _modelAnim.SetBlendAttach(_animationKey, 10.0f, 1.0f, false);
                break;
              }
              _modelAnim.SetBlendAttach(_animationKey, 10.0f, 1.3f, false);
              break;
            case PlayerState::Attack3: // �U��3
              _animationKey = (_attackFlag) ? GroundHeavyAttack3 : GroundLightAttack3;
              _modelAnim.SetBlendAttach(_animationKey, 10.0f, 1.0f, false);
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
      if (_jump->IsJump()) {
        // �V�����d�͉����x��ݒ肷��
        _gravityScale = _jump->JumpPower();
        return;
      }
      using Gravity = AppFrame::Math::GravityBase;
      // �d�͉����x�����Z����
      _gravityScale += (Gravity::Acceleration() / 60.0f);
    }

    bool Player::IsStand() {
      // �O�t���[�����W
      _oldState = _playerState;
      // �V�������W
      auto newPos = _position.AddVectorY(_gravityScale);
      // �V�����J�v�Z��
      auto newCapsule = *_capsule;
      // �J�v�Z�����W���Z�b�g
      newCapsule.SetPosition(newPos);
      // �����̎擾
      auto [start, end] = newCapsule.LineSegment().GetVector();
      // �n�`(��)�Ɛ����̏Փ˔���
      auto flag = false;
      for (int i = 0; i < _app.GetStageComponent().GetStageModel().size(); i++) {
        _handleMap = _app.GetStageComponent().GetStageModel()[i];
        auto hit = MV1CollCheck_Line(_handleMap, 2, UtilityDX::ToVECTOR(end), UtilityDX::ToVECTOR(start));
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
      // �Փ˃t���O�ɉ����ď�����؂�ւ���
      switch (flag) {
      case true: // ���Ƃ̐ڐG�L��
        // �W�����v�̌�n�����s��
        if (_jump->IsJump()) {
          _jump->Finish();
        }
        if (_playerState == PlayerState::Jump) {
          _playerState = PlayerState::Idle;
        }
        break;
      case false:
        // �V�������W���Z�b�g
        _position = newPos;
        // �R���W�������ɍX�V��������
        _capsule->SetPosition(_position);
        break;
      }
      return flag; // ���ɗ����Ă���
    }

#ifdef _DEBUG
    bool Player::DebugDraw() const {
      // �t���O�������Ă���ꍇ�̂ݕ`����s��
      if (!ObjectBase::DebugDraw()) {
        return false; // �o�͂��s��Ȃ�
      }
      DebugString(); // ���W���̏o��
      _app.GetCamera().Draw(_position, _move->MoveVector()); // �J�������̏o�͏���
      // _sphere->Draw(); // �����蔻��̕`��
      _capsule->Draw();   // �J�v�Z���̕`��
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
      auto [moveX, moveY, moveZ] = _move->MoveVector().GetVector3();
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
          // �J�����̍��W�ɉ��Z
          _app.GetCamera().CamAddPos(vv);
          // auto l = radius2 - v.Length();
          // _position = (AppMath::Vector4::Normalize(v) * l);
          // _position.SetY(y);
          _capsule->SetPosition(_position);
          // �Փ˂����ꍇ�̓��C���[�A�N�V�����𒆒f����
          if (_wire->IsAction()) {
            _wire->Finish();
            _playerState = PlayerState::Idle;
          }
        }
      }
    }

    void Player::Extrude() {
      auto newPosition = _position + _move->MoveVector();
      // �R���W�����ƕǂ̉����o���������s��
      auto newCapsule = *_capsule;
      newCapsule.SetPosition(newPosition);
      auto [start, end] = newCapsule.LineSegment().GetVector();
      auto radius = newCapsule.GetRadius();
      // �X�e�[�W�Ƃ̏Փ˔���
      auto hit = MV1CollCheck_Capsule(_handleMap, 1, UtilityDX::ToVECTOR(start), UtilityDX::ToVECTOR(end), radius);
      // �ڐG�ӏ����Ȃ��ꍇ
      if (!hit.HitNum) {
        // �Փ˗p���̌�n�����s��
        MV1CollResultPolyDimTerminate(hit);
        return;
      }
      MV1CollResultPolyDimTerminate(hit);
    }

    void Player::Jump() {
      // �W�����v�t���O�������Ă���ꍇ�͏������s��Ȃ�
      if (_jump->IsJump()) {
        return; // �C���^�[�o�����Ȃ��ꍇ�͏������s��Ȃ�
      }
      _jump->Start(); // �W�����v�J�n
      _gravityScale = 0.0f;
      _playerState = PlayerState::Jump;
    }

    void Player::Wire(AppMath::Vector4& move) {
      // ���C���[�A�N�V���������s����Ă��Ȃ���
      if (!_wire->IsAction()) {
        // ���W���Z�b�g���ď������s��
        auto o = _app.GetObjectServer().GetObjects();
        _wire->SetTarget(o.back()->GetPosition(), WireSpeed);
        _wire->Start();
        // �W�����v�t���O�������Ă���ꍇ��
        if (_jump->IsJump()) {
          _jump->Finish();
          _gravityScale = 0.0f;
        }
        return;
      }
      // �ړ��ʂ��Z�b�g����Ă���ꍇ�͏����𒆒f����
      _wire->Finish();
    }

    void Player::Attack() {
      using AttackState = Object::AttackComponent::AttackState;
      // �U����ԂłȂ��ꍇ�͏������s��Ȃ�
      if (_attack->GetState() == AttackState::NonActive) {
        return;
      }
      // ���݃A�^�b�`����Ă���C���f�b�N�X���擾
      auto attachIndex = _modelAnim.GetMainAttachIndex();
      // �v���C���[���̎擾
      auto bone = BoneMap.at(_playerState).GetBone();
      // �C���f�b�N�X���̎擾
      auto index = (_attackFlag) ? bone[0] : bone[1];
      // �w�肵���{�[���̃��[���h���W���擾
      auto pos = MV1GetFramePosition(_model, index);
      // ���[�J�����W���U�����W�ɃZ�b�g����
      _attack->Process(UtilityDX::ToVector(pos));
    }

    void Player::ChangeState(const PlayerState& state, std::string_view animName) {
      // �e��f�[�^�̐؂�ւ�
      _playerState = state;
      _animationKey = animName;
    }

    bool Player::IsAttackState() const {
      // ���݂̏�Ԃ͍U����Ԃ��H
      switch (_playerState) {
      case PlayerState::Attack1:
      case PlayerState::Attack2:
      case PlayerState::Attack3:
        return true;  // �U�����
      default:
        return false; // �U����Ԃł͂Ȃ�
      }
    }

    bool Player::SetStateParam(PlayerState pState) {
      // ��Ԃ̐؂�ւ�
      _playerState = pState;
      // �f�[�^���o�^����Ă��Ȃ��ꍇ�͐ݒ���s��Ȃ�
      if (!chaneMap.contains(_playerState)) {
        _stateComponent->Finish();
        return false;
      }
      // ���@�̏�Ԃ��擾
      auto [start, end] = chaneMap.at(_playerState);
      // �؂�ւ���Ԃ�ݒ肷��
      _stateComponent->Set(_modelAnim.GetMainPlayTime(), start, end);
      _stateComponent->Start();
      return true; // �؂�ւ�������
    }

  } // namespace Player
}// namespace Gyro
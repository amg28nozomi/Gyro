/*****************************************************************//**
 * @file   Player.cpp
 * @brief  �I�u�W�F�N�g�x�[�X�̃T�u�N���X�̒�`
 *
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "Player.h"
#include "ApplicationMain.h"
#include "Box.h"
#include "DashComponent.h"
#include "UtilityDX.h"
#include "ObjectServer.h"
#include "EnemyBase.h"
#include "CollisionCapsule.h"
#include "SpawnBase.h"
#include "StageComponent.h"
#include "ModelAnimData.h"
#include "EnemyBase.h"

namespace {
  constexpr auto NoAnimation = -1; //!< �A�j���[�V�����̓A�^�b�`����Ă��Ȃ�
  constexpr auto InputMin = 2000.0f;  //!< ���͂��󂯕t����Œ�l
  constexpr auto InputMax = 32767.0f;

  constexpr auto MoveSpeed = 5.0f; //!< �f�t�H���g�̈ړ���
  constexpr auto MoveZero = 0.0f;
  // ������
  constexpr auto RunValue = 36.0f;

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
  constexpr auto GroundHeavyAttack1 = "Gyrohigh1";             //!< �n�㋭�U��1
  constexpr auto GroundHeavyAttack2 = "Gyrohigh2";             //!< �n�㋭�U��2
  constexpr auto GroundHeavyAttack3 = "Gyrohigh3";             //!< �n�㋭�U��3
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
  // �v���C���[��HP
  constexpr int GyroHP = 1000;
  // �g���b�N�Q�[�W�̐ݒ�
  constexpr auto TrickMax = 30000;
  // �W�����v�t���O
  constexpr auto JumpPowe = 3.0f;
  constexpr auto JumpMax = 300.0f;

  constexpr auto RunPower = 3.8f;

  constexpr auto LightFlag = true;  //!< ��U���t���O
  constexpr auto HeavyFlag = false; //!< ���U���t���O

  // ��Ԃ�\���L�[
  constexpr auto StateNumberIdle = 0;    //!< �ҋ@
  constexpr auto StateNumberWalk = 1;    //!< ����
  constexpr auto StateNumberRun = 2;     //!< ����
  constexpr auto StateNumberJump = 3;    //!< �W�����v
  constexpr auto StateNumberLight1 = 4;  //!< ��U��1
  constexpr auto StateNumberLight2 = 6;  //!< ��U��2
  constexpr auto StateNumberLight3 = 8;  //!< ��U��3
  constexpr auto StateNumberHeavy1 = 5;  //!< ���U��1
  constexpr auto StateNumberHeavy2 = 7;  //!< ���U��2
  constexpr auto StateNumberHeavy3 = 9;  //!< ���U��3
  constexpr auto StateNumberAirLight1 = 10;  //!< �󒆎�U��1
  constexpr auto StateNumberAirLight2 = 12;  //!< �󒆎�U��2
  constexpr auto StateNumberAirLight3 = 14;  //!< �󒆎�U��3
  constexpr auto StateNumberAirHeavy1 = 11;  //!< �󒆋��U��1
  constexpr auto StateNumberAirHeavy2 = 13;  //!< �󒆋��U��2
  constexpr auto StateNumberExcite = 15; //!< �G�L�T�C�g�g���b�N
  constexpr auto StateNumberDash = 16;   //!< �_�b�V��

  constexpr auto AttackInterval = 150.0f; //!< �U���p�C���^�[�o��

  constexpr auto DashTime = 600.0f;   //!< �_�b�V������
  constexpr auto DashPower = 300.0f;  //!< �_�b�V���̈ړ���
}

namespace Gyro {
  namespace Player {

    /**
     * @brief ���@�̏�Ԃ��L�[�Ƃ��ď�Ԃ��Ǘ�����A�z�z��N���X
     */
    const std::unordered_map<Player::PlayerState, std::pair<int, int>> chaneMap{
      {Player::PlayerState::Attack1, {60, 90}}, // �U��1
      {Player::PlayerState::Attack2, {60, 90}}, // �U��2
      {Player::PlayerState::JumpAttack1, {60, 90}}, // �󒆍U��1
      {Player::PlayerState::JumpAttack2, {60, 90}}, // �󒆍U��2
    };

    const std::unordered_map<Player::PlayerState, Player::PlayerState> stateMap{
      {Player::PlayerState::Attack1, Player::PlayerState::Attack2},
      {Player::PlayerState::Attack2, Player::PlayerState::Attack3},
      {Player::PlayerState::Attack3, Player::PlayerState::Idle},
      {Player::PlayerState::Dash, Player::PlayerState::Idle},
      {Player::PlayerState::JumpAttack1, Player::PlayerState::JumpAttack2},
      {Player::PlayerState::JumpAttack2, Player::PlayerState::JumpAttack3},
      {Player::PlayerState::JumpAttack3, Player::PlayerState::Idle},
    };
    /**
     * @brief �R���W�����Ɏg�p����t���[���ԍ����Ǘ�����A�z�z��
     */
    const std::unordered_map<int, std::vector<int>> attackMap{
      // ��U��
      {StateNumberLight1, {50, 75}},
      {StateNumberLight2, {15, 17}},
      {StateNumberLight3, {15, 17, 20, 22}},
      // ���U��
      {StateNumberHeavy1 ,{15/*, 17, 20, 22*/}},
      {StateNumberHeavy2 ,{15, 17, 20, 22}},
      {StateNumberHeavy3 ,{15, 17, 20, 22, 50, 75}},
      // �󒆎�U��
      {StateNumberAirLight1 ,{15, 17, 20, 22}},
      {StateNumberAirLight2 ,{15, 17, 20, 22}},
      {StateNumberAirLight3 ,{15, 17, 20, 22}},
      // �󒆋��U��
      {StateNumberAirHeavy1 ,{15, 17, 20, 22}},
      {StateNumberAirHeavy2 ,{15, 17, 20, 22}},
    };

    /**
     * @brief ��Ԕԍ����L�[�Ƃ��āA���[�V�����u�����h����ێ�����A�z�z��
     */
    const std::unordered_map<int, ModelAnim::ModelAnimData> animMap {
      // �ҋ@���
      {StateNumberIdle, {Idle, 10.0f, 1.0f, true}},
      // ����
      {StateNumberWalk, {Walk, 10.0f, 1.0f, true}},
      // ����
      {StateNumberRun, {Run, 10.0f, 1.0f, true}},
      // �W�����v
      {StateNumberJump, {JumpUp, 10.0f, 1.0f, false, EffectNum::PlayerJump}},
      // ��U��1
      {StateNumberLight1, {GroundLightAttack1, 10.0f, 1.3f, false, EffectNum::PlayerWeakAttack1}},
      // ��U��2
      {StateNumberLight2, {GroundLightAttack2, 10.0f, 1.3f, false, EffectNum::PlayerWeakAttack2}},
      // ��U��3
      {StateNumberLight3, {GroundLightAttack3, 10.0f, 1.0f, false, EffectNum::PlayerWeakAttack3}},
      // ���U��1
      {StateNumberHeavy1 ,{GroundHeavyAttack1, 10.0f, 1.0f, false, EffectNum::PlayerHeavyAttack1}},
      // ���U��2
      {StateNumberHeavy2 ,{GroundHeavyAttack2, 10.0f, 1.0f, false, EffectNum::PlayerHeavyAttack2}},
      // ���U��3
      {StateNumberHeavy3 ,{GroundHeavyAttack3, 10.0f, 1.0f, false, EffectNum::PlayerHeavyAttack3}},
      // �󒆎�U��1
      {StateNumberAirLight1 ,{AirLightAttack1, 10.0f, 1.0f, false}},
      // �󒆎�U��2
      {StateNumberAirLight2 ,{AirLightAttack2, 10.0f, 1.0f, false}},
      // �󒆎�U��3
      {StateNumberAirLight3 ,{AirLightAttack3, 10.0f, 1.0f, false}},
      // �󒆋��U��1
      {StateNumberAirHeavy1 ,{AirHeavyAttack1, 10.0f, 1.0f, false}},
      // �󒆋��U��2
      {StateNumberAirHeavy2 ,{AirHeavyAttack2, 10.0f, 1.0f, false}},
      // �_�b�V��
      {StateNumberDash, {Step, 10.0f, 1.0f, false}}
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
      // �m�b�N�o�b�N�R���|�[�l���g�̐ݒ�
      _knockBack = std::make_unique<Object::KnockBackComponent>(*this, _app);
      // ���C���[�R���|�[�l���g�̐ݒ�
      _wire = std::make_unique<WireComponent>(*this);
      // �A�^�b�N�R���|�[�l���g�̐ݒ�
      // �����蔻��͋����Z�b�g����
      _attack = std::make_unique<Object::AttackComponent>(*this, std::move(std::make_shared<Object::CollisionSphere>(*this, _position, 30.0f)));
      // �C���r�W�u���R���|�[�l���g�̐ݒ�
      _invincible = std::make_unique<Object::InvincibleComponent>(_app);
      // �X�e�[�g�R���|�[�l���g�̐ݒ�
      _stateComponent = std::make_unique<Object::StateComponent>();
      // �_�b�V���R���|�[�l���g�̐ݒ�
      _dash = std::make_unique<Object::DashComponent>(*this);
      // �A�j���[�V�����̐ݒ�
      _modelAnim.SetMainAttach(_model, Idle, 1.0f, true);
      return true;
    }

    bool Player::Process() {
      // ���N���X�̍X�V�����Ăяo��
      ObjectBase::Process();
      // �O���r�e�B�t���O���I�t�̏ꍇ�͂����ōX�V
      if (!_gravity) { _oldState = _playerState; }
      // ���O��Ԃ̏ȗ�
      namespace App = AppFrame::Application;
      // ���͏�Ԃ̎擾
      auto input = _app.GetOperation().GetXBoxState();
      // �A�i���O�X�e�B�b�N�̓��͏�Ԃ��擾
      auto [leftX, leftY] = input.GetStick(false);
      auto [rightX, rightY] = input.GetStick(true);
      // �O�t���[�����W�̕ێ�
      _move->OldPosition();
      // �ړ���
      AppMath::Vector4 move;
      // ���C���[�t���O�������Ă��Ȃ��ꍇ�̂ݍX�V���s��
      if (!_wire->IsAction()) {
        // ��Ԃ̐؂�ւ�����
        auto f = StateChanege(input);
        // �ړ��ʂ̎擾
        move = Move(static_cast<float>(leftX), static_cast<float>(leftY));
        // ��Ԃ̕ω����Ȃ��ꍇ
        if (!f) {
          SetRotation(move);
        }
      }
      // ���C���[�t���O�������Ă���ꍇ�͈ړ��ʂ��g�p
      else {
        move = _wire->WireMove();
      }
      // ���W�Ɍ��ݍ��W���X�V����
      _gaugeHp.Process();      // HP�Q�[�W�̍X�V
      _gaugeTrick.Process();   // �g���b�N�Q�[�W�̍X�V
      _gaugeTrick.SetValue(_trickValue); // �g���b�N�Q�[�W�ɒl������
      Animation(_oldState);    // �A�j���[�V�����̐ݒ�
      _modelAnim.Process();    // �A�j���[�V�����̍Đ�
      Attack();                // �U������
      _sphere->Process(move);  // �ړ��ʂ̉��Z

      _capsule->Process(move); // �J�v�Z���̍X�V
      //�Փ˔���
      Hit();
      // �m�b�N�o�b�N����
      KnockBack(move);
      // �_���[�W�E���G����
      Invincible();
      // �n�`�̉����o������
      Extrude(move);
      _position.Add(move);     // ���ݍ��W�̍X�V
      // ���[���h���W�̍X�V
      WorldMatrix();
      // �X�e�[�W���ς���������W�ύX
      auto stage = "boss";
      if (_app.GetStageComponent().GetStageName().generic_string() == stage && _stageChange == true) {
        auto oldPos = _position;
        _position.Set(0.0f, 1000.f, -200.f);
        move = _position - oldPos;
        _stageChange = false;
      }
      // �J�����̍X�V
      _app.GetCamera().Process(AppMath::Vector4(rightX, rightY), _position, _move->GetOldPosition().Direction(_position));
      // ���[���h���W�̐ݒ�
      MV1SetMatrix(_model, UtilityDX::ToMATRIX(_world));
      return true;
    }

    bool Player::Draw() const{
      MV1DrawModel(_model); // ���@�̕`��
      _gaugeHp.Draw();      // HP�Q�[�W�̕`��
      _gaugeTrick.Draw();   // �g���b�N�Q�[�W�̕`��
#ifdef _DEBUG
      // �f�o�b�O���̏o��
      DebugDraw();
      // �f�o�b�O�t���O������ꍇ�̂ݕ`�揈�����s��
      if (_app.GetDebugFlag()) {
        _attack->Draw(); // �U������̕`��
      }
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

    AppMath::Vector4 Player::GetCameraForward() const {
      // �J�����̎擾
      const auto camera = _app.GetCamera();
      // �J�����E�������W�̎擾
      auto cameraPosition = camera.GetPosition();
      auto cameraTarget = camera.GetTarget();
      // �J������������ւ̃x�N�g��
      using Vector4 = AppMath::Vector4;
      using Matrix44 = AppMath::Matrix44;
      // �r���[�ϊ��s��̎擾

      auto view = AppMath::Matrix44::CreateLookAt(cameraPosition, cameraTarget, Vector4(1.0f, 1.0f, 1.0f));
      // �t�s��
      auto inverse = view.Inverse(view);
      // ���@�̌������擾
      auto rotation = GetRotationRadianY();
      // �ʖ���`
      using Vector4 = AppMath::Vector4;
      // �����x�N�g��
      auto vector = Vector4(1.0f, 0.0f, -1.0f);
      // 
      vector = vector * rotation;
      // ��_�Ԃ̋������Z�o
      auto l = cameraPosition.Direction(cameraTarget);
      l.SetY(0.0f);
      // 

      auto direction = cameraPosition.Direction(cameraTarget);
      // �J���������̎Z�o
      auto cameraForward = Vector4::Normalize(direction);

      auto dot = Vector4::Dot(_position, l);
      return Vector4::Up();
    }

    float Player::GetRotationRadianY() const {
#ifndef _DEBUG
      return  _rotation.GetY();
#else
      return AppMath::Utility::DegreeToRadian(_rotation.GetY());
#endif
    }

    AppMath::Vector4 Player::GetFramePosition(int frame) {
      // �擾�������W��Vector�N���X�ɕϊ����ĕԂ�
      auto position = MV1GetFramePosition(_model, frame);
      // �w��t���[�������x�N�g���N���X�ɕϊ�
      return UtilityDX::ToVector(position);
    }

    bool Player::StateChanege(const AppFrame::Application::XBoxState& input) {
      // �U����Ԃ��̔���
      if (IsAttackState()) {
        // �����Ŏg�p����L�[�̎擾
        auto key = NextKey();
        /**
         * @brief  �U���J�ڗp�̓��͔�����s����
         * @param  nextKey �J�ڔ���Ŏg�p����L�[�{�^��
         * @param  flag    �U���J�ڃt���O(true:�J�ڗ\�� false:�\��Ȃ�)
         * @return true:���͔�����s�� false:���͔�����s��Ȃ�
         */
        auto AttackInput = [](int nextKey, bool flag) {
          // �J�ڃt���O�������Ă��邩�̔���
          if (flag) {
            return false; // ���͔���͍s��Ȃ�
          }
          // �L�[�̎擾�ɐ�����������Ԃ�
          return nextKey != -1;
        };
        // ���͔�����s����
        if (AttackInput(key, _nextAttack)) {
          // �U���J�ڔ���
          if (input.GetButton(key, false) && _stateComponent->Process(_modelAnim.GetMainPlayTime())) {
            // �����𖞂����Ă���ꍇ�͍U���J�ڃt���O���Z�b�g����
            _nextAttack = true;
            return true;
          }
        }
        /**
         * @brief  �A�j���[�V�����̏I������
         * @param  animEnd �A�j���[�V�����I���t���O
         * @param  brand   �A�j���[�V�����u�����h�t���O
         * @return true:�I���@false:�I�����Ă��Ȃ�
         */
        auto IsAnimEnd = [](bool animEnd, bool brand) {
          return animEnd == true && brand == false;
        };
        // �A�j���[�V�������I�����Ă���ꍇ
        if (_modelAnim.GetMainAnimEnd()) {
          // �U���J�ڃt���O���Z�b�g����Ă���ꍇ
          if (_nextAttack) {
            // �t���O�����Z�b�g
            _nextAttack = false;
            // ���݂̍U���������I��
            _attack->Finish();
            // �����𖞂������̂ōX�V���s��
            SetStateParam(stateMap.at(_playerState));
            // �U�������J�n
            _attack->Start();
            // 
            _intervalAttack = true;
            return true;
          }
          // �ҋ@��Ԃւ̑J�ڂ��s����
          if (_intervalAttack) {
            // �A�j���[�V�����u�����h�����̔���
            if (_modelAnim.IsBlending()) {
              return true;
            }
            // �A�j���[�V�����u�����h���I�������̂őҋ@�����𖳌�
            _intervalAttack = false;
          }
          // �W�����v���[�V�������Z�b�g����Ă���ꍇ�͒e��
          if (_modelAnim.IsSetMainAnim(JumpUp)) {
            return true;
          }
          // �d�͏���
          _gravity = true;
          // ���݂̏�Ԃ����ċ󒆍U��
          if (_playerState == PlayerState::JumpAttack1 || _playerState == PlayerState::JumpAttack2 || _playerState == PlayerState::JumpAttack3) {
            // �W�����v�����郂�[�V�����ɂ���
            _playerState = PlayerState::Jump;
          }
          else {
            // �ҋ@��ԂɑJ�ڂ���
            _playerState = PlayerState::Idle;
          }
          // �U���I��
          _attack->Finish();
          // �C���^�[�o�����Ԃ̐ݒ�
          _attack->SetInterval(150.0f);
          // ��ԑJ�ڔ���𒆒f
          _stateComponent->Finish();
        }
        return true;
      }
      // �U����ԂɑJ�ڂ��邩�̔���H
      if (_playerState == PlayerState::Idle || _playerState == PlayerState::Run || _playerState == PlayerState::Walk) {
        // �U����ԂɑJ�ڂł��邩
        if (_attack->ToAttack()) {
          // ��U������
          auto light = InputAttackCheck(input, XINPUT_BUTTON_Y, LightFlag);
          // ���U������
          auto heavy = InputAttackCheck(input, XINPUT_BUTTON_X, HeavyFlag);
          // �ǂ��炩�̏�ԂɑJ�ڂ�����
          if (light || heavy) {
            _gravity = false;
            return true;
          }
        }
        // A�{�^���̓��͂��������ꍇ�̓W�����v��ԂɑJ��
        if (input.GetButton(XINPUT_BUTTON_A, false)) {
          Jump();      // �W�����v����
          return true; // �J�ڂ���
        }
      }
      // �󒆍U����ԂɑJ�ڂ��邩�̔���H
      if (_playerState == PlayerState::Jump) {
        // �U����ԂɑJ�ڂł��邩
        if (_attack->ToAttack()) {
          // ��U������
          auto light = InputAttackCheck(input, XINPUT_BUTTON_Y, LightFlag);
          // ���U������
          auto heavy = InputAttackCheck(input, XINPUT_BUTTON_X, HeavyFlag);
          // �ǂ��炩�̏�ԂɑJ�ڂ�����
          if (light || heavy) {
            _gravity = false;
            return true;
          }
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
      case PlayerState::JumpAttack1:
      case PlayerState::JumpAttack2:
        return key; // �Ή�����L�[��Ԃ�
      case PlayerState::Attack3:
      case PlayerState::JumpAttack3:
        return -1;  // �����͔h�����Ȃ�
      default:
        return -2;  // �U����Ԃł͂Ȃ�
      }
    }

    bool Player::InputAttackCheck(const AppFrame::Application::XBoxState& input, const int key, bool flag) {
      // ���͂��s��ꂽ���̔���
      if (input.GetButton(key, false)) {
        // �U�����1�ɑJ�ڂ���
        if (_playerState != PlayerState::Jump) {
          SetStateParam(PlayerState::Attack1);
        }
        else {
          SetStateParam(PlayerState::JumpAttack1);
        }
        // �U������Ŏg�p����t���[���ԍ��̎擾
        auto frames = attackMap.at(PlayerStateToNumber());
        // �t���[���ƃR���W�������̐ݒ�
        _attack->SetFrame(frames, AddSpheres(static_cast<int>(frames.size())));
        _stateComponent->Start();
        _attack->Start();
        _attackFlag = flag;
        return true; // �J�ڂ���
      }
      return false; // ���͖���
    }

    void Player::Input() {

    }

    AppMath::Vector4 Player::Move(const float leftX, const float leftY) {
      // �ړ��x�N�g��
      auto move = AppMath::Vector4();
      // �U����Ԃ̏ꍇ
      if (_attack->IsAttack()) {
        return move;  // �ړ����s��Ȃ�
      }
      // �ړ��ʂ̐���
      if (_move->Move(leftX, leftY)) {
        // �ړ��ʂ̎擾
        move = _move->MoveVector();
        _forward = AppMath::Vector4::Normalize(_position + move);
      }
      return move; // �ړ��ʂ�Ԃ�
    }

    void Player::LoadResource() {
      // �e�탊�\�[�X�̓ǂݎ�菈��
      auto [model, key1] = _app.GetModelServer().GetModel(_modelKey, 1);
      // �擾�������f���n���h����ݒ�
      _model = model;
    }

    void Player::SetCamera() {

    }


    void Player::SetState() {
      // ��Ԃ̐ݒ�
      _id = ObjectId::Player;
      _state = ObjectState::Active;
      _gravity = true; // �d�͏������s��
      // �ړ��R���|�[�l���g�̐���
      _move = std::make_unique<Object::MoveComponent>(*this);
      // �n�`�̏Փ˔����ݒ�
      using Vector = AppFrame::Math::Vector4;
      // ���ʂ̐ݒ�
      auto a = Vector(0.0f, 0.0f, 100.0f);
      auto b = Vector(-100.0f, 0.0f, -100.0f);
      auto c = Vector(100.0f, 0.0f, -100.0f);
      _plane = std::make_unique<AppFrame::Math::Plane>(a, b, c);
      // HP�̐ݒ�
      _playerHP = GyroHP;
      // �\�[�g�̐ݒ�
      _sort = 2;
      // �Q�[�W�̐ݒ�
      _gaugeHp.Init(GyroHP);
      _gaugeTrick.Init(TrickMax);
      _stageChange = true;
    }

    void Player::CameraUpdate(const AppFrame::Math::Vector4 stick) {
      
    }

    void Player::SetRotation(const AppFrame::Math::Vector4 move) {
      // �w���Ԃ̏ꍇ��
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
      auto [x, y , z] = move.GetVector3();
      // �ʖ���`
      using Utility = AppMath::Utility;
      // �����ɕϊ�
      x = Utility::ToPlus(x) * Utility::ToPlus(x);
      z = Utility::ToPlus(z) * Utility::ToPlus(z);
      // �����Ԃ��̔���
      if (RunValue <= x || RunValue <= z) {
        return true; // �����Ԃ�
      }
      return false;  // �����Ԃł͂Ȃ�
    }

    void Player::KnockBack(AppMath::Vector4& move) {
      // �m�b�N�o�b�N��Ԃł͂Ȃ��ꍇ�͏������s��Ȃ�
      if (!_knockBack->IsKnockBack()) {
        return;
      }
      // �X�V�����Ăяo��
      _knockBack->Process();
      // �ړ��ʍX�V
      move = _knockBack->MoveVector();
    }

    void Player::Animation(PlayerState old) {
      // ��Ԃ��؂�ւ���Ă���ꍇ�̂ݏ������s��
      if (_playerState == old) {
        return;
      }
      // �J�ڔԍ��̎擾
      auto number = PlayerStateToNumber();
      // �擾�Ɏ��s�����ꍇ�͏������s��Ȃ�
      if (number == -1) {
        return;
      }
      // ���f���A�j���[�V�������̎擾
      const auto modelAnim = animMap.at(number);
      auto [key, frame, speed, loop] = modelAnim.ModelAnim();
      // �A�j���[�V�������Z�b�g����
      _modelAnim.SetBlendAttach(key.data(), frame, speed, loop);
      // �G�t�F�N�g���o�^����Ă���ꍇ�͍Đ�����
      if (!modelAnim.Effect() == 0) {
        PlayEffect();
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
      // �Փ˃t���O
      auto flag = false;
      // �I�u�W�F�N�g�Ƃ̏Փ˔���
      if (IsStandObject(newCapsule, newPos)) {
        flag = true;
        _position = newPos;
        _capsule->SetPosition(_position);
      }
      // ��Q���ƐڐG���Ă��Ȃ��ꍇ�͏��Ƃ̏Փ˔�����s��
      else flag = StandFloor(newCapsule, newPos);
      // �Փ˃t���O�ɉ����ď�����؂�ւ���
      switch (flag) {
      case true: // ���Ƃ̐ڐG�L��
        // �W�����v�̌�n�����s��
        if (_jump->IsJump()) {
          _jump->Finish();
        }
        if (_playerState == PlayerState::Jump || _playerState == PlayerState::JumpAttack1 || _playerState == PlayerState::JumpAttack2 || _playerState == PlayerState::JumpAttack3) {
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
      std::shared_ptr<Enemy::EnemyBase> enemy;
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
          _capsule->SetPosition(_position);
          // �Փ˂����ꍇ�̓��C���[�A�N�V�����𒆒f����
          if (_wire->IsAction()) {
            _wire->Finish();
            _playerState = PlayerState::Idle;
          }
        }
      }
    }

    void Player::Extrude(AppMath::Vector4& move) {
      // �n�`�Ƃ̏Փ˔���
      auto newPosition = _position + move;
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
          auto slide = Vector4::Cross(normal, Vector4::Cross(move, normal));
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
        move.Zero();
        _position = newPosition;
        _capsule->SetPosition(newPosition);
      }
    }

    void Player::Jump() {
      // �W�����v�t���O�������Ă���ꍇ�͏������s��Ȃ�
      if (_jump->IsJump()) {
        return; // �C���^�[�o�����Ȃ��ꍇ�͏������s��Ȃ�
      }
      // �W�����v�������J�n����
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
      // ���[�J�����W���U�����W�ɃZ�b�g����
      _attack->Process();
    }

    bool Player::ExiteTrick() {
      return true;
    }

    bool Player::DashStart() {
      // �_�b�V�����J�n����
      // _dash->SetDash(, 600.0f);
      return true;
    }

    AppMath::Vector4 Player::Dash() {
      // �ړ���
      auto move = AppMath::Vector4();
      _dash->Process(move);
      return move;
    }


    void Player::IsDamage() {
      auto objects = _app.GetObjectServer().GetObjects(); // �I�u�W�F�N�g�̃R�s�[
      std::shared_ptr<Enemy::EnemyBase> enemy;
      // �Փ˔�����s��
      for (auto obj : objects) {
        // �G�̏ꍇ�̂ݏ������s��
        if (obj->GetId() != ObjectId::Enemy) continue;
        // �G���U����Ԃ̏ꍇ�_���[�W����ɐi��
        enemy = std::dynamic_pointer_cast<Enemy::EnemyBase>(obj);
        if (enemy->GetEnemyState() != Enemy::EnemyBase::EnemyState::Attack) continue;
        // ���Ƌ��̏Փ˔���
        if (_capsule->IntersectSphere(std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCollision())) {
          // �m�b�N�o�b�N�����̊J�n
          _knockBack->Start();
          // �q�b�g�|�C���g�̌���
          _playerHP -= 100;
          _gaugeHp.Sub(100);
          // HP��������������ꍇ
          if (_playerHP <= 0) {
            _app.GameOver(); // �Q�[���I�[�o�[�����̌Ăяo��
          }
          // ���G���Ԃ��J�n����
          _invincible->Start();
        }
      }
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
      case PlayerState::JumpAttack1:
      case PlayerState::JumpAttack2:
      case PlayerState::JumpAttack3:
        return true;  // �U�����
      default:
        return false; // �U����Ԃł͂Ȃ�
      }
    }

    bool Player::SetStateParam(PlayerState pState) {
      // ��Ԃ̐؂�ւ�
      _playerState = pState;
      // �J�ڔ���t���[���̓o�^���s���Ă��邩�̔���
      if (chaneMap.contains(_playerState)) {
        // ���@�̏�Ԃ��擾
        auto [start, end] = chaneMap.at(_playerState);
        // �؂�ւ���Ԃ�ݒ肷��
        _stateComponent->Set(_modelAnim.GetMainPlayTime(), start, end);
        _stateComponent->Start();
      } 
      else {
        // �X�e�[�g�̐ݒ���I������
        _stateComponent->Finish();
      }

      // �U��������Z�b�g���邩
      if (!attackMap.contains(PlayerStateToNumber())) {
        return true;
      }
      // �U������Ŏg�p����t���[���ԍ��̎擾
      auto frames = attackMap.at(PlayerStateToNumber());
      // �t���[���ƃR���W�������̐ݒ�
      _attack->SetFrame(frames, AddSpheres(static_cast<int>(frames.size())));
      return true; // �؂�ւ�������
    }

    int Player::PlayerStateToNumber() const {
      auto number = -1;
      // �v���C���[�̏�Ԃɉ��������l��Ԃ�
      switch (_playerState) {
        // �ҋ@
      case PlayerState::Idle:
        return StateNumberIdle;
        // ����
      case PlayerState::Walk:
        return StateNumberWalk;
        // ����
      case PlayerState::Run:
        return StateNumberRun;
        // �W�����v
      case PlayerState::Jump:
        return StateNumberJump;
        // �U��1
      case PlayerState::Attack1:
        number = StateNumberLight1;
        break;
        // �U��2
      case PlayerState::Attack2:
        number = StateNumberLight2;
        break;
        // �U��3
      case PlayerState::Attack3:
        number = StateNumberLight3;
        break;
        // �󒆍U��1
      case PlayerState::JumpAttack1:
        number = StateNumberAirLight1;
        break;
        // �󒆍U��2
      case PlayerState::JumpAttack2:
        number = StateNumberAirLight2;
        break;
        // �󒆍U��3
      case PlayerState::JumpAttack3:
        number = StateNumberAirLight3;
        break;
        // �G�L�T�C�g�g���b�N
      case PlayerState::ExciteTrick:
        return StateNumberExcite;
        // �_�b�V��
      case PlayerState::Dash:
        return StateNumberDash;
      default:
        return -1;
      }
      // ���U���E��U�����̔���
      auto IsHevyLight = [](bool flag) {
        return (flag == true) ? 1 : 0;
      };
      // �U���ԍ�
      return number + IsHevyLight(_attackFlag);
    }

    bool Player::PlayEffect() const {
      auto modelAnim = animMap.at(PlayerStateToNumber());
#ifndef _DEBUG
      auto eRad = -_rotation.GetY();
#else
      auto eRad = -AppMath::Utility::DegreeToRadian(_rotation.GetY());
#endif
      // �G�t�F�N�g�̍Đ�
      _app.GetEffectServer().MakeEffect(modelAnim.Effect(), _position, eRad);
      return true;
    }

    void Player::Invincible() {
      // ���G��Ԃ�
      switch (_invincible->Invincible()) {
      case true:
        // ���G���Ԃ̌o�ߏ������Ăяo��
        _invincible->Process();
        break;
      case false:
        // ���G��Ԃł͂Ȃ��ꍇ�A�_���[�W������s��
        IsDamage();
        break;
      }
    }

    bool Player::StandFloor(Object::CollisionCapsule capsule, const AppMath::Vector4& position) {
      // �����̎擾
      const auto [start, end] = capsule.LineSegment().GetVector();
      // �n�`(��)�Ɛ����̏Փ˔���
      for (int i = 0; i < _app.GetStageComponent().GetStageModel().size(); i++) {
        // �X�e�[�W�n���h���̎擾
        auto handleMap = _app.GetStageComponent().GetStageModel()[i];
        // �n�`�Ɛ����̏Փ˔���
        auto hit = MV1CollCheck_Line(handleMap, 2, UtilityDX::ToVECTOR(end), UtilityDX::ToVECTOR(start));
        // �Փ˃t���O���Ȃ��ꍇ
        if (hit.HitFlag == 0) {
          continue;
        }
        // �Փ˒n�_�����W�ɑ��
        _position = UtilityDX::ToVector(hit.HitPosition);
        // �V�������W���R���W�����ɔ��f
        _capsule->SetPosition(_position);
        return true; // �ڐG���Ă���
      }
      return false;  // �ڐG���Ă��Ȃ�
    }

    bool Player::IsStandObject(Object::CollisionCapsule capsule, AppMath::Vector4& position) {
      // �I�u�W�F�N�g�T�[�o�̎擾
      auto object = _app.GetObjectServer();
      // �x�N�g���̎擾
      auto [min, max] = capsule.LineSegment().GetVector();
      // ��Q���̂݃\�[�g����
      for (auto obj : object.GetObjects()) {
        // �I�u�W�F�N�g�̔���
        if (obj->GetId() != ObjectBase::ObjectId::Item) continue;
        // �ΏۂƂ̐ڐG������s��
        auto item = std::dynamic_pointer_cast<Item::Box>(obj);
        // �R���W�������̎擾
        auto collision = item->GetCollision();
        // �߂荞��ł���ꍇ�͉����o���������s��
        if (collision.CheckPoint(min) || collision.CheckPoint(max)) {
          position.SetY(collision.GetMax().GetY());
          return true;
        }
      }
      return false;
    }

    std::vector<std::shared_ptr<Object::CollisionBase>> Player::AddSpheres(const int num, float radius) {
      // �����蔻����i�[����R���e�i
      std::vector<std::shared_ptr<Object::CollisionBase>> collision;
      collision.clear();
      for (auto number = 0; number <= num; ++number) {
        // �������������蔻���o�^
        collision.emplace_back(std::make_shared<Object::CollisionSphere>(*this, _position, radius));
      }
      return collision;
    }

    bool Player::OffScreen() {
      // ���Ɏ��S���Ă��邩
      if (IsDead()) {
        return true;
      }
      // ��ʊO�ɑ��Ă��邩
      return false;
    }

    bool Player::Heal(const float heal) {
      // �Q�[�W���ő�l�̏ꍇ�͍X�V���s��Ȃ�
      const auto max = _gaugeHp.GetMaxGauge();
      // ����HP�̎擾
      auto hp = _gaugeHp.GetFloatPoint();
      // �ő�l�̏ꍇ�͏������s��Ȃ�
      if (_gaugeHp.IsMax()) {
        return false;
      }
      // ���@���񕜂�����
      _gaugeHp.Add(heal);
      return true;
    }
  } // namespace Player
}// namespace Gyro
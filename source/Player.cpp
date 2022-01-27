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
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )

namespace {
  constexpr auto NoAnimation = -1; //!< �A�j���[�V�����̓A�^�b�`����Ă��Ȃ�
  constexpr auto InputMin = 2000.0f;  //!< ���͂��󂯕t����Œ�l
  constexpr auto InputMax = 32767.0f;

  constexpr auto MoveSpeed = 2.0f; //!< �f�t�H���g�̈ړ���
  constexpr auto MoveZero = 0.0f;
}

namespace Gyro {
  namespace Player {

    Player::Player(Application::ApplicationMain& app) : ObjectBase(app), _cam(app) {
      LoadResource(); // ���\�[�X�̓ǂݎ��
      Init();
    }

    bool Player::Init() {
      SetCamera(); // �J�����̐ݒ�
      SetState();  // �p�����[�^�̐ݒ�
      return true;
    }

    bool Player::Process() {
      // ���O��Ԃ̏ȗ�
      namespace App = AppFrame::Application;
      namespace AppMath = AppFrame::Math;
      // ���͏�Ԃ̎擾
      auto input = _app.GetOperation().GetXBoxState();
      auto [lX, lY] = input.GetStick(false); // ���X�e�B�b�N
      auto [rX, rY] = input.GetStick(true);  // �E�X�e�B�b�N
      auto [leftTrigger, rightTrigger] = input.GetTrigger(); // �g���K�[�{�^��
      // �J���������̎Z�o
      /*auto sX = _cam._pos.x - _cam._target.x;
      auto sZ = _cam._pos.z - _cam._target.z;
      auto camrad = atan2(sZ, sX);*/
      // ���ۂɎg�p����ړ���(2�����x�N�g��)
      auto stickLeft = AppMath::Vector4(lX , lY);
      auto stickRight = AppMath::Vector4(rX, rY);
      Move(stickLeft);

      auto oldPosition = _position; // �O�t���[�����W
      // �ړ��ʂ��Z�o����
      //AppMath::Vector4 move;
      //move = AppMath::Vector4(mx, 0.0f, my);
      //CameraUpdate(stickRight);
      // �J�����̍X�V
      _cam.Process(stickRight, _position, _move);
      auto oldState = _playerState;
      // ��Ԃ̍X�V
      SetRotation(_move);
      Animation(oldState);
      // ���W�̐ݒ�
      VECTOR p(_position.GetX(), _position.GetY(), _position.GetZ());
      MV1SetPosition(_model, p);
      // �X�J�C�X�t�B�A�̍��W
      MV1SetPosition(_handleSkySphere, p);
      // �X�e�[�W�̍��W
      MV1SetPosition(_handleMap, VGet(0, -1500, 0));
      return true;
    }

    bool Player::Draw() const {
      // �v���C���[�̕`��
      MV1SetScale(_model, VGet(10, 10, 10));
      MV1DrawModel(_model);
      // �X�J�C�X�t�B�A�̕`��
      MV1DrawModel(_handleSkySphere);
      MV1DrawMesh(_handleMap, 0);
#ifdef _DEBUG
      DebugString(); // Debug���̏o�͂��s��
      // �J�������̕`��
      _cam.Draw(_position, _move);
#endif
      return true;
    }

    void Player::Input() {
      
    }

    void Player::Move(AppMath::Vector4 move) {
      _move.Fill(0.0f); // ������
      // ���͂��󂯕t���邩
      if (move.Length2D() < InputMin) {
        return;
      }
      // ���s�ړ�
      auto x = (move.GetX() / 30000) * MoveSpeed;
      auto z = (move.GetY() / 30000) * MoveSpeed;
      _move = AppMath::Vector4(x, 0.0f, z);
      _position.Add(_move); //!< �ړ��ʂɉ��Z����
      return;
    }

    void Player::LoadResource() {
      // �e�탊�\�[�X�̓ǂݎ�菈��
      _model = MV1LoadModel("res/Player/Gyro_multimotion.mv1"); // �v���C���[
      _handleSkySphere = MV1LoadModel("res/SkySphere/skysphere.mv1"); // �X�J�C�X�t�B�A
      _handleMap = MV1LoadModel("res/Stage/houseGEO.mv1");
      //_frameMapCollision = MV1SearchFrame(_handleMap, "ground_navmesh");
    }

    void Player::SetCamera() {
      // �J�����̏�����
      _cam.Init();
    }

    void Player::SetState() {
      // ��Ԃ̐ݒ�
      _id = ObjectId::Player;
      _state = ObjectState::Active;
      // ���W�E�����̐ݒ�
      namespace AppMath = AppFrame::Math;
      _position = AppMath::Vector4();
      _rotation = AppMath::Vector4();
      // �A�j���[�V�����̏�����
      _animaIndex = NoAnimation;
      _animaTime = 0.0f;
      _totalTime = 0.0f;
    }

    float Player::Speed(const AppFrame::Math::Vector4 stick) const {
      // �ړ��ʂ͂��邩
      auto length = stick.Length2D();
      auto rad = atan2(stick.GetX(), stick.GetY());
      // ���͋�����Ȃ��ꍇ�͈ړ��ʂ�0�ɂ���
      if (length < InputMin) {
        return MoveZero;
      }
      return MoveSpeed;
    }

    void Player::CameraUpdate(const AppFrame::Math::Vector4 stick) {
      
    }

    void Player::SetRotation(const AppFrame::Math::Vector4 move) {
      // �ړ��ʂ�����ꍇ�͌�����ύX����
      if (move.Length()) {
        _rotation = move;
        _playerState = PlayerState::Walk;
      }
      _playerState = PlayerState::Idle;
    }

    void Player::Animation(PlayerState old) {
      // �A�j���[�V��������
      MV1SetAttachAnimTime(_model, _animaIndex, _animaTime);
      // �O�t���[���ƈقȂ�ꍇ�̏���
      if (_playerState == old) {
        _animaTime += 0.5f; // �Đ����Ԃ�i�߂�
        // �A�j���[�V�������I���������̔���
        if (_totalTime <= _animaTime) {
          // �A�j���[�V������؂�ւ���
          AttachAnima(GetAnimaKey());
        }
        return;
      }
      // ���݂̃A�j���[�V������j��
      MV1DetachAnim(_model, _animaIndex);
      _animaIndex = -1;
      // �A�j���[�V������؂�ւ���
      AttachAnima(GetAnimaKey());
    }

    int Player::AnimaIndex(std::string_view key) const {
      return MV1GetAnimIndex(_model, key.data());
    }

    bool Player::AttachAnima(std::string_view key) {
      // �A�j���[�V�����ԍ��̎擾
      _animaIndex = AnimaIndex(key);
      // �擾�ɐ����������̔���
      if (_animaIndex == -1) {
#ifdef _DEBUG
        throw ("�A�j���[�V�����ԍ��̎擾�Ɏ��s���܂���\n");
#endif
        return false;
      }
      // �A�j���[�V�������A�^�b�`
      MV1AttachAnim(_model, _animaIndex, -1, false);
      // ���Đ����Ԃ��X�V
      _totalTime = MV1GetAttachAnimTotalTime(_model, _animaIndex);
      _animaTime = 0.0f; // �Đ����Ԃ�0�ɂ���
      return true;
    }

    std::string_view Player::GetAnimaKey() const {
      // ��Ԃɉ������L�[��Ԃ�
      switch (_playerState) {
      case PlayerState::Idle:
        return "idle";
      case PlayerState::Run:
        return "run";
      case PlayerState::Walk:
        return "Walk";
      case PlayerState::Jump:
        return "Jump";
      case PlayerState::Attack:
        return "Attack";
      default:
        return "";
      }
    }

#ifdef _DEBUG
    void Player::DebugString() const {
      // ���W���o�͂���
      auto[x, y, z] = _position.GetVector3();
      DrawFormatString(0, 0, 255, "x:%f  y:%f, z:%f", x, y, z);
      auto [lx, ly] = _app.GetOperation().GetXBoxState().GetStick(false);
      DrawFormatString(0, 20, 255, "lx:%d  ly:%d", lx, ly);
      auto [rx, ry] = _app.GetOperation().GetXBoxState().GetStick(true);
      DrawFormatString(0, 40, 255, "lx:%d  ly:%d", rx, ry);
    }
#endif

  } // namespace Player
}// namespace Gyro

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

    Player::Player(Application::ApplicationMain& app) : ObjectBase(app) {
      LoadResource(); // ���\�[�X�̓ǂݎ��
      Init();
    }

    bool Player::Init() {
      SetCamera(); // �J�����̐ݒ�
      SetState();  // �p�����[�^�̐ݒ�
      _modelAnim.SetMainAttach(_model, 5, 1.0f, true);
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

        // ���ۂɎg�p����ړ���(2�����x�N�g��)
        auto stickLeft = AppMath::Vector4(lX, lY);
        auto stickRight = AppMath::Vector4(rX, rY);
        Move(stickLeft);

        auto oldPosition = _position; // �O�t���[�����W
        
        // �J�����̍X�V
        _app.GetCamera().Process(stickRight, _position, _move);
        auto oldState = _playerState;
        // ��Ԃ̍X�V
        SetRotation(_move);
        //if (input.GetButton(XINPUT_BUTTON_Y, false)) {
        //    _playerState = PlayerState::Attack1;
        //}else {
        //    //_playerState = PlayerState::Idle;
        //}
        Animation(oldState);
        _modelAnim.Process();
        // ���W����VECTOR�\���̂ɕϊ�
        auto vPosition = UtilityDX::ToVECTOR(_position);
        auto world = WorldMatrix();
        // ���[���h���W�̐ݒ�
        MV1SetMatrix(_model, UtilityDX::ToMATRIX(world));
        // MV1SetPosition(_model, vPosition);
        auto rotationY = AppMath::Vector4(0.0f, _rotation.GetY(), 0.0f);
        // ���f���̌�����ݒ肷��
        // MV1SetRotationXYZ(_model, UtilityDX::ToVECTOR(rotationY));
        // �X�J�C�X�t�B�A�̍��W
        MV1SetPosition(_handleSkySphere, vPosition);
        // �X�e�[�W�̍��W
        MV1SetPosition(_handleMap, VGet(0, -1500, 0));
        return true;
    }

    bool Player::Draw() const {
      // �v���C���[�̕`��
      auto scale = _scale;
      MV1SetScale(_model, UtilityDX::ToVECTOR(scale));
      MV1DrawModel(_model);
      // �X�J�C�X�t�B�A�̕`��
      MV1DrawModel(_handleSkySphere);
      MV1DrawModel(_handleMap);
#ifdef _DEBUG
      DebugString(); // Debug���̏o�͂��s��
      // �J�������̕`��
      _app.GetCamera().Draw(_position, _move);
#endif
        return true;
    }

    void Player::Input() {

    }

    void Player::Move(AppMath::Vector4 move) {
        _move.Fill(0.0f); // �ړ��ʏ�����
        // �ړ��ʂ�0�̏ꍇ�͓��͂��󂯕t���Ȃ�
        if (move.LengthSquared() == 0.0f) {
            return;
        }
        auto x = (move.GetX() / 30000) * MoveSpeed; // x���̈ړ���
        auto z = (move.GetY() / 30000) * MoveSpeed; // y���̈ړ���
        _move = AppMath::Vector4(x, 0.0f, z);
        _position.Add(_move); //!< �ړ��ʂɉ��Z����
        
        auto angle = std::atan2(move.GetX() * -1, move.GetY() * -1);
        
        _rotation.SetY(angle);
        // �J���������̎Z�o
        //auto  sX = _app.GetCamera().CamPosGetX() - _app.GetCamera().CamTarGetX();
        //auto  sZ = _app.GetCamera().CamPosGetZ() - _app.GetCamera().CamTarGetZ();
        //auto camrad = atan2(sZ, sX);
        //auto rad = atan2(move.GetX(), move.GetZ());
        //// ���s�ړ�
        //auto x = cos(rad + camrad) * MoveSpeed;
        //auto z = sin(rad + camrad) * MoveSpeed;
        return;
    }

    void Player::LoadResource() {
        // �e�탊�\�[�X�̓ǂݎ�菈��
        _model = MV1LoadModel("res/Player/Gyro multibag.mv1"); // �v���C���[
        _handleSkySphere = MV1LoadModel("res/SkySphere/skysphere.mv1"); // �X�J�C�X�t�B�A
        _handleMap = MV1LoadModel("res/Stage/houseGEO_1.mv1");
    }

    void Player::SetCamera() {

    }


    void Player::SetState() {
      // ��Ԃ̐ݒ�
      _id = ObjectId::Player;
      _state = ObjectState::Active;
      // ���W�E�����̐ݒ�
      namespace AppMath = AppFrame::Math;
      _position = AppMath::Vector4();
      _rotation = AppMath::Vector4();
      _scale = { 10.0f, 10.0f, 10.0f };
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
      if (move.LengthSquared()) {
        using Utility = AppFrame::Math::Utility;
        // ���͏��̃t�B���^�����O���s��
        //auto n = move.Normalize();
        //auto angle = std::atan2(n.GetX(), n.GetY()) - Utility::_pi / 2;
        //_rotation.SetY(angle);
        _playerState = PlayerState::Walk;
      }
      _playerState = PlayerState::Idle;
    }

    void Player::Animation(PlayerState old) {
        // ���@�̏�Ԃɍ��킹�ăA�j���[�V�����ω�
        if (old != _playerState) {
            switch (_playerState) {
            case PlayerState::Idle:
                _modelAnim.SetBlendAttach(5, 10.0f, 1.0f, true);
                break;
            case PlayerState::Walk:
                _modelAnim.SetBlendAttach(17, 10.0f, 1.0f, true);
                break;
            case PlayerState::Run:
                _modelAnim.SetBlendAttach(1, 10.0f, 1.0f, true);
                break;
            case PlayerState::Attack1:
                _modelAnim.SetBlendAttach(13, 10.0f, 1.0f, false);
                break;
            case PlayerState::Attack2:
                _modelAnim.SetBlendAttach(14, 10.0f, 1.0f, false);
                break;
            case PlayerState::Attack3:
                _modelAnim.SetBlendAttach(15, 10.0f, 1.0f, false);
                break;
            case PlayerState::Jump:
                _modelAnim.SetBlendAttach(12, 10.0f, 1.0f, false);
                break;
            default:
                break;
            }
        }

      //// �A�j���[�V��������
      //MV1SetAttachAnimTime(_model, _animaIndex, _animaTime);
      //// �O�t���[���ƈقȂ�ꍇ�̏���
      //if (_playerState == old) {
      //  _animaTime += 0.5f; // �Đ����Ԃ�i�߂�
      //  // �A�j���[�V�������I���������̔���
      //  if (_totalTime <= _animaTime) {
      //    // �A�j���[�V������؂�ւ���
      //    AttachAnima(GetAnimaKey());
      //  }
      //  return;
      //}
      //// ���݂̃A�j���[�V������j��
      //MV1DetachAnim(_model, _animaIndex);
      //_animaIndex = -1;
      //// �A�j���[�V������؂�ւ���
      //AttachAnima(GetAnimaKey());
    }

    /*int Player::AnimaIndex(std::string_view key) const {
      return MV1GetAnimIndex(_model, key.data());
    }*/

//    bool Player::AttachAnima(std::string_view key) {
//      // �A�j���[�V�����ԍ��̎擾
//      _animaIndex = AnimaIndex(key);
//      // �擾�ɐ����������̔���
//      if (_animaIndex == -1) {
//#ifdef _DEBUG
//        throw ("�A�j���[�V�����ԍ��̎擾�Ɏ��s���܂���\n");
//#endif
//        return false;
//      }
//      // �A�j���[�V�������A�^�b�`
//      auto a = MV1AttachAnim(_model, _animaIndex, -1, false);
//      // ���Đ����Ԃ��X�V
//      _totalTime = MV1GetAttachAnimTotalTime(_model, a);
//      _animaTime = 0.0f; // �Đ����Ԃ�0�ɂ���
//      return true;
//    }
//
//    std::string_view Player::GetAnimaKey() const {
//      // ��Ԃɉ������L�[��Ԃ�
//      switch (_playerState) {
//      case PlayerState::Idle:
//        return "GyroIdle";
//      case PlayerState::Run:
//        return "GyroDash";
//      case PlayerState::Walk:
//        return "GyroWalk";
//      case PlayerState::Jump:
//        return "GyroJUp";
//      case PlayerState::Attack1:
//        return "GyroLaw1";
//      case PlayerState::Attack2:
//        return "GyroLaw2";
//      case PlayerState::Attack3:
//        return "GyroLaw3";
//      default:
//        return "";
//      }
//    }

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

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
  constexpr auto InputMin = 0.3f;  //!< ���͂��󂯕t����Œ�l
  constexpr auto InputMax = 32767.0f;

  constexpr auto MoveSpeed = 6.0f; //!< �f�t�H���g�̈ړ���
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
      auto stickLeft = AppMath::Vector4(lX / InputMax, lY / InputMax);
      auto stickRight = AppMath::Vector4(rX / InputMax, rY / InputMax);
      // �J���������̎Z�o
      auto sX = _cam._pos.x - _cam._target.x;
      auto sZ = _cam._pos.z - _cam._target.z;
      auto camrad = atan2(sZ, sX);
      // �ړ��ʂ͂��邩
      auto length = stickLeft.Length2D();
      auto rad = atan2(stickLeft.GetX(), stickLeft.GetY());

      float mx, my;
      if (lX == 0) {
        mx = 0.0f;
      }
      else mx = (stickLeft.GetX() / InputMax) * 10.0f;
      if (lY == 0) {
        my = 0.0f;
      }
      else my = (stickLeft.GetY() / InputMax) * 10.0f;

      auto oldPosition = _position; // �O�t���[�����W
      // �ړ��ʂ��Z�o����
      AppMath::Vector4 move;
      move = AppMath::Vector4(mx, 0.0f, my);
      CameraUpdate(stickRight);
      // ���W���X�V����
      _position.Add(move);
      auto oldState = _playerState;
      // ��Ԃ̍X�V
      SetRotation(move);
      Animation(oldState);
      // ���W�̐ݒ�
      VECTOR p(_position.GetX(), _position.GetY(), _position.GetZ());
      MV1SetPosition(_model, p);
      return true;
    }

    bool Player::Draw() const {
      // �v���C���[�̕`��
      MV1DrawModel(_model);
      // �X�J�C�X�t�B�A�̕`��
      MV1DrawModel(_handleSkySphere);
      MV1DrawModel(_handleMap);
      // �J�����ݒ�X�V
      SetCameraPositionAndTarget_UpVecY(_cam._pos, _cam._target);
      SetCameraNearFar(_cam._clipNear, _cam._clipFar);
#ifdef _DEBUG
      DebugString(); // Debug���̏o�͂��s��
#endif
      return true;
    }

    void Player::Input() {
      
    }

    void Player::LoadResource() {
      // �e�탊�\�[�X�̓ǂݎ�菈��
      _model = MV1LoadModel("res/SDChar.mv1"); // �v���C���[
      _handleSkySphere = MV1LoadModel("res/skysphere.mv1"); // �X�J�C�X�t�B�A
      _handleMap = MV1LoadModel("res/Ground.mv1");
      _frameMapCollision = MV1SearchFrame(_handleMap, "ground_navmesh");
    }

    void Player::SetCamera() {
      // �J�����̏�����
      _cam._pos = VGet(0, 90.0f, -300.0f);
      _cam._target = VGet(0, 80.0f, 0);
      _cam._clipNear = 2.0f;
      _cam._clipFar = 10000.0f;
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
      float sx = _cam._pos.x - _cam._target.x;
      float sz = _cam._pos.z - _cam._target.z;
      float rad = atan2(sz, sx);
      float length = sqrt(sz * sz + sx * sx);
      if (stick.GetX() > InputMin) { rad -= 0.05f; }
      if (stick.GetX() < -InputMin) { rad += 0.05f; }
      _cam._pos.x = _cam._target.x + cos(rad) * length;
      _cam._pos.z = _cam._target.z + sin(rad) * length;
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
      _totalTime = MV1GetAnimTotalTime(_model, _animaIndex);
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
      DrawFormatString(0, 20, 255, "lx:%f  ly:%f", lx, ly);
    }
#endif

  } // namespace Player
    //namespace Player {

    //  Player::Player(Application::ApplicationMain& app) : ObjectBase(app) {
    //    // �e��
    //    _handleModel = MV1LoadModel("res/SDChar.mv1"); // �v���C���[
    //    _handleSkySphere = MV1LoadModel("res/skysphere.mv1"); // �X�J�C�X�t�B�A
    //    _handleMap = MV1LoadModel("res/Ground.mv1");
    //    _frameMapCollision = MV1SearchFrame(_handleMap, "ground_navmesh");
    //  }


    //    Player::Player(Application::ApplicationMain& app) : Object::ObjectBase(app) {
    //      
    //        _handleModel = MV1LoadModel("res/SDChar.mv1"); // �v���C���[
    //        _handleSkySphere = MV1LoadModel("res/skysphere.mv1"); // �X�J�C�X�t�B�A
    //        _handleMap = MV1LoadModel("res/Ground.mv1");
    //        _frameMapCollision = MV1SearchFrame(_handleMap, "ground_navmesh");
    //        _attachIndex = -1;
    //        _totalTime = 0.0f;
    //        _playTime = 0.0f;
    //        _position = VGet(0.0f, 0.0f, 0.0f);
    //        _dir = VGet(0.0f, 0.0f, 0.0f);
    //        _state = STATE::IDLE;
    //        // �J����
    //        _cam._pos = VGet(0, 90.0f, -300.0f);
    //        _cam._target = VGet(0, 80.0f, 0);
    //        _cam._clipNear = 2.0f;
    //        _cam._clipFar = 10000.0f;
    //    }

    //    bool Player::Init() {
    //        // ������

    //        //// �J����
    //        //_cam._pos = VGet(0, 90.0f, -300.0f);
    //        //_cam._target = VGet(0, 80.0f, 0);
    //        //_cam._clipNear = 2.0f;
    //        //_cam._clipFar = 10000.0f;

    //        return true;
    //    }

    //    bool Player::Process() {
    //        auto joypad = _app.GetOperation().GetJoypadState();
    //        auto key = joypad.GetKey();
    //        auto trigger = joypad.GetTriggerKey();
    //        auto [stickX, stickY] = joypad.GetAnalogStick();

    //        STATE oldState = _state;

    //        DINPUT_JOYSTATE di;
    //        GetJoypadDirectInputState(DX_INPUT_PAD1, &di);
    //        float lx, ly, rx, ry;	// ���E�A�i���O�X�e�B�b�N�̍��W
    //        float analogMin = 0.3f;	// �A�i���O臒l
    //        // Logicool�p�b�h�̏ꍇ
    //        lx = (float)di.X / 1000.f; ly = (float)di.Y / 1000.f;
    //        rx = (float)di.Z / 1000.f; ry = (float)di.Rz / 1000.f;

    //        // �L�����ړ�(�J�����ݒ�ɍ��킹��)

    //        // �J�����̌����Ă���p�x���擾
    //        float sx = _cam._pos.x - _cam._target.x;
    //        float sz = _cam._pos.z - _cam._target.z;
    //        float camrad = atan2(sz, sx);

    //        // �ړ����������߂�
    //        VECTOR v = { 0,0,0 };
    //        float mvSpeed = 6.f;

    //        // �A�i���O���X�e�B�b�N�p
    //        float length = sqrt(lx * lx + ly * ly);
    //        float rad = atan2(lx, ly);
    //        if (length < analogMin) {
    //            // ���͂������������瓮���Ȃ��������Ƃɂ���
    //            length = 0.f;
    //        }
    //        else {
    //            length = mvSpeed;
    //        }

    //        // �ړ��O�̈ʒu��ۑ�
    //        VECTOR oldvPos = _position;
    //        VECTOR oldv = v;

    //        // �R���W��������ň��������������ɁAescapeTbl[]���Ɋp�x��ς��ĉ�������݂�
    //        float escapeTbl[] = {
    //            0, -10, 10, -20, 20, -30, 30, -40, 40, -50, 50, -60, 60, -70, 70, -80, 80,
    //        };
    //        for (int i = 0; i < sizeof(escapeTbl) / sizeof(escapeTbl[0]); i++) {
    //            // escapeTbl[i]�̕������ړ���v��]
    //            float escape_rad = DEG2RAD(escapeTbl[i]);
    //            v.x = cos(rad + camrad + escape_rad) * length;
    //            v.z = sin(rad + camrad + escape_rad) * length;

    //            // v�̕��ړ�
    //            _position = VAdd(_position, v);
    //        }

    //        // �ړ��ʂ����̂܂܃L�����̌����ɂ���
    //        if (VSize(v) > 0.f) {		// �ړ����Ă��Ȃ����͖������邽��
    //            _dir = v;
    //            _state = STATE::WALK;
    //            MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "run"), -1, false);
    //        }
    //        else {
    //            _state = STATE::IDLE;
    //            MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "idle"), -1, false);
    //        }

    //        { // �J�����̑�����s��(�E�X�e�B�b�N)
    //            // Y����]
    //            float sx = _cam._pos.x - _cam._target.x;
    //            float sz = _cam._pos.z - _cam._target.z;
    //            float rad = atan2(sz, sx);
    //            float length = sqrt(sz * sz + sx * sx);
    //            if (rx > analogMin) { rad -= 0.05f; }
    //            if (rx < -analogMin) { rad += 0.05f; }
    //            _cam._pos.x = _cam._target.x + cos(rad) * length;
    //            _cam._pos.z = _cam._target.z + sin(rad) * length;
    //        }

    //        // �X�e�[�^�X���ς���Ă��Ȃ����H
    //        if (oldState == _state) {
    //            // �Đ����Ԃ�i�߂�
    //            _playTime += 0.5f;
    //        }
    //        else {
    //            // �A�j���[�V�������A�^�b�`����Ă�����A�f�^�b�`����
    //            if (_attachIndex != -1) {
    //                MV1DetachAnim(_handleModel, _attachIndex);
    //                _attachIndex = -1;
    //            }
    //            // �X�e�[�^�X�ɍ��킹�ăA�j���[�V�����̃A�^�b�`
    //            switch (_state) {
    //            case STATE::IDLE:
    //                _attachIndex = MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Wait"), -1, FALSE);
    //                break;
    //            case STATE::WALK:
    //                _attachIndex = MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Run"), -1, FALSE);
    //                break;
    //            }
    //            // �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
    //            _totalTime = MV1GetAttachAnimTotalTime(_handleModel, _attachIndex);
    //            // �Đ����Ԃ�������
    //            _playTime = 0.0f;
    //        }

    //        // �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
    //        if (_playTime >= _totalTime) {
    //            _playTime = 0.0f;
    //        }

    //        // �Đ����Ԃ��Z�b�g����
    //        MV1SetAttachAnimTime(_handleModel, _attachIndex, _playTime);
    //        // �ʒu
    //        MV1SetPosition(_handleModel, _position);
    //       // MV1SetPosition(_handleSkySphere, _position);
    //        // ��������Y����]���Z�o
    //        VECTOR vRot = { 0,0,0 };
    //        vRot.y = atan2(_dir.x * -1, _dir.z * -1);		// ���f�����W���łǂ���������Ă��邩�Ŏ����ς��(�����-z�������Ă���ꍇ)
    //        MV1SetRotationXYZ(_handleModel, vRot);

    //        /*switch (_state) {
    //        case STATE::IDLE:
    //            MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Wait"), -1, false);
    //            break;
    //        case STATE::WALK:
    //            MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Walk"), -1, false);
    //            break;
    //        case STATE::RUN:
    //            MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Run"), -1, false);
    //            break;
    //        case STATE::ATTACK:
    //            MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Kick1"), -1, false);
    //            break;
    //        case STATE::JUMP:
    //            MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Jump1"), -1, false);
    //            break;
    //        default:
    //            break;
    //        }*/

    //        return true;
    //    }

    //    bool Player::Draw() const {

    //        // �v���C���[�̕`��
    //        MV1DrawModel(_handleModel);

    //        // �X�J�C�X�t�B�A�̕`��
    //        MV1DrawModel(_handleSkySphere);
    //        MV1DrawModel(_handleMap);

    //        // �J�����ݒ�X�V
    //        SetCameraPositionAndTarget_UpVecY(_cam._pos, _cam._target);
    //        SetCameraNearFar(_cam._clipNear, _cam._clipFar);

    //        // ���C�g�ݒ�
    //        //SetUseLighting(TRUE);

    //        return true;
    //    }
    }// namespace Player
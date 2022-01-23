/*****************************************************************//**
 * @file   Player.cpp
 * @brief  �I�u�W�F�N�g�x�[�X�̃T�u�N���X�̒�`
 *
 * @author �y������
 * @date   January 2022
 *********************************************************************/
#include "Player.h"
#include "ApplicationMain.h"
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )

namespace {
  constexpr auto NoAnimation = -1; //!< �A�j���[�V�����̓A�^�b�`����Ă��Ȃ�
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
      // 
    }

    void Player::Input() {
      // ���͏�Ԃ̎擾
      auto input = _app.GetOperation().GetJoypadState();
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

  } // namespace Player
    namespace Player {

      Player::Player(Application::ApplicationMain& app) : ObjectBase(app) {
        // �e��
        _handleModel = MV1LoadModel("res/SDChar.mv1"); // �v���C���[
        _handleSkySphere = MV1LoadModel("res/skysphere.mv1"); // �X�J�C�X�t�B�A
        _handleMap = MV1LoadModel("res/Ground.mv1");
        _frameMapCollision = MV1SearchFrame(_handleMap, "ground_navmesh");
      }


        Player::Player(Application::ApplicationMain& app) : Object::ObjectBase(app) {
          
            _handleModel = MV1LoadModel("res/SDChar.mv1"); // �v���C���[
            _handleSkySphere = MV1LoadModel("res/skysphere.mv1"); // �X�J�C�X�t�B�A
            _handleMap = MV1LoadModel("res/Ground.mv1");
            _frameMapCollision = MV1SearchFrame(_handleMap, "ground_navmesh");
            _attachIndex = -1;
            _totalTime = 0.0f;
            _playTime = 0.0f;
            _position = VGet(0.0f, 0.0f, 0.0f);
            _dir = VGet(0.0f, 0.0f, 0.0f);
            _state = STATE::IDLE;
            // �J����
            _cam._pos = VGet(0, 90.0f, -300.0f);
            _cam._target = VGet(0, 80.0f, 0);
            _cam._clipNear = 2.0f;
            _cam._clipFar = 10000.0f;
        }

        bool Player::Init() {
            // ������

            //// �J����
            //_cam._pos = VGet(0, 90.0f, -300.0f);
            //_cam._target = VGet(0, 80.0f, 0);
            //_cam._clipNear = 2.0f;
            //_cam._clipFar = 10000.0f;

            return true;
        }

        bool Player::Process() {
            auto joypad = _app.GetOperation().GetJoypadState();
            auto key = joypad.GetKey();
            auto trigger = joypad.GetTriggerKey();
            auto [stickX, stickY] = joypad.GetAnalogStick();

            STATE oldState = _state;

            DINPUT_JOYSTATE di;
            GetJoypadDirectInputState(DX_INPUT_PAD1, &di);
            float lx, ly, rx, ry;	// ���E�A�i���O�X�e�B�b�N�̍��W
            float analogMin = 0.3f;	// �A�i���O臒l
            // Logicool�p�b�h�̏ꍇ
            lx = (float)di.X / 1000.f; ly = (float)di.Y / 1000.f;
            rx = (float)di.Z / 1000.f; ry = (float)di.Rz / 1000.f;

            // �L�����ړ�(�J�����ݒ�ɍ��킹��)

            // �J�����̌����Ă���p�x���擾
            float sx = _cam._pos.x - _cam._target.x;
            float sz = _cam._pos.z - _cam._target.z;
            float camrad = atan2(sz, sx);

            // �ړ����������߂�
            VECTOR v = { 0,0,0 };
            float mvSpeed = 6.f;

            // �A�i���O���X�e�B�b�N�p
            float length = sqrt(lx * lx + ly * ly);
            float rad = atan2(lx, ly);
            if (length < analogMin) {
                // ���͂������������瓮���Ȃ��������Ƃɂ���
                length = 0.f;
            }
            else {
                length = mvSpeed;
            }

            // �ړ��O�̈ʒu��ۑ�
            VECTOR oldvPos = _position;
            VECTOR oldv = v;

            // �R���W��������ň��������������ɁAescapeTbl[]���Ɋp�x��ς��ĉ�������݂�
            float escapeTbl[] = {
                0, -10, 10, -20, 20, -30, 30, -40, 40, -50, 50, -60, 60, -70, 70, -80, 80,
            };
            for (int i = 0; i < sizeof(escapeTbl) / sizeof(escapeTbl[0]); i++) {
                // escapeTbl[i]�̕������ړ���v��]
                float escape_rad = DEG2RAD(escapeTbl[i]);
                v.x = cos(rad + camrad + escape_rad) * length;
                v.z = sin(rad + camrad + escape_rad) * length;

                // v�̕��ړ�
                _position = VAdd(_position, v);
            }

            // �ړ��ʂ����̂܂܃L�����̌����ɂ���
            if (VSize(v) > 0.f) {		// �ړ����Ă��Ȃ����͖������邽��
                _dir = v;
                _state = STATE::WALK;
                MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "run"), -1, false);
            }
            else {
                _state = STATE::IDLE;
                MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "idle"), -1, false);
            }

            { // �J�����̑�����s��(�E�X�e�B�b�N)
                // Y����]
                float sx = _cam._pos.x - _cam._target.x;
                float sz = _cam._pos.z - _cam._target.z;
                float rad = atan2(sz, sx);
                float length = sqrt(sz * sz + sx * sx);
                if (rx > analogMin) { rad -= 0.05f; }
                if (rx < -analogMin) { rad += 0.05f; }
                _cam._pos.x = _cam._target.x + cos(rad) * length;
                _cam._pos.z = _cam._target.z + sin(rad) * length;
            }

            // �X�e�[�^�X���ς���Ă��Ȃ����H
            if (oldState == _state) {
                // �Đ����Ԃ�i�߂�
                _playTime += 0.5f;
            }
            else {
                // �A�j���[�V�������A�^�b�`����Ă�����A�f�^�b�`����
                if (_attachIndex != -1) {
                    MV1DetachAnim(_handleModel, _attachIndex);
                    _attachIndex = -1;
                }
                // �X�e�[�^�X�ɍ��킹�ăA�j���[�V�����̃A�^�b�`
                switch (_state) {
                case STATE::IDLE:
                    _attachIndex = MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Wait"), -1, FALSE);
                    break;
                case STATE::WALK:
                    _attachIndex = MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Run"), -1, FALSE);
                    break;
                }
                // �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
                _totalTime = MV1GetAttachAnimTotalTime(_handleModel, _attachIndex);
                // �Đ����Ԃ�������
                _playTime = 0.0f;
            }

            // �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
            if (_playTime >= _totalTime) {
                _playTime = 0.0f;
            }

            // �Đ����Ԃ��Z�b�g����
            MV1SetAttachAnimTime(_handleModel, _attachIndex, _playTime);
            // �ʒu
            MV1SetPosition(_handleModel, _position);
           // MV1SetPosition(_handleSkySphere, _position);
            // ��������Y����]���Z�o
            VECTOR vRot = { 0,0,0 };
            vRot.y = atan2(_dir.x * -1, _dir.z * -1);		// ���f�����W���łǂ���������Ă��邩�Ŏ����ς��(�����-z�������Ă���ꍇ)
            MV1SetRotationXYZ(_handleModel, vRot);

            /*switch (_state) {
            case STATE::IDLE:
                MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Wait"), -1, false);
                break;
            case STATE::WALK:
                MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Walk"), -1, false);
                break;
            case STATE::RUN:
                MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Run"), -1, false);
                break;
            case STATE::ATTACK:
                MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Kick1"), -1, false);
                break;
            case STATE::JUMP:
                MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Jump1"), -1, false);
                break;
            default:
                break;
            }*/

            return true;
        }

        bool Player::Draw() const {

            // �v���C���[�̕`��
            MV1DrawModel(_handleModel);

            // �X�J�C�X�t�B�A�̕`��
            MV1DrawModel(_handleSkySphere);
            MV1DrawModel(_handleMap);

            // �J�����ݒ�X�V
            SetCameraPositionAndTarget_UpVecY(_cam._pos, _cam._target);
            SetCameraNearFar(_cam._clipNear, _cam._clipFar);

            // ���C�g�ݒ�
            //SetUseLighting(TRUE);

            return true;
        }
    }// namespace Player
}// namespace Gryo


/*****************************************************************//**
 * @file   Player.cpp
 * @brief  �I�u�W�F�N�g�x�[�X�̃T�u�N���X�̒�`
 *
 * @author �y������
 * @date   January 2022
 *********************************************************************/
#include "Player.h"
#include "ApplicationMain.h"

namespace Gyro {
    namespace Player {

        Player::Player(Application::ApplicationMain& app) : Object::ObjectBase(app) {
            Init();
        }

        bool Player::Init() {
            // ������
            _handleModel = MV1LoadModel("res/sera.mv1"); // �v���C���[
            _handleSkySphere = MV1LoadModel("res/skysphere.mv1"); // �X�J�C�X�t�B�A
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

            // v��rad����]������
            v.x = cos(rad + camrad) * length;
            v.z = sin(rad + camrad) * length;

            // �ړ��ʂ����̂܂܃L�����̌����ɂ���
            if (VSize(v) > 0.f) {		// �ړ����Ă��Ȃ����͖������邽��
                _dir = v;
                _state = STATE::WALK;
                MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Walk"), -1, false);
            }
            else {
                _state = STATE::IDLE;
                MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Wait"), -1, false);
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
            MV1SetPosition(_handleSkySphere, _position);
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

            // ���C�g�ݒ�
            SetUseLighting(TRUE);

            return true;
        }
    }// namespace Player
}// namespace Gryo


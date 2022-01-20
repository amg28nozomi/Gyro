/*****************************************************************//**
 * @file   Player.cpp
 * @brief  オブジェクトベースのサブクラスの定義
 *
 * @author 土橋峡介
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
            // 初期化
            _handleModel = MV1LoadModel("res/sera.mv1"); // プレイヤー
            _handleSkySphere = MV1LoadModel("res/skysphere.mv1"); // スカイスフィア
            _attachIndex = -1;
            _totalTime = 0.0f;
            _playTime = 0.0f;
            _position = VGet(0.0f, 0.0f, 0.0f);
            _dir = VGet(0.0f, 0.0f, 0.0f);
            _state = STATE::IDLE;

            // カメラ
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
            float lx, ly, rx, ry;	// 左右アナログスティックの座標
            float analogMin = 0.3f;	// アナログ閾値
            // Logicoolパッドの場合
            lx = (float)di.X / 1000.f; ly = (float)di.Y / 1000.f;
            rx = (float)di.Z / 1000.f; ry = (float)di.Rz / 1000.f;

            // キャラ移動(カメラ設定に合わせて)

            // カメラの向いている角度を取得
            float sx = _cam._pos.x - _cam._target.x;
            float sz = _cam._pos.z - _cam._target.z;
            float camrad = atan2(sz, sx);

            // 移動方向を決める
            VECTOR v = { 0,0,0 };
            float mvSpeed = 6.f;

            // アナログ左スティック用
            float length = sqrt(lx * lx + ly * ly);
            float rad = atan2(lx, ly);
            if (length < analogMin) {
                // 入力が小さかったら動かなかったことにする
                length = 0.f;
            }
            else {
                length = mvSpeed;
            }

            // vをrad分回転させる
            v.x = cos(rad + camrad) * length;
            v.z = sin(rad + camrad) * length;

            // 移動量をそのままキャラの向きにする
            if (VSize(v) > 0.f) {		// 移動していない時は無視するため
                _dir = v;
                _state = STATE::WALK;
                MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Walk"), -1, false);
            }
            else {
                _state = STATE::IDLE;
                MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Wait"), -1, false);
            }

            { // カメラの操作を行う(右スティック)
                // Y軸回転
                float sx = _cam._pos.x - _cam._target.x;
                float sz = _cam._pos.z - _cam._target.z;
                float rad = atan2(sz, sx);
                float length = sqrt(sz * sz + sx * sx);
                if (rx > analogMin) { rad -= 0.05f; }
                if (rx < -analogMin) { rad += 0.05f; }
                _cam._pos.x = _cam._target.x + cos(rad) * length;
                _cam._pos.z = _cam._target.z + sin(rad) * length;
            }

            // ステータスが変わっていないか？
            if (oldState == _state) {
                // 再生時間を進める
                _playTime += 0.5f;
            }
            else {
                // アニメーションがアタッチされていたら、デタッチする
                if (_attachIndex != -1) {
                    MV1DetachAnim(_handleModel, _attachIndex);
                    _attachIndex = -1;
                }
                // ステータスに合わせてアニメーションのアタッチ
                switch (_state) {
                case STATE::IDLE:
                    _attachIndex = MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Wait"), -1, FALSE);
                    break;
                case STATE::WALK:
                    _attachIndex = MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Run"), -1, FALSE);
                    break;
                }
                // アタッチしたアニメーションの総再生時間を取得する
                _totalTime = MV1GetAttachAnimTotalTime(_handleModel, _attachIndex);
                // 再生時間を初期化
                _playTime = 0.0f;
            }

            // 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
            if (_playTime >= _totalTime) {
                _playTime = 0.0f;
            }

            // 再生時間をセットする
            MV1SetAttachAnimTime(_handleModel, _attachIndex, _playTime);
            // 位置
            MV1SetPosition(_handleModel, _position);
            MV1SetPosition(_handleSkySphere, _position);
            // 向きからY軸回転を算出
            VECTOR vRot = { 0,0,0 };
            vRot.y = atan2(_dir.x * -1, _dir.z * -1);		// モデルが標準でどちらを向いているかで式が変わる(これは-zを向いている場合)
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

            // プレイヤーの描画
            MV1DrawModel(_handleModel);

            // スカイスフィアの描画
            MV1DrawModel(_handleSkySphere);

            // ライト設定
            SetUseLighting(TRUE);

            return true;
        }
    }// namespace Player
}// namespace Gryo


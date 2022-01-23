/*****************************************************************//**
 * @file   Player.cpp
 * @brief  オブジェクトベースのサブクラスの定義
 *
 * @author 土橋峡介
 * @date   January 2022
 *********************************************************************/
#include "Player.h"
#include "ApplicationMain.h"
#include "UtilityDX.h"
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )

namespace {
  constexpr auto NoAnimation = -1; //!< アニメーションはアタッチされていない
  constexpr auto InputMin = 0.3f;  //!< 入力を受け付ける最低値
  constexpr auto InputMax = 32767.0f;

  constexpr auto MoveSpeed = 6.0f; //!< デフォルトの移動量
  constexpr auto MoveZero = 0.0f;
}

namespace Gyro {
  namespace Player {

    Player::Player(Application::ApplicationMain& app) : ObjectBase(app) {
      LoadResource(); // リソースの読み取り
      Init();
    }

    bool Player::Init() {
      SetCamera(); // カメラの設定
      SetState();  // パラメータの設定
      return true;
    }

    bool Player::Process() {
      // 名前空間の省略
      namespace App = AppFrame::Application;
      namespace AppMath = AppFrame::Math;
      // 入力状態の取得
      auto input = _app.GetOperation().GetXBoxState();
      auto [lX, lY] = input.GetStick(false); // 左スティック
      auto [rX, rY] = input.GetStick(true);  // 右スティック
      auto [leftTrigger, rightTrigger] = input.GetTrigger(); // トリガーボタン
      // 実際に使用する移動量(2次元ベクトル)
      auto stickLeft = AppMath::Vector4(lX / InputMax, lY / InputMax);
      auto stickRight = AppMath::Vector4(rX / InputMax, rY / InputMax);
      // カメラ向きの算出
      auto sX = _cam._pos.x - _cam._target.x;
      auto sZ = _cam._pos.z - _cam._target.z;
      auto camrad = atan2(sZ, sX);
      // 移動量はあるか
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

      auto oldPosition = _position; // 前フレーム座標
      // 移動量を算出する
      AppMath::Vector4 move;
      move = AppMath::Vector4(mx, 0.0f, my);
      CameraUpdate(stickRight);
      // 座標を更新する
      _position.Add(move);
      auto oldState = _playerState;
      // 状態の更新
      SetRotation(move);
      Animation(oldState);
      // 座標の設定
      VECTOR p(_position.GetX(), _position.GetY(), _position.GetZ());
      MV1SetPosition(_model, p);
      return true;
    }

    bool Player::Draw() const {
      // プレイヤーの描画
      MV1DrawModel(_model);
      // スカイスフィアの描画
      MV1DrawModel(_handleSkySphere);
      MV1DrawModel(_handleMap);
      // カメラ設定更新
      SetCameraPositionAndTarget_UpVecY(_cam._pos, _cam._target);
      SetCameraNearFar(_cam._clipNear, _cam._clipFar);
#ifdef _DEBUG
      DebugString(); // Debug情報の出力を行う
#endif
      return true;
    }

    void Player::Input() {
      
    }

    void Player::LoadResource() {
      // 各種リソースの読み取り処理
      _model = MV1LoadModel("res/SDChar.mv1"); // プレイヤー
      _handleSkySphere = MV1LoadModel("res/skysphere.mv1"); // スカイスフィア
      _handleMap = MV1LoadModel("res/Ground.mv1");
      _frameMapCollision = MV1SearchFrame(_handleMap, "ground_navmesh");
    }

    void Player::SetCamera() {
      // カメラの初期化
      _cam._pos = VGet(0, 90.0f, -300.0f);
      _cam._target = VGet(0, 80.0f, 0);
      _cam._clipNear = 2.0f;
      _cam._clipFar = 10000.0f;
    }

    void Player::SetState() {
      // 状態の設定
      _id = ObjectId::Player;
      _state = ObjectState::Active;
      // 座標・向きの設定
      namespace AppMath = AppFrame::Math;
      _position = AppMath::Vector4();
      _rotation = AppMath::Vector4();
      // アニメーションの初期化
      _animaIndex = NoAnimation;
      _animaTime = 0.0f;
      _totalTime = 0.0f;
    }

    float Player::Speed(const AppFrame::Math::Vector4 stick) const {
      // 移動量はあるか
      auto length = stick.Length2D();
      auto rad = atan2(stick.GetX(), stick.GetY());
      // 入力具合が少ない場合は移動量を0にする
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
      // 移動量がある場合は向きを変更する
      if (move.Length()) {
        _rotation = move;
        _playerState = PlayerState::Walk;
      }
      _playerState = PlayerState::Idle;
    }

    void Player::Animation(PlayerState old) {
      // アニメーション処理
      MV1SetAttachAnimTime(_model, _animaIndex, _animaTime);
      // 前フレームと異なる場合の処理
      if (_playerState == old) {
        _animaTime += 0.5f; // 再生時間を進める
        // アニメーションが終了したかの判定
        if (_totalTime <= _animaTime) {
          // アニメーションを切り替える
          AttachAnima(GetAnimaKey());
        }
        return;
      }
      // 現在のアニメーションを破棄
      MV1DetachAnim(_model, _animaIndex);
      _animaIndex = -1;
      // アニメーションを切り替える
      AttachAnima(GetAnimaKey());
    }

    int Player::AnimaIndex(std::string_view key) const {
      return MV1GetAnimIndex(_model, key.data());
    }

    bool Player::AttachAnima(std::string_view key) {
      // アニメーション番号の取得
      _animaIndex = AnimaIndex(key);
      // 取得に成功したかの判定
      if (_animaIndex == -1) {
#ifdef _DEBUG
        throw ("アニメーション番号の取得に失敗しました\n");
#endif
        return false;
      }
      // アニメーションをアタッチ
      MV1AttachAnim(_model, _animaIndex, -1, false);
      // 総再生時間を更新
      _totalTime = MV1GetAnimTotalTime(_model, _animaIndex);
      _animaTime = 0.0f; // 再生時間を0にする
      return true;
    }

    std::string_view Player::GetAnimaKey() const {
      // 状態に応じたキーを返す
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
      // 座標を出力する
      auto[x, y, z] = _position.GetVector3();
      DrawFormatString(0, 0, 255, "x:%f  y:%f, z:%f", x, y, z);
      auto [lx, ly] = _app.GetOperation().GetXBoxState().GetStick(false);
      DrawFormatString(0, 20, 255, "lx:%f  ly:%f", lx, ly);
    }
#endif

  } // namespace Player
    //namespace Player {

    //  Player::Player(Application::ApplicationMain& app) : ObjectBase(app) {
    //    // 各種
    //    _handleModel = MV1LoadModel("res/SDChar.mv1"); // プレイヤー
    //    _handleSkySphere = MV1LoadModel("res/skysphere.mv1"); // スカイスフィア
    //    _handleMap = MV1LoadModel("res/Ground.mv1");
    //    _frameMapCollision = MV1SearchFrame(_handleMap, "ground_navmesh");
    //  }


    //    Player::Player(Application::ApplicationMain& app) : Object::ObjectBase(app) {
    //      
    //        _handleModel = MV1LoadModel("res/SDChar.mv1"); // プレイヤー
    //        _handleSkySphere = MV1LoadModel("res/skysphere.mv1"); // スカイスフィア
    //        _handleMap = MV1LoadModel("res/Ground.mv1");
    //        _frameMapCollision = MV1SearchFrame(_handleMap, "ground_navmesh");
    //        _attachIndex = -1;
    //        _totalTime = 0.0f;
    //        _playTime = 0.0f;
    //        _position = VGet(0.0f, 0.0f, 0.0f);
    //        _dir = VGet(0.0f, 0.0f, 0.0f);
    //        _state = STATE::IDLE;
    //        // カメラ
    //        _cam._pos = VGet(0, 90.0f, -300.0f);
    //        _cam._target = VGet(0, 80.0f, 0);
    //        _cam._clipNear = 2.0f;
    //        _cam._clipFar = 10000.0f;
    //    }

    //    bool Player::Init() {
    //        // 初期化

    //        //// カメラ
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
    //        float lx, ly, rx, ry;	// 左右アナログスティックの座標
    //        float analogMin = 0.3f;	// アナログ閾値
    //        // Logicoolパッドの場合
    //        lx = (float)di.X / 1000.f; ly = (float)di.Y / 1000.f;
    //        rx = (float)di.Z / 1000.f; ry = (float)di.Rz / 1000.f;

    //        // キャラ移動(カメラ設定に合わせて)

    //        // カメラの向いている角度を取得
    //        float sx = _cam._pos.x - _cam._target.x;
    //        float sz = _cam._pos.z - _cam._target.z;
    //        float camrad = atan2(sz, sx);

    //        // 移動方向を決める
    //        VECTOR v = { 0,0,0 };
    //        float mvSpeed = 6.f;

    //        // アナログ左スティック用
    //        float length = sqrt(lx * lx + ly * ly);
    //        float rad = atan2(lx, ly);
    //        if (length < analogMin) {
    //            // 入力が小さかったら動かなかったことにする
    //            length = 0.f;
    //        }
    //        else {
    //            length = mvSpeed;
    //        }

    //        // 移動前の位置を保存
    //        VECTOR oldvPos = _position;
    //        VECTOR oldv = v;

    //        // コリジョン判定で引っかかった時に、escapeTbl[]順に角度を変えて回避を試みる
    //        float escapeTbl[] = {
    //            0, -10, 10, -20, 20, -30, 30, -40, 40, -50, 50, -60, 60, -70, 70, -80, 80,
    //        };
    //        for (int i = 0; i < sizeof(escapeTbl) / sizeof(escapeTbl[0]); i++) {
    //            // escapeTbl[i]の分だけ移動量v回転
    //            float escape_rad = DEG2RAD(escapeTbl[i]);
    //            v.x = cos(rad + camrad + escape_rad) * length;
    //            v.z = sin(rad + camrad + escape_rad) * length;

    //            // vの分移動
    //            _position = VAdd(_position, v);
    //        }

    //        // 移動量をそのままキャラの向きにする
    //        if (VSize(v) > 0.f) {		// 移動していない時は無視するため
    //            _dir = v;
    //            _state = STATE::WALK;
    //            MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "run"), -1, false);
    //        }
    //        else {
    //            _state = STATE::IDLE;
    //            MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "idle"), -1, false);
    //        }

    //        { // カメラの操作を行う(右スティック)
    //            // Y軸回転
    //            float sx = _cam._pos.x - _cam._target.x;
    //            float sz = _cam._pos.z - _cam._target.z;
    //            float rad = atan2(sz, sx);
    //            float length = sqrt(sz * sz + sx * sx);
    //            if (rx > analogMin) { rad -= 0.05f; }
    //            if (rx < -analogMin) { rad += 0.05f; }
    //            _cam._pos.x = _cam._target.x + cos(rad) * length;
    //            _cam._pos.z = _cam._target.z + sin(rad) * length;
    //        }

    //        // ステータスが変わっていないか？
    //        if (oldState == _state) {
    //            // 再生時間を進める
    //            _playTime += 0.5f;
    //        }
    //        else {
    //            // アニメーションがアタッチされていたら、デタッチする
    //            if (_attachIndex != -1) {
    //                MV1DetachAnim(_handleModel, _attachIndex);
    //                _attachIndex = -1;
    //            }
    //            // ステータスに合わせてアニメーションのアタッチ
    //            switch (_state) {
    //            case STATE::IDLE:
    //                _attachIndex = MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Wait"), -1, FALSE);
    //                break;
    //            case STATE::WALK:
    //                _attachIndex = MV1AttachAnim(_handleModel, MV1GetAnimIndex(_handleModel, "Run"), -1, FALSE);
    //                break;
    //            }
    //            // アタッチしたアニメーションの総再生時間を取得する
    //            _totalTime = MV1GetAttachAnimTotalTime(_handleModel, _attachIndex);
    //            // 再生時間を初期化
    //            _playTime = 0.0f;
    //        }

    //        // 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
    //        if (_playTime >= _totalTime) {
    //            _playTime = 0.0f;
    //        }

    //        // 再生時間をセットする
    //        MV1SetAttachAnimTime(_handleModel, _attachIndex, _playTime);
    //        // 位置
    //        MV1SetPosition(_handleModel, _position);
    //       // MV1SetPosition(_handleSkySphere, _position);
    //        // 向きからY軸回転を算出
    //        VECTOR vRot = { 0,0,0 };
    //        vRot.y = atan2(_dir.x * -1, _dir.z * -1);		// モデルが標準でどちらを向いているかで式が変わる(これは-zを向いている場合)
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

    //        // プレイヤーの描画
    //        MV1DrawModel(_handleModel);

    //        // スカイスフィアの描画
    //        MV1DrawModel(_handleSkySphere);
    //        MV1DrawModel(_handleMap);

    //        // カメラ設定更新
    //        SetCameraPositionAndTarget_UpVecY(_cam._pos, _cam._target);
    //        SetCameraNearFar(_cam._clipNear, _cam._clipFar);

    //        // ライト設定
    //        //SetUseLighting(TRUE);

    //        return true;
    //    }
    }// namespace Player
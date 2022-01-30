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
  constexpr auto InputMin = 2000.0f;  //!< 入力を受け付ける最低値
  constexpr auto InputMax = 32767.0f;

  constexpr auto MoveSpeed = 2.0f; //!< デフォルトの移動量
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
      _modelAnim.SetMainAttach(_model, 5, 1.0f, true);
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
        auto stickLeft = AppMath::Vector4(lX, lY);
        auto stickRight = AppMath::Vector4(rX, rY);
        Move(stickLeft);

        auto oldPosition = _position; // 前フレーム座標
        
        // カメラの更新
        _app.GetCamera().Process(stickRight, _position, _move);
        auto oldState = _playerState;
        // 状態の更新
        SetRotation(_move);
        //if (input.GetButton(XINPUT_BUTTON_Y, false)) {
        //    _playerState = PlayerState::Attack1;
        //}else {
        //    //_playerState = PlayerState::Idle;
        //}
        Animation(oldState);
        _modelAnim.Process();
        // 座標情報をVECTOR構造体に変換
        auto vPosition = UtilityDX::ToVECTOR(_position);
        auto world = WorldMatrix();
        // ワールド座標の設定
        MV1SetMatrix(_model, UtilityDX::ToMATRIX(world));
        // MV1SetPosition(_model, vPosition);
        auto rotationY = AppMath::Vector4(0.0f, _rotation.GetY(), 0.0f);
        // モデルの向きを設定する
        // MV1SetRotationXYZ(_model, UtilityDX::ToVECTOR(rotationY));
        // スカイスフィアの座標
        MV1SetPosition(_handleSkySphere, vPosition);
        // ステージの座標
        MV1SetPosition(_handleMap, VGet(0, -1500, 0));
        return true;
    }

    bool Player::Draw() const {
      // プレイヤーの描画
      auto scale = _scale;
      MV1SetScale(_model, UtilityDX::ToVECTOR(scale));
      MV1DrawModel(_model);
      // スカイスフィアの描画
      MV1DrawModel(_handleSkySphere);
      MV1DrawModel(_handleMap);
#ifdef _DEBUG
      DebugString(); // Debug情報の出力を行う
      // カメラ情報の描画
      _app.GetCamera().Draw(_position, _move);
#endif
        return true;
    }

    void Player::Input() {

    }

    void Player::Move(AppMath::Vector4 move) {
        _move.Fill(0.0f); // 移動量初期化
        // 移動量が0の場合は入力を受け付けない
        if (move.LengthSquared() == 0.0f) {
            return;
        }
        auto x = (move.GetX() / 30000) * MoveSpeed; // x軸の移動量
        auto z = (move.GetY() / 30000) * MoveSpeed; // y軸の移動量
        _move = AppMath::Vector4(x, 0.0f, z);
        _position.Add(_move); //!< 移動量に加算する
        
        auto angle = std::atan2(move.GetX() * -1, move.GetY() * -1);
        
        _rotation.SetY(angle);
        // カメラ向きの算出
        //auto  sX = _app.GetCamera().CamPosGetX() - _app.GetCamera().CamTarGetX();
        //auto  sZ = _app.GetCamera().CamPosGetZ() - _app.GetCamera().CamTarGetZ();
        //auto camrad = atan2(sZ, sX);
        //auto rad = atan2(move.GetX(), move.GetZ());
        //// 平行移動
        //auto x = cos(rad + camrad) * MoveSpeed;
        //auto z = sin(rad + camrad) * MoveSpeed;
        return;
    }

    void Player::LoadResource() {
        // 各種リソースの読み取り処理
        _model = MV1LoadModel("res/Player/Gyro multibag.mv1"); // プレイヤー
        _handleSkySphere = MV1LoadModel("res/SkySphere/skysphere.mv1"); // スカイスフィア
        _handleMap = MV1LoadModel("res/Stage/houseGEO_1.mv1");
    }

    void Player::SetCamera() {

    }


    void Player::SetState() {
      // 状態の設定
      _id = ObjectId::Player;
      _state = ObjectState::Active;
      // 座標・向きの設定
      namespace AppMath = AppFrame::Math;
      _position = AppMath::Vector4();
      _rotation = AppMath::Vector4();
      _scale = { 10.0f, 10.0f, 10.0f };
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
      
    }

    void Player::SetRotation(const AppFrame::Math::Vector4 move) {
      // 移動量がある場合は向きを変更する
      if (move.LengthSquared()) {
        using Utility = AppFrame::Math::Utility;
        // 入力情報のフィルタリングを行う
        //auto n = move.Normalize();
        //auto angle = std::atan2(n.GetX(), n.GetY()) - Utility::_pi / 2;
        //_rotation.SetY(angle);
        _playerState = PlayerState::Walk;
      }
      _playerState = PlayerState::Idle;
    }

    void Player::Animation(PlayerState old) {
        // 自機の状態に合わせてアニメーション変化
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

      //// アニメーション処理
      //MV1SetAttachAnimTime(_model, _animaIndex, _animaTime);
      //// 前フレームと異なる場合の処理
      //if (_playerState == old) {
      //  _animaTime += 0.5f; // 再生時間を進める
      //  // アニメーションが終了したかの判定
      //  if (_totalTime <= _animaTime) {
      //    // アニメーションを切り替える
      //    AttachAnima(GetAnimaKey());
      //  }
      //  return;
      //}
      //// 現在のアニメーションを破棄
      //MV1DetachAnim(_model, _animaIndex);
      //_animaIndex = -1;
      //// アニメーションを切り替える
      //AttachAnima(GetAnimaKey());
    }

    /*int Player::AnimaIndex(std::string_view key) const {
      return MV1GetAnimIndex(_model, key.data());
    }*/

//    bool Player::AttachAnima(std::string_view key) {
//      // アニメーション番号の取得
//      _animaIndex = AnimaIndex(key);
//      // 取得に成功したかの判定
//      if (_animaIndex == -1) {
//#ifdef _DEBUG
//        throw ("アニメーション番号の取得に失敗しました\n");
//#endif
//        return false;
//      }
//      // アニメーションをアタッチ
//      auto a = MV1AttachAnim(_model, _animaIndex, -1, false);
//      // 総再生時間を更新
//      _totalTime = MV1GetAttachAnimTotalTime(_model, a);
//      _animaTime = 0.0f; // 再生時間を0にする
//      return true;
//    }
//
//    std::string_view Player::GetAnimaKey() const {
//      // 状態に応じたキーを返す
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
      // 座標を出力する
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

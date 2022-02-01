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
#include "ObjectServer.h"
#include "Enemy/EnemyBase.h"
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )

namespace {
  constexpr auto NoAnimation = -1; //!< アニメーションはアタッチされていない
  constexpr auto InputMin = 2000.0f;  //!< 入力を受け付ける最低値
  constexpr auto InputMax = 32767.0f;

  constexpr auto MoveSpeed = 5.0f; //!< デフォルトの移動量
  constexpr auto MoveZero = 0.0f;
  // プレイヤーのアニメーション番号(まだ増える)
  constexpr auto Walk = 17;                     //!< 歩き
  constexpr auto Run = 1;                       //!< 走り
  constexpr auto Idle = 5;                      //!< アイドル
  constexpr auto JumpUp = 12;                   //!< ジャンプアップ
  constexpr auto JumpDown = 6;                  //!< ジャンプダウン(落下中)
  constexpr auto JumpLanding = 6;               //!< ジャンプランド(着地)
  constexpr auto GroundLightAttack1 = 13;       //!< 地上弱攻撃1
  constexpr auto GroundLightAttack2 = 14;       //!< 地上弱攻撃2
  constexpr auto GroundLightAttack3 = 15;       //!< 地上弱攻撃3
  constexpr auto GroundLightAttackEX = 16;      //!< 地上EX攻撃(弱の〆)
  constexpr auto AirLightAttack1 = 10;          //!< 空中弱攻撃1
  constexpr auto AirLightAttack2 = 11;          //!< 空中弱攻撃2
  // ジャンプフラグ
  constexpr auto JumpPowe = 3.0f;
  constexpr auto JumpMax = 300.0f;
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
        auto stickRight = AppMath::Vector4(rX, rY);
        // 移動量の算出
        _position = Move(AppMath::Vector4(lX, lY));
        // 前フレーム座標
        auto oldPosition = _position;   
        // カメラの更新
        _app.GetCamera().Process(stickRight, _position, _move);
        // 前フレームの状態を保持
        auto oldState = _playerState;
        // 状態の更新
        SetRotation(_move);
        Animation(oldState);  // アニメーションの設定
        _modelAnim.Process(); // アニメーションの再生
        WorldMatrix(); // ワールド座標の更新
        _sphere->Process(_move); // 移動量の加算
        // ワールド座標の設定
        MV1SetMatrix(_model, UtilityDX::ToMATRIX(_world));
        Hit();
        // モデルの向きを設定する
        // MV1SetRotationXYZ(_model, UtilityDX::ToVECTOR(rotationY));
        // スカイスフィアの座標
        auto skypos = AppMath::Utility::ToWorldMatrix(_position, AppMath::Vector4(0, 0, 0), AppMath::Vector4(1.0f, 1.0f, 1.0f));
        MV1SetMatrix(_handleSkySphere, UtilityDX::ToMATRIX(skypos));
        // MV1SetPosition(_handleSkySphere, UtilityDX::ToVECTOR(_position));
        auto stage = AppMath::Utility::ToWorldMatrix(AppMath::Vector4(0, -1500.0f, 0), AppMath::Vector4(0, 0, 0), AppMath::Vector4(1.0f, 1.0f, 1.0f));
        // ステージの座標
        MV1SetMatrix(_handleMap, UtilityDX::ToMATRIX(stage));
        return true;
    }

    bool Player::Draw() const {
      // プレイヤーの描画
      MV1DrawModel(_model);
      // スカイスフィアの描画
      MV1DrawModel(_handleSkySphere);
      MV1DrawModel(_handleMap);
#ifdef _DEBUG
      DebugDraw(); // デバッグ描画
#endif
        return true;
    }

    void Player::Input() {

    }

    AppMath::Vector4 Player::Move(AppMath::Vector4 move) {
        _move.Zero(); // 移動量初期化
        // 移動量がない場合は処理を行わない
        if (move.LengthSquared() == 0.0f) {
            return _position; // 前フレームの位置を返す
        }
        auto x = (move.GetX() / 30000) * MoveSpeed; // x軸の移動量
        auto z = (move.GetY() / 30000) * MoveSpeed; // y軸の移動量
        _move.Set(x, _gravityScale, z); // 移動量を設定
        // ラジアンを生成(y軸は反転させる)
        auto radian = std::atan2(move.GetX(), -move.GetY());
#ifndef _DEBUG
        _rotation.SetY(radian); // y軸の回転量をセットする
#else
        // デグリー値をセットする(デバッグ用)
        _rotation.SetY(AppMath::Utility::RadianToDegree(radian));
#endif
        return _position + _move;
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
      auto m = _position;
      m.AddY(100.0f);
      _sphere = std::make_unique<Object::CollisionSphere>(*this, m, 100.0f);
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
        _playerState = PlayerState::Walk;
      }
      else {
        _playerState = PlayerState::Idle;
      }
    }

    void Player::Animation(PlayerState old) {
        // 自機の状態に合わせてアニメーション状態を切り替える
        if (old != _playerState) {
            switch (_playerState) {
            case PlayerState::Idle:
                _modelAnim.SetBlendAttach(Idle, 10.0f, 1.0f, true);
                return;
            case PlayerState::Walk:
                _modelAnim.SetBlendAttach(Walk, 10.0f, 1.0f, true);
                return;
            case PlayerState::Run:
                _modelAnim.SetBlendAttach(Run, 10.0f, 1.0f, true);
                return;
            case PlayerState::Attack1:
                _modelAnim.SetBlendAttach(GroundLightAttack1, 10.0f, 1.0f, false);
                return;
            case PlayerState::Attack2:
                _modelAnim.SetBlendAttach(GroundLightAttack2, 10.0f, 1.0f, false);
                return;
            case PlayerState::Attack3:
                _modelAnim.SetBlendAttach(GroundLightAttack3, 10.0f, 1.0f, false);
                return;
            case PlayerState::Jump:
                _modelAnim.SetBlendAttach(JumpUp, 10.0f, 1.0f, false);
                return;
            default:
              return;
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

    bool Player::DebugDraw() const {
      // フラグが立っている場合のみ描画を行う
      if (!ObjectBase::DebugDraw()) {
        return false; // 出力を行わない
      }
      DebugString(); // 座標情報の出力
      _app.GetCamera().Draw(_position, _move); // カメラ情報の出力処理
      _sphere->Draw(); // 当たり判定の描画
      return true;
    }

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

    void Player::Hit() {
      auto objects = _app.GetObjectServer().GetObjects(); // オブジェクトのコピー
      // 衝突判定を行う6
      for (auto obj : objects) {
        // 敵の場合のみ処理を行う
        if (obj->GetId() != ObjectId::Enemy) continue;
        // 球と球の衝突判定
        _sphere->IntersectSphere(std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCollision());
      }
    }

    void Player::Jump() {
      // ジャンプのインターバル中か
      if (_jumpInterval != 0.0f) {
        return; // インターバルがない場合は処理を行わない
      }
      _jump = true; // ジャンプフラグを起動
      _jumpInterval = 300.0f; // インターバルを設定

    }
  } // namespace Player
}// namespace Gyro
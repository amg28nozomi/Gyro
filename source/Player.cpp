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
#include "CollisionCapsule.h"
#include "SpawnBase.h"
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )

namespace {
  constexpr auto NoAnimation = -1; //!< アニメーションはアタッチされていない
  constexpr auto InputMin = 2000.0f;  //!< 入力を受け付ける最低値
  constexpr auto InputMax = 32767.0f;

  constexpr auto MoveSpeed = 5.0f; //!< デフォルトの移動量
  constexpr auto MoveZero = 0.0f;
  // プレイヤーのアニメーションキー
  constexpr auto Idle = "GyroIdle";                     //!< アイドル
  constexpr auto Walk = "GyroWalk";                     //!< 歩き
  constexpr auto Run = "GyroDash";                      //!< 走り
  constexpr auto Step = "Gyro step";                    //!< ステップ
  constexpr auto JumpUp = "GyroJUp";                    //!< ジャンプアップ
  constexpr auto JumpDown = "GyroJDown";                //!< ジャンプダウン(落下中)
  constexpr auto JumpLanding = "GyroJLand";             //!< ジャンプランド(着地)
  constexpr auto GroundLightAttack1 = "GyroLaw1";       //!< 地上弱攻撃1
  constexpr auto GroundLightAttack2 = "GyroLaw2";       //!< 地上弱攻撃2
  constexpr auto GroundLightAttack3 = "GyroLaw3";       //!< 地上弱攻撃3
  constexpr auto GroundLightAttackEX = "GyroLawEx";     //!< 地上EX攻撃(弱の〆)
  constexpr auto GroundHeavyAttack1 = "GyroHigh1";      //!< 地上強攻撃1
  constexpr auto GroundHeavyAttack2 = "GyroHigh2";      //!< 地上強攻撃2
  constexpr auto GroundHeavyAttack3 = "GyroHigh3";      //!< 地上強攻撃3
  constexpr auto AirLightAttack1 = "GyroJLaw1";         //!< 空中弱攻撃1
  constexpr auto AirLightAttack2 = "GyroJLaw2";         //!< 空中弱攻撃2
  constexpr auto AirLightAttack3 = "GyroJLaw3";         //!< 空中弱攻撃3
  constexpr auto AirHeavyAttack1 = "GyroJHigh1";        //!< 空中強攻撃1
  constexpr auto AirHeavyAttack2 = "GyroJHigh2";        //!< 空中強攻撃2
  constexpr auto Damage1 = "Gyro damage1";              //!< 小ダメージ
  constexpr auto Damage2 = "Gyro damage2";              //!< 大ダメージ
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
      _modelAnim.SetMainAttach(_model, Idle, 1.0f, true);
      _gaugeHp.Init();
      _gaugeTrick.Init();
      return true;
    }

    bool Player::Process() {
      // 更新処理呼び出し
      ObjectBase::Process();
      // 名前空間の省略
      namespace App = AppFrame::Application;
      // 入力状態の取得
      auto input = _app.GetOperation().GetXBoxState();
      auto [lX, lY] = input.GetStick(false); // 左スティック
      auto [rX, rY] = input.GetStick(true);  // 右スティック
      auto [leftTrigger, rightTrigger] = input.GetTrigger(); // トリガーボタン
      // 前フレーム座標
      auto oldPosition = _position;
      // 座標更新
      _position = Move(AppMath::Vector4(lX, lY)); 
      // カメラの更新
      // _app.GetCamera().Process(AppMath::Vector4(rX, rY), _position, _move);
      // 前フレームの状態を保持
      auto oldState = _playerState;

      // ジャンプ処理の入口処理
      if (input.GetButton(XINPUT_BUTTON_A, false) && !_jump) {
        Jump(); // ジャンプ処理
      }


      // 状態の更新
      if (_playerState == PlayerState::Idle && _attackFlugY == false && input.GetButton(XINPUT_BUTTON_Y, false)) {
          _playerState = PlayerState::Attack1;
          _gaugeTrick.Add(-50.f);
          _attackFlugY = true;
          _cnt = 0;
      }else if (_playerState == PlayerState::Attack1 && _attackFlugY == true && input.GetButton(XINPUT_BUTTON_Y, false)) {
          _playerState = PlayerState::Attack2;
          _gaugeTrick.Add(-50.f);
          _cnt = 0;
      }else if (_playerState == PlayerState::Attack2 && _attackFlugY == true && input.GetButton(XINPUT_BUTTON_Y, false)) {
          _playerState = PlayerState::Attack3;
          _gaugeTrick.Add(-50.f);
          _cnt = 0;
      }
      if (_playerState == PlayerState::Idle && _attackFlugX == false && input.GetButton(XINPUT_BUTTON_X, false)) {
          _playerState = PlayerState::Attack1;
          _gaugeTrick.Add(-50.f);
          _attackFlugX = true;
          _cnt = 0;
      }else if (_playerState == PlayerState::Attack1 && _attackFlugX == true && input.GetButton(XINPUT_BUTTON_X, false)) {
          _playerState = PlayerState::Attack2;
          _gaugeTrick.Add(-50.f);
          _cnt = 0;
      }else if (_playerState == PlayerState::Attack2 && _attackFlugX == true && input.GetButton(XINPUT_BUTTON_X, false)) {
          _playerState = PlayerState::Attack3;
          _gaugeTrick.Add(-50.f);
          _cnt = 0;
      }
      if (_modelAnim.GetMainAnimEnd() == true && _attackFlugY == true) {
          _attackFlugY = false;
      }else if (_modelAnim.GetMainAnimEnd() == true && _attackFlugX == true) {
          _attackFlugX = false;
      }else if (_attackFlugX == false && _attackFlugY == false) {
          SetRotation(_move);
      }
      _cnt++;
      _gaugeHp.Process();
      _gaugeTrick.Process();
      Animation(oldState);      // アニメーションの設定
      _modelAnim.Process();     // アニメーションの再生
      WorldMatrix();            // ワールド座標の更新
      _sphere->Process(_move);  // 移動量の加算
      _capsule->Process(_move); // カプセルの更新
      Hit();
      // カメラの更新
      _app.GetCamera().Process(AppMath::Vector4(rX, rY), _position, _move);
      // ワールド座標の設定
      MV1SetMatrix(_model, UtilityDX::ToMATRIX(_world));
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
      // MV1DrawModel(_handleMap);
      _gaugeHp.Draw();
      _gaugeTrick.Draw();
#ifdef _DEBUG
      DebugDraw(); // デバッグ描画
#endif
      return true;
    }

    void Player::Set(Object::SpawnBase& spawn) {
      ObjectBase::Set(spawn);
      // 当たり判定の設定を行う
      auto m = _position.AddVectorY(100.0f);
      // 各種コリジョンの設定
      _sphere = std::make_unique<Object::CollisionSphere>(*this, m, 100.0f);
      _capsule = std::make_unique<Object::CollisionCapsule>(*this, _position, 150.0f, 20.0f);
    }

    void Player::Input() {

    }

    AppMath::Vector4 Player::Move(AppMath::Vector4 move) {
        _move.Zero(); // 移動量初期化
        // 移動量はあるか
        if (move.LengthSquared() == 0.0f) {
          // 現在座標に重力スケールを加算した値を返す
          return _position;
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
      auto [model, key1] = _app.GetModelServer().GetModel("player", 0);
      _model = model;     // モデルハンドルを登録
      auto [handle, key2] = _app.GetModelServer().GetModel("sky", 0);
      _handleSkySphere = handle; // スカイスフィア
      auto [stage , key3] = _app.GetModelServer().GetModel("stage", 0);
      _handleMap = stage; // ステージハンドル
    }

    void Player::SetCamera() {

    }


    void Player::SetState() {
      // 状態の設定
      _id = ObjectId::Player;
      _state = ObjectState::Active;
      _gravity = true; // 重力処理を行う
      // 座標・向きの設定
      // アニメーションの初期化
      _animaIndex = NoAnimation;
      _animaTime = 0.0f;
      _totalTime = 0.0f;
      // 地形の衝突判定を設定
      using Vector = AppFrame::Math::Vector4;
      // 平面の設定
      auto a = Vector(0.0f, 0.0f, 100.0f);
      auto b = Vector(-100.0f, 0.0f, -100.0f);
      auto c = Vector(100.0f, 0.0f, -100.0f);
      _plane = std::make_unique<AppFrame::Math::Plane>(a, b, c);
    }

    void Player::CameraUpdate(const AppFrame::Math::Vector4 stick) {
      
    }

    void Player::SetRotation(const AppFrame::Math::Vector4 move) {
      // 移動量がある場合は歩きモーションに遷移
      // 後程移動量に応じて歩き・ダッシュモーション切り替え
      if (move.LengthSquared()) {
        _playerState = PlayerState::Walk;
        _gaugeHp.Add(3.f);
      }
      else {
        _playerState = PlayerState::Idle;
      }
    }

    void Player::Animation(PlayerState old) {
        // 自機の状態に合わせてアニメーション変化
        if (old != _playerState) {
            switch (_playerState) {
            case PlayerState::Idle: // 待機
                _modelAnim.SetBlendAttach(Idle, 10.0f, 1.0f, true);
                break;
            case PlayerState::Walk: // 歩き
                _modelAnim.SetBlendAttach(Walk, 10.0f, 1.0f, true);
                break;
            case PlayerState::Run: // 走り
                _modelAnim.SetBlendAttach(Run, 10.0f, 1.0f, true);
                break;
            case PlayerState::Attack1: // 攻撃1
                if (_attackFlugY == true) {
                    _modelAnim.SetBlendAttach(GroundLightAttack1, 10.0f, 1.3f, false);
                }
                else if (_attackFlugX == true) {
                    _modelAnim.SetBlendAttach(GroundHeavyAttack1, 10.0f, 1.0f, false);
                }
                break;
            case PlayerState::Attack2: // 攻撃2
                if (_attackFlugY == true) {
                    _modelAnim.SetBlendAttach(GroundLightAttack2, 10.0f, 1.3f, false);
                }
                else if (_attackFlugX == true) {
                    _modelAnim.SetBlendAttach(GroundHeavyAttack2, 10.0f, 1.0f, false);
                }
                break;
            case PlayerState::Attack3: // 攻撃3
                if (_attackFlugY == true) {
                    _modelAnim.SetBlendAttach(GroundLightAttack3, 10.0f, 1.0f, false);
                }
                else if (_attackFlugX == true) {
                    _modelAnim.SetBlendAttach(GroundHeavyAttack3, 10.0f, 1.0f, false);
                }
                break;
            case PlayerState::Jump: // ジャンプ
                _modelAnim.SetBlendAttach(JumpUp, 10.0f, 1.0f, false);
                break;
            default:
                break;
            }
        }
    }

    void Player::GravityScale() {
      // ジャンプフラグが立っている場合
      if (_jump) {
        // 新しい重力加速度を設定する
        auto gScale = _gravityScale + (_jumpPower / 60.0f);
        // 加速度がジャンプ力を超過していないか？
        if (gScale <= _jumpPower) {
          // 重力加速度をセットする
          _gravityScale = gScale;
          return;
        }
        _jump = false;
      }
      using Gravity = AppFrame::Math::GravityBase;
      // 重力加速度を加算する
      _gravityScale += Gravity::Acceleration();
    }

    bool Player::IsStand() {
      // 新しい座標
      auto newPos = _position.AddVectorY(_gravityScale);
      // 新しいカプセル
      auto newCapsule = *_capsule;
      // カプセル座標をセット
      newCapsule.SetPosition(newPos);
      // 線分の取得
      auto [start, end] = newCapsule.LineSegment().GetVector();
      // 地形(床)と線分の衝突判定
      auto hit = MV1CollCheck_Line(_handleMap, 2, UtilityDX::ToVECTOR(end), UtilityDX::ToVECTOR(start));
      // 衝突フラグがない場合
      if (hit.HitFlag == 0) {
        // 新しい座標をセット
        _position = newPos;
        // コリジョン情報に更新をかける
        _capsule->SetPosition(_position);
        return false; // 床に立っていない
      }
      // 衝突座標を座標に代入
      _position = UtilityDX::ToVector(hit.HitPosition);
      // 新しい座標をコリジョンに反映
      _capsule->SetPosition(_position);
      // ジャンプフラグが立っている場合はオフにする
      _jump = false;
      _jumpPower = 0.0f;
      return true; // 床に立っている
    }

#ifdef _DEBUG
    bool Player::DebugDraw() const {
      // フラグが立っている場合のみ描画を行う
      if (!ObjectBase::DebugDraw()) {
        return false; // 出力を行わない
      }
      DebugString(); // 座標情報の出力
      _app.GetCamera().Draw(_position, _move); // カメラ情報の出力処理
      // _sphere->Draw(); // 当たり判定の描画
      _capsule->Draw(); // カプセルの描画
      return true;
    }

    void Player::DebugString() const {
      // 座標を出力する
      auto[x, y, z] = _position.GetVector3();
      DrawFormatString(0, 0, 255, "x:%f  y:%f, z:%f", x, y, z);
      auto [lx, ly] = _app.GetOperation().GetXBoxState().GetStick(false);
      DrawFormatString(0, 20, 255, "lx:%d  ly:%d", lx, ly);
      auto [rx, ry] = _app.GetOperation().GetXBoxState().GetStick(true);
      DrawFormatString(300, 20, 255, "lx:%d  ly:%d", rx, ry);
      // 回転情報の出力
      auto [rX, rY, rZ] = _rotation.GetVector3();
      DrawFormatString(0, 40, 255, "rotationX:%f  rotationY:%f rotationZ:%f", rX, rY, rZ);
      auto [moveX, moveY, moveZ] = _move.GetVector3();
      DrawFormatString(0, 60, 255, "moveX:%f  moveY:%f moveZ:%f", moveX, moveY, moveZ);
    }
#endif

    void Player::Hit() {
      auto objects = _app.GetObjectServer().GetObjects(); // オブジェクトのコピー
      // 衝突判定を行う
      for (auto obj : objects) {
        // 敵の場合のみ処理を行う
        if (obj->GetId() != ObjectId::Enemy) continue;
        // 球と球の衝突判定
        if (_sphere->IntersectSphere(std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCollision())) {
          // 衝突した場合は押し出し処理を行う
        }
        // カプセルとカプセルの衝突判定
        if (_capsule->IntersectCapsule(std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCapsule())) {
          // 衝突している場合は押し出し処理を行う
          auto y = _position.GetY(); // Y座標は変更を行わない
          // 二つの座標から押し出し力を算出する
          auto mPos = _capsule->GetPosition();
          auto ePos = std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCapsule().GetPosition();

          auto v = (mPos - ePos);   // 中心距離
          auto length2 = v.LengthSquared(); // 二点間の長さを算出
          auto radius2 = _capsule->GetRadius() + std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCapsule().GetRadius();

          auto l7 = radius2 - std::sqrtf(v.GetX() * v.GetX() + v.GetZ() * v.GetZ());
          v.Normalize();
          AppMath::Vector4 vv(v.GetX() * l7, 0.0f, v.GetZ());
          _position.Add(vv);
          // auto l = radius2 - v.Length();
          // _position = (AppMath::Vector4::Normalize(v) * l);
          // _position.SetY(y);
          _capsule->SetPosition(_position);
        }
      }
    }

    void Player::Jump() {
      // ジャンプのインターバル中か
      if (_jump) {
        return; // インターバルがない場合は処理を行わない
      }
      _gravityScale = 0.0f;
      _jump = true;           // ジャンプフラグ
      _jumpInterval = 300.0f; // インターバルを設定
      _jumpPower = 100.0f;    // ジャンプ力をセット
    }
  } // namespace Player
}// namespace Gyro
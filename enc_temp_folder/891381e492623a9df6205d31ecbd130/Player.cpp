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

namespace {
  constexpr auto NoAnimation = -1; //!< アニメーションはアタッチされていない
  constexpr auto InputMin = 2000.0f;  //!< 入力を受け付ける最低値
  constexpr auto InputMax = 32767.0f;

  constexpr auto MoveSpeed = 5.0f; //!< デフォルトの移動量
  constexpr auto MoveZero = 0.0f;

  constexpr auto WireSpeed = 10.0f; //!< ワイヤー移動速度
  // プレイヤーのアニメーションキー
  constexpr auto Idle = "GyroIdle";                            //!< アイドル
  constexpr auto Walk = "GyroWalk";                            //!< 歩き
  constexpr auto Run = "GyroDash";                             //!< 走り
  constexpr auto Step = "GyroStep";                            //!< ステップ
  constexpr auto JumpUp = "GyroJUp";                           //!< ジャンプアップ
  constexpr auto JumpDown = "GyroJDown";                       //!< ジャンプダウン(落下中)
  constexpr auto JumpLanding = "GyroJLand";                    //!< ジャンプランド(着地)
  constexpr auto GroundLightAttack1 = "GyroLaw1";              //!< 地上弱攻撃1
  constexpr auto GroundLightAttack2 = "GyroLaw2";              //!< 地上弱攻撃2
  constexpr auto GroundLightAttack3 = "GyroLaw3";              //!< 地上弱攻撃3
  constexpr auto GroundLightAttackEX = "GyroLawEx";            //!< 地上EX攻撃(弱の〆)
  constexpr auto GroundHeavyAttack1 = "Gyro High1";            //!< 地上強攻撃1
  constexpr auto GroundHeavyAttack2 = "GyroHigh2";             //!< 地上強攻撃2
  constexpr auto GroundHeavyAttack3 = "GyroHigh3";             //!< 地上強攻撃3
  constexpr auto AirLightAttack1 = "GyroJLaw1";                //!< 空中弱攻撃1
  constexpr auto AirLightAttack2 = "GyroJLaw2";                //!< 空中弱攻撃2
  constexpr auto AirLightAttack3 = "GyroJLaw3";                //!< 空中弱攻撃3
  constexpr auto AirHeavyAttack1 = "GyroJHigh1";               //!< 空中強攻撃1
  constexpr auto AirHeavyAttack2 = "GyroJHigh2";               //!< 空中強攻撃2
  constexpr auto ExciteTrickActive = "GyroExciteTrickActive";  //!< 必殺技
  constexpr auto ExciteTrick1 = "GyroExciteTrickDirect1";      //!< 必殺技
  constexpr auto ExciteTrick2 = "GyroExciteTrickDirect2";      //!< 必殺技
  constexpr auto Damage1 = "GyroDamage1";                      //!< 小ダメージ
  constexpr auto Damage2 = "GyroDamage2";                      //!< 大ダメージ
  // ジャンプフラグ
  constexpr auto JumpPowe = 3.0f;
  constexpr auto JumpMax = 300.0f;

  constexpr auto RunPower = 3.8f;
}

namespace Gyro {
  namespace Player {

    /**
     * @brief 自機の状態をキーとして状態を管理する連想配列クラス
     */
    const std::unordered_map<Player::PlayerState, std::pair<int, int>> chaneMap{
      {Player::PlayerState::Attack1, {60, 90}}, // 攻撃1
      {Player::PlayerState::Attack2, {60, 90}}, // 攻撃2
    };

    const std::unordered_map<Player::PlayerState, Player::PlayerState> stateMap{
      {Player::PlayerState::Attack1, Player::PlayerState::Attack2},
      {Player::PlayerState::Attack2, Player::PlayerState::Attack3},
      {Player::PlayerState::Attack3, Player::PlayerState::Idle}
    };

    Player::Player(Application::ApplicationMain& app) : ObjectBase(app) {
      LoadResource(); // リソースの読み取り
      Init();
    }

    bool Player::Init() {
      _animationKey = Idle; //!< アイドルモーションを設定
      SetCamera(); // カメラの設定
      SetState();  // パラメータの設定
      // ジャンプコンポーネントの設定
      _jump = std::make_unique<JumpComponent>();
      _jump->Set(300.0f, 120); // ジャンプの設定
      // ワイヤーコンポーネントの設定
      _wire = std::make_unique<WireComponent>(*this);
      // アタックコンポーネントの設定
      // 当たり判定は球をセットする
      _attack = std::make_unique<Object::AttackComponent>(*this, std::move(std::make_shared<Object::CollisionSphere>(*this, _position, 30.0f)));
      // インビジブルコンポーネントの設定
      _invincible = std::make_unique<Object::InvincibleComponent>(_app);
      // ステートコンポーネントの設定
      _stateComponent = std::make_unique<Object::StateComponent>();
      // アニメーションの設定
      _modelAnim.SetMainAttach(_model, Idle, 1.0f, true);
      // ゲージの設定
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
      //!< 移動量
      AppMath::Vector4 move;

      //// ワイヤーアクションの入口処理
      //if (input.GetButton(XINPUT_BUTTON_B, false)) {
      //  Wire(move);
      //}
      // 
      // ワイヤーフラグが立っていない場合のみ更新を行う
      if (!_wire->IsAction()) {
        // 状態の切り替え処理
        auto f = StateChanege(input);
        // 移動量の取得
        move = Move(lX, lY);
        // 
        if (!f) {
          SetRotation(move);
        }
      }
      // ワイヤーフラグが立っている場合は移動量を使用
      else {
        move = _wire->WireMove();
      }

      //// ワイヤーアクション実行中は他のアクションを実行しない
      //if (!_wire->IsAction()) {
      //  // ジャンプ処理の入口処理
      //  if (input.GetButton(XINPUT_BUTTON_A, false)) {
      //    Jump(); // ジャンプ処理
      //  }
        // 移動量の取得
        // move = Move(lX, lY);

        // 状態遷移処理


      //  // 状態の更新
      //  if (State(PlayerState::Idle) && _attackFlugY == false && input.GetButton(XINPUT_BUTTON_Y, false)) {
      //    _attack->Start();
      //    ChangeState(PlayerState::Attack1, GroundLightAttack1);
      //    _gaugeTrick.Add(-50.f);
      //    _attackFlugY = true;
      //    _cnt = 0;
      //  }
      //  else if (State(PlayerState::Attack1) && _attackFlugY == true && input.GetButton(XINPUT_BUTTON_Y, false)) {
      //    ChangeState(PlayerState::Attack2, GroundLightAttack2);
      //    _gaugeTrick.Add(-50.f);
      //    _cnt = 0;
      //  }
      //  else if (State(PlayerState::Attack2) && _attackFlugY == true && input.GetButton(XINPUT_BUTTON_Y, false)) {
      //    ChangeState(PlayerState::Attack3, GroundLightAttack3);
      //    _gaugeTrick.Add(-50.f);
      //    _cnt = 0;
      //  }
      //  // 強攻撃入口
      //  if (State(PlayerState::Idle) && _attackFlugX == false && input.GetButton(XINPUT_BUTTON_X, false)) {
      //    _attack->Start();
      //    ChangeState(PlayerState::Attack1, GroundHeavyAttack1);
      //    _gaugeTrick.Add(-50.f);
      //    _attackFlugX = true;
      //    _cnt = 0;
      //  }
      //  else if (State(PlayerState::Attack1) && _attackFlugX == true && input.GetButton(XINPUT_BUTTON_X, false)) {
      //    ChangeState(PlayerState::Attack2, GroundHeavyAttack2);
      //    _gaugeTrick.Add(-50.f);
      //    _cnt = 0;
      //  }
      //  else if (State(PlayerState::Attack2) && _attackFlugX == true && input.GetButton(XINPUT_BUTTON_X, false)) {
      //    ChangeState(PlayerState::Attack3, GroundHeavyAttack3);
      //    _gaugeTrick.Add(-50.f);
      //    _cnt = 0;
      //  }
      //  if (_modelAnim.GetMainAnimEnd() == true && _attackFlugY == true) {
      //    _attackFlugY = false;
      //  }
      //  else if (_modelAnim.GetMainAnimEnd() == true && _attackFlugX == true) {
      //    _attackFlugX = false;
      //  }
      //  else if (_attackFlugX == false && _attackFlugY == false) {
      //    SetRotation(move);
      //  }
      //}
      //else {
      //  move = _wire->WireMove();
      //}
      // 座標に現在座標を更新する
      _position.Add(move);
      _gaugeHp.Process();
      _gaugeTrick.Process();
      Animation(_oldState);     // アニメーションの設定
      _modelAnim.Process();    // アニメーションの再生
      WorldMatrix();           // ワールド座標の更新
      Attack();                //攻撃処理
      _sphere->Process(move);  // 移動量の加算
      _capsule->Process(move); // カプセルの更新
      Hit(); //衝突判定
      // カメラの更新
      _app.GetCamera().Process(AppMath::Vector4(rX, rY), _position, move);
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
      MV1DrawModel(_handleMap);
      _gaugeHp.Draw();
      _gaugeTrick.Draw();
#ifdef _DEBUG
      DebugDraw();     // デバッグ描画
      _attack->Draw(); // 攻撃判定の描画
#endif
      // 移動処理の後始末を行う
      _move->Finish();
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

    bool Player::StateChanege(const AppFrame::Application::XBoxState& input) {
      // 既に攻撃状態か
      if (IsAttackState()) {
        // 検索で使用するキーの取得
        auto key = NextKey();
        // 攻撃状態の場合は遷移フラグの判定を行う
        if (input.GetButton(key, false) && _stateComponent->Process(_modelAnim.GetMainPlayTime())) {
          _attack->Finish();
          // 条件を満たしたので更新を行う
          SetStateParam(stateMap.at(_playerState));
          return true;
        }
        // アニメーションが終了している場合
        if (_modelAnim.GetMainAnimEnd()) {
          _playerState = PlayerState::Idle;
          _attack->Finish();
          _stateComponent->Finish();
        }
        return true;
      }
      // 攻撃状態に遷移するかの判定？
      if (_playerState == PlayerState::Idle || _playerState == PlayerState::Run || _playerState == PlayerState::Walk) {
        // Yボタンの入力があった場合
        if (input.GetButton(XINPUT_BUTTON_Y, false)) {
          // 強攻撃に遷移する
          SetStateParam(PlayerState::Attack1);
          _attack->Start();
          _stateComponent->Start();
          _attackFlag = true;
          return true; // 遷移する
        }
        // Xボタンの入力があった場合
        if (input.GetButton(XINPUT_BUTTON_X, false)) {
          // 弱攻撃に遷移する
          SetStateParam(PlayerState::Attack1);
          _stateComponent->Start();
          _attack->Start();
          _attackFlag = false;
          return true; // 遷移する
        }
        // Aボタンの入力があった場合はジャンプ状態に遷移
        if (input.GetButton(XINPUT_BUTTON_A, false)) {
          Jump(); // ジャンプ処理
          return true; // 遷移する
        }
      }
      return false;
    }

    int Player::NextKey() const {
      // 攻撃フラグに応じて返すキーを切り替える
      auto key = (_attackFlag) ? XINPUT_BUTTON_Y : XINPUT_BUTTON_X;
      // 現在の状況に応じたキーを返す
      switch (_playerState) {
      case PlayerState::Attack1:
      case PlayerState::Attack2:
        return key; // 対応するキーを返す
      case PlayerState::Attack3:
        return -1;  // 処理は派生しない
      default:
        return -2;  // 攻撃状態ではない
      }
    }

    void Player::Input() {

    }

    AppMath::Vector4 Player::Move(const float leftX, const float leftY) {
      // 移動ベクトル
      auto move = AppMath::Vector4();
      // 移動量の生成
      if (_move->Move(leftX, leftY)) {
        move = _move->MoveVector();
        // ラジアンを生成(y軸は反転させる)
        auto radian = std::atan2(move.GetX(), -move.GetZ());
#ifndef _DEBUG
        _rotation.SetY(radian); // y軸の回転量をセットする
#else
        // デグリー値をセットする(デバッグ用)
        _rotation.SetY(AppMath::Utility::RadianToDegree(radian));
#endif
      }
      return move; // 移動量を返す
    }

    void Player::LoadResource() {
      // 各種リソースの読み取り処理
      auto [model, key1] = _app.GetModelServer().GetModel(_modelKey, 0);
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
      _move = std::make_unique<Object::MoveComponent>(*this);
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

      if (_playerState == PlayerState::Idle || _playerState == PlayerState::Run || _playerState == PlayerState::Walk) {
        // 移動量のいずれかが基準を超えていたらRunに遷移
        if (IsRun(move)) {
          // 走り状態に遷移
          _playerState = PlayerState::Run;
          return;
        }
        // 移動量がある場合は歩きモーションに遷移
        // 後程移動量に応じて歩き・ダッシュモーション切り替え
        if (move.LengthSquared()) {
          _playerState = PlayerState::Walk;
          return;
        }
        // 待機状態に遷移する
        _playerState = PlayerState::Idle;
      }
    }

    bool Player::IsRun(const AppMath::Vector4& move) {
      // 移動量の取得
      auto [x, z] = move.GetVector2();
      if (RunPower <= x || x <= -RunPower || RunPower <= z || z <= -RunPower) {
        return true;
      }
      return false;
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
            // アニメーションキーの設定
            _animationKey = (_attackFlag) ? GroundHeavyAttack1 : GroundLightAttack1;
              if (_attackFlag) {
                _modelAnim.SetBlendAttach(_animationKey, 10.0f, 1.0f, false);
                break;
              }
              _modelAnim.SetBlendAttach(_animationKey, 10.0f, 1.3f, false);
               break;
            case PlayerState::Attack2: // 攻撃2
              // アニメーションキーの設定
              _animationKey = (_attackFlag) ? GroundHeavyAttack2 : GroundLightAttack2;
              if (_attackFlag) {
                _modelAnim.SetBlendAttach(_animationKey, 10.0f, 1.0f, false);
                break;
              }
              _modelAnim.SetBlendAttach(_animationKey, 10.0f, 1.3f, false);
              break;
            case PlayerState::Attack3: // 攻撃3
              _animationKey = (_attackFlag) ? GroundHeavyAttack3 : GroundLightAttack3;
              _modelAnim.SetBlendAttach(_animationKey, 10.0f, 1.0f, false);
                //if (_attackFlugY == true) {
                //    _modelAnim.SetBlendAttach(_animationKey, 10.0f, 1.0f, false);
                //}
                //else if (_attackFlugX == true) {
                //    _modelAnim.SetBlendAttach(_animationKey, 10.0f, 1.0f, false);
                //}
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
      if (_jump->IsJump()) {
        // 新しい重力加速度を設定する
        _gravityScale = _jump->JumpPower();
        return;
      }
      using Gravity = AppFrame::Math::GravityBase;
      // 重力加速度を加算する
      _gravityScale += (Gravity::Acceleration() / 60.0f);
    }

    bool Player::IsStand() {
      // 前フレーム座標
      _oldState = _playerState;
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
      // ジャンプの後始末を行う
      if (_jump->IsJump()) {
        _jump->Finish();
      }
      if (_playerState == PlayerState::Jump) {
        _playerState = PlayerState::Idle;
      }
      return true; // 床に立っている
    }

#ifdef _DEBUG
    bool Player::DebugDraw() const {
      // フラグが立っている場合のみ描画を行う
      if (!ObjectBase::DebugDraw()) {
        return false; // 出力を行わない
      }
      DebugString(); // 座標情報の出力
      _app.GetCamera().Draw(_position, _move->MoveVector()); // カメラ情報の出力処理
      // _sphere->Draw(); // 当たり判定の描画
      _capsule->Draw();   // カプセルの描画
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
      auto [moveX, moveY, moveZ] = _move->MoveVector().GetVector3();
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
          _capsule->SetPosition(_position);
          // 衝突した場合はワイヤーアクションを中断する
          if (_wire->IsAction()) {
            _wire->Finish();
            _playerState = PlayerState::Idle;
          }
        }
      }
    }

    void Player::Extrude() {
      auto newPosition = _position + _move->MoveVector();
      // コリジョンと壁の押し出し処理を行う
      auto newCapsule = *_capsule;
      newCapsule.SetPosition(newPosition);
      auto [start, end] = newCapsule.LineSegment().GetVector();
      auto radius = newCapsule.GetRadius();
      // ステージとの衝突判定
      auto hit = MV1CollCheck_Capsule(_handleMap, 1, UtilityDX::ToVECTOR(start), UtilityDX::ToVECTOR(end), radius);
      // 接触箇所がない場合
      if (!hit.HitNum) {
        // 衝突用情報の後始末を行う
        MV1CollResultPolyDimTerminate(hit);
        return;
      }
      MV1CollResultPolyDimTerminate(hit);
    }

    void Player::Jump() {
      // ジャンプフラグが立っている場合は処理を行わない
      if (_jump->IsJump()) {
        return; // インターバルがない場合は処理を行わない
      }
      _jump->Start(); // ジャンプ開始
      _gravityScale = 0.0f;
      _playerState = PlayerState::Jump;
    }

    void Player::Wire(AppMath::Vector4& move) {
      // ワイヤーアクションが実行されていないか
      if (!_wire->IsAction()) {
        // 座標をセットして処理を行う
        auto o = _app.GetObjectServer().GetObjects();
        _wire->SetTarget(o.back()->GetPosition(), WireSpeed);
        _wire->Start();
        // ジャンプフラグが立っている場合は
        if (_jump->IsJump()) {
          _jump->Finish();
          _gravityScale = 0.0f;
        }
        return;
      }
      // 移動量がセットされている場合は処理を中断する
      _wire->Finish();
    }

    void Player::Attack() {
      using AttackState = Object::AttackComponent::AttackState;
      // 攻撃状態でない場合は処理を行わない
      if (_attack->GetState() == AttackState::NonActive) {
        return;
      }     
      // アニメーションから指定したボーンのローカル座標を取得
      // 全ての成分が-1のベクトルが返ってくる
      auto attachIndex = _modelAnim.GetMainAttachIndex();
      auto pos = MV1GetFramePosition(_model, 15);
      // ローカル座標を攻撃座標にセットする
      _attack->Process(UtilityDX::ToVector(pos));
    }

    void Player::ChangeState(const PlayerState& state, std::string_view animName) {
      // 各種データの切り替え
      _playerState = state;
      _animationKey = animName;
    }

    bool Player::IsAttackState() const {
      // 現在の状態は攻撃状態か？
      switch (_playerState) {
      case PlayerState::Attack1:
      case PlayerState::Attack2:
      case PlayerState::Attack3:
        return true;  // 攻撃状態
      default:
        return false; // 攻撃状態ではない
      }
    }

    bool Player::SetStateParam(PlayerState pState) {
      // 状態の切り替え
      _playerState = pState;
      // データが登録されていない場合は設定を行わない
      if (!chaneMap.contains(_playerState)) {
        _stateComponent->Finish();
        return false;
      }
      // 自機の状態を取得
      auto [start, end] = chaneMap.at(_playerState);
      // 切り替え状態を設定する
      _stateComponent->Set(_modelAnim.GetMainPlayTime(), start, end);
      _stateComponent->Start();
      return true; // 切り替えを完了
    }

  } // namespace Player
}// namespace Gyro
/*****************************************************************//**
 * @file   Player.cpp
 * @brief  オブジェクトベースのサブクラスの定義
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "Player.h"
#include "ApplicationMain.h"
#include "Box.h"
#include "DashComponent.h"
#include "UtilityDX.h"
#include "ObjectServer.h"
#include "EnemyBase.h"
#include "CollisionCapsule.h"
#include "SpawnBase.h"
#include "StageComponent.h"
#include "ModelAnimData.h"
#include "EnemyBase.h"

namespace {
  constexpr auto NoAnimation = -1;    // アニメーションはアタッチされていない
  constexpr auto InputMin = 2000.0f;  // 入力を受け付ける最低値
  constexpr auto InputMax = 32767.0f; // 入力上限
  constexpr auto MoveSpeed = 5.0f;    // デフォルトの移動量
  constexpr auto MoveZero = 0.0f;     // 移動量0
  constexpr auto RunValue = 36.0f;    // 走り状態
  constexpr auto WireSpeed = 10.0f;   // ワイヤー移動速度
  // プレイヤーのアニメーションキー
  constexpr auto Idle = "GyroIdle";                            // アイドル
  constexpr auto Walk = "GyroWalk";                            // 歩き
  constexpr auto Run = "GyroDash";                             // 走り
  constexpr auto Step = "GyroStep";                            // ステップ
  constexpr auto JumpUp = "GyroJUp";                           // ジャンプアップ
  constexpr auto JumpDown = "GyroJDown";                       // ジャンプダウン(落下中)
  constexpr auto JumpLanding = "GyroJLand";                    // ジャンプランド(着地)
  constexpr auto GroundLightAttack1 = "GyroLaw1";              // 地上弱攻撃1
  constexpr auto GroundLightAttack2 = "GyroLaw2";              // 地上弱攻撃2
  constexpr auto GroundLightAttack3 = "GyroLaw3";              // 地上弱攻撃3
  constexpr auto GroundLightAttackEX = "GyroLawEx";            // 地上EX攻撃(弱の〆)
  constexpr auto GroundHeavyAttack1 = "Gyrohigh1";             // 地上強攻撃1
  constexpr auto GroundHeavyAttack2 = "Gyrohigh2";             // 地上強攻撃2
  constexpr auto GroundHeavyAttack3 = "Gyrohigh3";             // 地上強攻撃3
  constexpr auto AirLightAttack1 = "GyroJLaw1";                // 空中弱攻撃1
  constexpr auto AirLightAttack2 = "GyroJLaw2";                // 空中弱攻撃2
  constexpr auto AirLightAttack3 = "GyroJLaw3";                // 空中弱攻撃3
  constexpr auto AirHeavyAttack1 = "GyroJHigh1";               // 空中強攻撃1
  constexpr auto AirHeavyAttack2 = "GyroJHigh2";               // 空中強攻撃2
  constexpr auto ExciteTrickActive = "GyroExciteTrickActive";  // 必殺技
  constexpr auto ExciteTrick1 = "GyroExciteTrickDirect1";      // 必殺技
  constexpr auto ExciteTrick2 = "GyroExciteTrickDirect2";      // 必殺技
  constexpr auto Damage1 = "GyroDamage1";                      // 小ダメージ
  constexpr auto Damage2 = "GyroDamage2";                      // 大ダメージ
  // プレイヤーのHP
  constexpr int GyroHP = 1000;
  // トリックゲージの設定
  constexpr auto TrickMax = 30000;
  // ジャンプフラグ
  constexpr auto JumpPowe = 3.0f;
  constexpr auto JumpMax = 300.0f;
  constexpr auto RunPower = 3.8f;
  constexpr auto LightFlag = true;  // 弱攻撃フラグ
  constexpr auto HeavyFlag = false; // 強攻撃フラグ
  // 状態を表すキー
  constexpr auto StateNumberIdle = 0;          // 待機
  constexpr auto StateNumberWalk = 1;          // 歩き
  constexpr auto StateNumberRun = 2;           // 走り
  constexpr auto StateNumberJump = 3;          // ジャンプ
  constexpr auto StateNumberLight1 = 4;        // 弱攻撃1
  constexpr auto StateNumberLight2 = 6;        // 弱攻撃2
  constexpr auto StateNumberLight3 = 8;        // 弱攻撃3
  constexpr auto StateNumberHeavy1 = 5;        // 強攻撃1
  constexpr auto StateNumberHeavy2 = 7;        // 強攻撃2
  constexpr auto StateNumberHeavy3 = 9;        // 強攻撃3
  constexpr auto StateNumberAirLight1 = 10;    // 空中弱攻撃1
  constexpr auto StateNumberAirLight2 = 12;    // 空中弱攻撃2
  constexpr auto StateNumberAirLight3 = 14;    // 空中弱攻撃3
  constexpr auto StateNumberAirHeavy1 = 11;    // 空中強攻撃1
  constexpr auto StateNumberAirHeavy2 = 13;    // 空中強攻撃2
  constexpr auto StateNumberExciteActive = 15; // 必殺技構え
  constexpr auto StateNumberExciteTrick1 = 16; // 必殺技中
  constexpr auto StateNumberExciteTrick2 = 17; // 必殺技後
  constexpr auto StateNumberDash = 18;         // ダッシュ
  constexpr auto StateNumberFall = 19;         // 降下
  constexpr auto StateNumberDamage = 20;       // ダメージ

  constexpr auto AttackInterval = 150.0f; // 攻撃用インターバル
  constexpr auto DashTime = 600.0f;       // ダッシュ時間
  constexpr auto DashPower = 300.0f;      // ダッシュの移動量
}

namespace Gyro {
  namespace Player {
    /**
     * @brief 自機の状態をキーとして状態を管理する連想配列
     */
    const std::unordered_map<Player::PlayerState, std::pair<int, int>> chaneMap{
      {Player::PlayerState::Attack1, {60, 90}}, // 攻撃1
      {Player::PlayerState::Attack2, {60, 90}}, // 攻撃2
      {Player::PlayerState::JumpAttack1, {0, 100}}, // 空中攻撃1
      {Player::PlayerState::JumpAttack2, {0, 100}}, // 空中攻撃2
    };
    /**
     * @brief 自機の現在の状態をキーとして次に遷移する状態を管理する連想配列
     */
    const std::unordered_map<Player::PlayerState, Player::PlayerState> stateMap{
      {Player::PlayerState::Attack1, Player::PlayerState::Attack2},
      {Player::PlayerState::Attack2, Player::PlayerState::Attack3},
      {Player::PlayerState::Attack3, Player::PlayerState::Idle},
      {Player::PlayerState::Dash, Player::PlayerState::Idle},
      {Player::PlayerState::JumpAttack1, Player::PlayerState::JumpAttack2},
      {Player::PlayerState::JumpAttack2, Player::PlayerState::JumpAttack3},
      {Player::PlayerState::JumpAttack3, Player::PlayerState::Idle},
      {Player::PlayerState::Idle, Player::PlayerState::ExciteTrick},
    };
    /**
     * @brief プレイヤーのボイスを管理する連想配列
     */
    const std::unordered_map<int, std::string> voiceMap{
      // 待機
      {StateNumberIdle, "idle"},
      // ジャンプ
      {StateNumberJump, "jump"},
      // 弱攻撃
      {StateNumberLight1, "low1"},
      {StateNumberLight2, "low2"},
      {StateNumberLight3, "low3"},
      // 強攻撃
      {StateNumberHeavy1, "high1"},
      {StateNumberHeavy2, "high2"},
      {StateNumberHeavy3, "high3"},
      // 空中弱攻撃
      {StateNumberAirLight1, "jlow1"},
      {StateNumberAirLight2, "jlow2"},
      {StateNumberAirLight3, "jlow3"},
      // 空中強攻撃
      {StateNumberAirHeavy1, "jhigh1"},
      {StateNumberAirHeavy2, "jhigh2"},
      // 必殺技攻撃
      {StateNumberExciteActive, "excite1"},
      {StateNumberExciteTrick1, "excite2"},
      {StateNumberExciteTrick2, "excite3"},
    };
    /**
     * @brief 攻撃判定が出てくるまでにかかるフレーム数を管理する連想配列
     */
    const std::unordered_map<int, int> occurrenceMap{
      // 弱攻撃
      {StateNumberLight1, 5},
      {StateNumberLight2, 6},
      {StateNumberLight3, 15},
      // 強攻撃
      {StateNumberHeavy1, 8},
      {StateNumberHeavy2, 10},
      {StateNumberHeavy3, 8},
      // 空中弱攻撃
      {StateNumberAirLight1, 4},
      {StateNumberAirLight2, 8},
      {StateNumberAirLight3, 26},
      // 空中強攻撃
      {StateNumberAirHeavy1, 10},
      {StateNumberAirHeavy2, 30},
      // 必殺技攻撃
      {StateNumberExciteTrick1, 10},
    };
    /**
     * @brief コリジョンに使用するフレーム番号を管理する連想配列
     */
    const std::unordered_map<int, std::vector<int>> attackMap{
      // 弱攻撃
      {StateNumberLight1, {50, 75}},
      {StateNumberLight2, {15, 17}},
      {StateNumberLight3, {15, 17, 20, 22}},
      // 強攻撃
      {StateNumberHeavy1 ,{15}},
      {StateNumberHeavy2 ,{15, 17, 20, 22}},
      {StateNumberHeavy3 ,{15, 17, 20, 22, 50, 75}},
      // 空中弱攻撃
      {StateNumberAirLight1 ,{15, 17, 20, 22}},
      {StateNumberAirLight2 ,{15, 17, 20, 22}},
      {StateNumberAirLight3 ,{15, 17, 20, 22}},
      // 空中強攻撃
      {StateNumberAirHeavy1 ,{15, 17, 20, 22}},
      {StateNumberAirHeavy2 ,{15, 17, 20, 22}},
      // 必殺技攻撃
      {StateNumberExciteTrick1 ,{15, 17, 20, 22}},
    };
    /**
     * @brief 状態番号をキーとして、モーションブレンド情報を保持する連想配列
     */
    const std::unordered_map<int, ModelAnim::ModelAnimData> animMap {
      // 待機情報
      {StateNumberIdle, {Idle, 10.0f, 1.0f, true}},
      // 歩き
      {StateNumberWalk, {Walk, 10.0f, 1.0f, true}},
      // 走り
      {StateNumberRun, {Run, 10.0f, 1.0f, true, EffectNum::PlayerDash}},
      // ジャンプ
      {StateNumberJump, {JumpUp, 10.0f, 1.0f, false, EffectNum::PlayerJump}},
      // 弱攻撃1
      {StateNumberLight1, {GroundLightAttack1, 10.0f, 1.3f, false, EffectNum::PlayerWeakAttack1}},
      // 弱攻撃2
      {StateNumberLight2, {GroundLightAttack2, 10.0f, 1.3f, false, EffectNum::PlayerWeakAttack2}},
      // 弱攻撃3
      {StateNumberLight3, {GroundLightAttack3, 10.0f, 1.0f, false, EffectNum::PlayerWeakAttack3}},
      // 強攻撃1
      {StateNumberHeavy1 ,{GroundHeavyAttack1, 10.0f, 1.0f, false, EffectNum::PlayerHeavyAttack1}},
      // 強攻撃2
      {StateNumberHeavy2 ,{GroundHeavyAttack2, 10.0f, 1.0f, false, EffectNum::PlayerHeavyAttack2}},
      // 強攻撃3
      {StateNumberHeavy3 ,{GroundHeavyAttack3, 10.0f, 1.0f, false, EffectNum::PlayerHeavyAttack3}},
      // 空中弱攻撃1
      {StateNumberAirLight1 ,{AirLightAttack1, 10.0f, 1.0f, false, EffectNum::PlayerAirWeakAttack1}},
      // 空中弱攻撃2
      {StateNumberAirLight2 ,{AirLightAttack2, 10.0f, 1.0f, false, EffectNum::PlayerAirWeakAttack2}},
      // 空中弱攻撃3
      {StateNumberAirLight3 ,{AirLightAttack3, 10.0f, 1.0f, false, EffectNum::PlayerAirWeakAttack3}},
      // 空中強攻撃1
      {StateNumberAirHeavy1 ,{AirHeavyAttack1, 10.0f, 1.0f, false, EffectNum::PlayerAirHeavyAttack1}},
      // 空中強攻撃2
      {StateNumberAirHeavy2 ,{AirHeavyAttack2, 10.0f, 1.0f, false, EffectNum::PlayerAirHeavyAttack2}},
      // 必殺技構え
      {StateNumberExciteActive ,{ExciteTrickActive, 10.0f, 1.0f, false, EffectNum::PlayerUltActivate}},
      // 必殺技中
      {StateNumberExciteTrick1 ,{ExciteTrick1, 10.0f, 1.0f, false, EffectNum::PlayerUltSlash}},
      // 必殺技後
      {StateNumberExciteTrick2 ,{ExciteTrick2, 10.0f, 1.0f, false}},
      // ダッシュ
      {StateNumberDash, {Step, 10.0f, 1.0f, false, EffectNum::PlayerAvoidance}},
      // 降下モーション
      {StateNumberFall, {JumpDown, 10.0f, 1.0f, false}},
    };

    Player::Player(Application::ApplicationMain& app) : ObjectBase(app), _gaugeHp(app), _gaugeTrick(app) {
      LoadResource(); // リソースの読み取り
      Init();
    }

    bool Player::Init() {
      _animationKey = Idle; //!< アイドルモーションを設定
      SetState();  // パラメータの設定
      // ジャンプコンポーネントの設定
      _jump = std::make_unique<JumpComponent>();
      _jump->Set(300.0f, 75); // ジャンプの設定
      // ノックバックコンポーネントの設定
      _knockBack = std::make_unique<Object::KnockBackComponent>(*this, _app);
      // ワイヤーコンポーネントの設定
      _wire = std::make_unique<WireComponent>(*this);
      // アタックコンポーネントの設定
      // 当たり判定は球をセットする
      _attack = std::make_unique<Object::AttackComponent>(*this, std::move(std::make_shared<Object::CollisionSphere>(*this, _position, 30.0f)));
      // インビジブルコンポーネントの設定
      _invincible = std::make_unique<Object::InvincibleComponent>(_app);
      // ステートコンポーネントの設定
      _stateComponent = std::make_unique<Object::StateComponent>();
      // ダッシュコンポーネントの設定
      _dash = std::make_unique<Object::DashComponent>(*this);
      // アニメーションの設定
      _modelAnim.SetMainAttach(_model, Idle, 1.0f, true);
      return true;
    }

    bool Player::Process() {
      // 基底クラスの更新処理呼び出し
      ObjectBase::Process();
      // 重力スケールに応じたジャンプ・降下モーションの遷移
      if (_gravity) {
        // 重力スケールがマイナスの場合は落下状態に遷移する
        if (_playerState == PlayerState::Jump && _gravityScale < 0.0f) {
          _playerState = PlayerState::Fall;
        }
      }
      // グラビティフラグがオフの場合はここで旧状態を更新
      else { _oldState = _playerState; }
      // 名前空間の省略
      namespace App = AppFrame::Application;
      // 入力状態の取得
      auto input = _app.GetOperation().GetXBoxState();
      // アナログスティックの入力状態を取得
      auto [leftX, leftY] = input.GetStick(false);
      auto [rightX, rightY] = input.GetStick(true);
      // 前フレーム座標の保持
      _move->OldPosition();
      // 移動量
      AppMath::Vector4 move;
      //!< スティック情報の更新
      InputValue(input);
      // ワイヤーフラグが立っていない場合のみ更新を行う
      if (!_wire->IsAction()) {
        // 状態の切り替え処理
        auto f = StateChanege(input);
        // 移動量の取得
        move = Move(static_cast<float>(leftX), static_cast<float>(leftY));
        // ダッシュ処理
        Dash(move);
        // 状態の変化がない場合
        if (!f) {
          SetRotation(move);
        }
      }
      // ワイヤーフラグが立っている場合は移動量を使用
      else {
        move = _wire->WireMove();
      }
      // 座標に現在座標を更新する
      _gaugeHp.Process();      // HPゲージの更新
      _gaugeTrick.Process();   // トリックゲージの更新
      _gaugeTrick.SetValue(_trickValue); // トリックゲージに値を入れる
      if (_drawFlag != false) {
        Animation(_oldState);    // アニメーションの設定
        _modelAnim.Process();    // アニメーションの再生
      }
      Attack();                // 攻撃処理
      _sphere->Process(move);  // 移動量の加算

      _capsule->Process(move); // カプセルの更新
      //衝突判定
      Hit();
      // ノックバック処理
      KnockBack(move);
      // ダメージ・無敵処理
      Invincible();
      // 地形の押し出し処理
      Extrude(move);
      _position.Add(move);     // 現在座標の更新
      // ワールド座標の更新
      WorldMatrix();
      // ステージが変わった時座標変更
      auto stage = "boss";
      if (_app.GetStageComponent().GetStageName().generic_string() == stage && _stageChange == true) {
        auto oldPos = _position;
        _position.Set(0.0f, 845.f, -200.f);
        move = _position - oldPos;
        _stageChange = false;
      }
      // SE停止
      StopSE();
      // カメラの更新
      _app.GetCamera().Process(AppMath::Vector4(rightX, rightY), _position, _move->GetOldPosition().Direction(_position));
      // ワールド座標の設定
      MV1SetMatrix(_model, UtilityDX::ToMATRIX(_world));
      // 画面外判定
      OffScreen();
      return true;
    }

    bool Player::Draw() const{
      if (_drawFlag != false) {
        MV1DrawModel(_model); // 自機の描画
      }
      _gaugeHp.Draw();      // HPゲージの描画
      _gaugeTrick.Draw();   // トリックゲージの描画
#ifdef _DEBUG
      // デバッグ情報の出力
      DebugDraw();
      // デバッグフラグがある場合のみ描画処理を行う
      if (_app.GetDebugFlag()) {
        _attack->Draw(); // 攻撃判定の描画
      }
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

    AppMath::Vector4 Player::GetCameraForward() const {
      // カメラの取得
      const auto camera = _app.GetCamera();
      // カメラ・注視座標の取得
      auto cameraPosition = camera.GetPosition();
      auto cameraTarget = camera.GetTarget();
      // カメラから向きへのベクトル
      using Vector4 = AppMath::Vector4;
      using Matrix44 = AppMath::Matrix44;
      // ビュー変換行列の取得

      auto view = AppMath::Matrix44::CreateLookAt(cameraPosition, cameraTarget, Vector4(1.0f, 1.0f, 1.0f));
      // 逆行列
      auto inverse = view.Inverse(view);
      // 自機の向きを取得
      auto rotation = GetRotationRadianY();
      // 別名定義
      using Vector4 = AppMath::Vector4;
      // 向きベクトル
      auto vector = Vector4(1.0f, 0.0f, -1.0f);
      // 
      vector = vector * rotation;
      // 二点間の距離を算出
      auto l = cameraPosition.Direction(cameraTarget);
      l.SetY(0.0f);
      // 
      auto direction = cameraPosition.Direction(cameraTarget);
      // カメラ向きの算出
      auto cameraForward = Vector4::Normalize(direction);

      auto dot = Vector4::Dot(_position, l);
      return Vector4::Up();
    }

    float Player::GetRotationRadianY() const {
#ifndef _DEBUG
      return  _rotation.GetY();
#else
      return AppMath::Utility::DegreeToRadian(_rotation.GetY());
#endif
    }

    AppMath::Vector4 Player::GetFramePosition(int frame) {
      // 取得した座標をVectorクラスに変換して返す
      auto position = MV1GetFramePosition(_model, frame);
      // 指定フレーム情報をベクトルクラスに変換
      return UtilityDX::ToVector(position);
    }

    bool Player::StateChanege(const AppFrame::Application::XBoxState& input) {
      // 攻撃状態かの判定
      if (IsAttackState()) {
        // 検索で使用するキーの取得
        auto key = NextKey();
        /**
         * @brief  攻撃遷移用の入力判定を行うか
         * @param  nextKey 遷移判定で使用するキーボタン
         * @param  flag    攻撃遷移フラグ(true:遷移予約 false:予約なし)
         * @return true:入力判定を行う false:入力判定を行わない
         */
        auto AttackInput = [](int nextKey, bool flag) {
          // 遷移フラグが立っているかの判定
          if (flag) {
            return false; // 入力判定は行わない
          }
          // キーの取得に成功したかを返す
          return nextKey != -1;
        };
        // 入力判定を行うか
        if (AttackInput(key, _nextAttack)) {
          // 攻撃遷移判定
          if (input.GetButton(key, false) && _stateComponent->Process(_modelAnim.GetMainPlayTime())) {
            // 条件を満たしている場合は攻撃遷移フラグをセットする
            _nextAttack = true;
            return true;
          }
        }
        /**
         * @brief  アニメーションの終了判定
         * @param  animEnd アニメーション終了フラグ
         * @param  brand   アニメーションブレンドフラグ
         * @return true:終了　false:終了していない
         */
        auto IsAnimEnd = [](bool animEnd, bool brand) {
          return animEnd == true && brand == false;
        };
        // アニメーションが終了している場合
        if (_modelAnim.GetMainAnimEnd()) {
          // 攻撃遷移フラグがセットされている場合
          if (_nextAttack) {
            // フラグをリセット
            _nextAttack = false;
            // 現在の攻撃処理を終了
            _attack->Finish();
            // 条件を満たしたので更新を行う
            SetStateParam(stateMap.at(_playerState));
            // 攻撃処理開始
            _attack->Start();
            // 
            _intervalAttack = true;
            return true;
          }
          // 待機状態への遷移を行うか
          if (_intervalAttack) {
            // アニメーションブレンド中かの判定
            if (_modelAnim.IsBlending()) {
              return true;
            }
            // アニメーションブレンドが終了したので待機処理を無効
            _intervalAttack = false;
          }
          // ジャンプモーションがセットされている場合は弾く
          if (_modelAnim.IsSetMainAnim(JumpUp)) {
            return true;
          }
          // 重力処理
          _gravity = true;
          // 現在の状態を見て空中攻撃
          if (_playerState == PlayerState::JumpAttack1 || _playerState == PlayerState::JumpAttack2 || _playerState == PlayerState::JumpAttack3) {
            // ジャンプ落ちるモーションにする
            _playerState = PlayerState::Fall;
          }
          else {
            // 待機状態に遷移する
            _playerState = PlayerState::Idle;
          }
          // 攻撃終了
          _attack->Finish();
          // インターバル時間の設定
          _attack->SetInterval(150.0f);
          // 状態遷移判定を中断
          _stateComponent->Finish();
        }
        return true;
      }
      // 攻撃状態に遷移するかの判定？
      if (_playerState == PlayerState::Idle || _playerState == PlayerState::Run || _playerState == PlayerState::Walk) {
        // 攻撃状態に遷移できるか
        if (_attack->ToAttack()) {
          // 弱攻撃判定
          auto light = InputAttackCheck(input, XINPUT_BUTTON_Y, LightFlag);
          // 強攻撃判定
          auto heavy = InputAttackCheck(input, XINPUT_BUTTON_X, HeavyFlag);
          // どちらかの状態に遷移したか
          if (light || heavy) {
            _gravity = false;
            return true;
          }
        }
        // 足場に立っている場合のみ
        if (_isStand) {
          // Aボタンの入力があった場合はジャンプ状態に遷移
          if (input.GetButton(XINPUT_BUTTON_A, false)) {
            Jump();      // ジャンプ処理
            return true; // 遷移する
          }
        }
      }
      // 空中攻撃状態に遷移するかの判定？
      if (_playerState == PlayerState::Jump || _playerState == PlayerState::Fall) {
        // 攻撃状態に遷移できるか
        if (_attack->ToAttack()) {
          // 弱攻撃判定
          auto light = InputAttackCheck(input, XINPUT_BUTTON_Y, LightFlag);
          // 強攻撃判定
          auto heavy = InputAttackCheck(input, XINPUT_BUTTON_X, HeavyFlag);
          // どちらかの状態に遷移したか
          if (light || heavy) {
            _gravity = false;
            return true;
          }
        }
      }
      // 必殺技準備に遷移するかの判定
      if (_gaugeTrick.Getvalue() >= TrickMax) {
        // 攻撃状態に遷移できるか
        if (_attack->ToAttack()) {
          auto exicite = InputExciteTrick(input, XINPUT_BUTTON_B);
          if (exicite) {
            _app.GetSoundComponent().PlayBackGround("ready", 200);
            return true;
          }
        }
        if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
          if (_playerState == PlayerState::ExciteTrickReady) {
            _playerState = PlayerState::ExciteTrick;
            // 流す音声の文字列の取得
            auto voice = voiceMap.at(PlayerStateToNumber());
            _app.GetSoundComponent().PlayBackGround(voice, 200);
            _app.GetSoundComponent().PlayBackGround("barst", 200);
            // 無敵時間を開始する
            _invincible->Start();
            // 攻撃判定をセットするか
            if (!attackMap.contains(PlayerStateToNumber())) {
              return true;
            }
            // 攻撃判定で使用するフレーム番号の取得
            auto frames = attackMap.at(PlayerStateToNumber());
            // 攻撃判定が出るまでのフレーム数の取得
            auto occurrence = occurrenceMap.at(PlayerStateToNumber());
            // フレームとコリジョン情報の設定
            _attack->SetFrame(frames, AddSpheres(static_cast<int>(frames.size()), 2000.f), occurrence);
          }
          else if (_playerState == PlayerState::ExciteTrick) {
            if (_modelAnim.GetMainAnimEnd()) {
              _drawFlag = false;
            }
            if (_app.GetEffectServer().GetUltSlashEnd()) {
              _drawFlag = true;
              _playerState = PlayerState::ExciteTrickEnd;
              // 流す音声の文字列の取得
              auto voice = voiceMap.at(PlayerStateToNumber());
              _app.GetSoundComponent().PlayBackGround(voice, 200);
            }
          }
          else if (_playerState == PlayerState::ExciteTrickEnd) {
            if (_modelAnim.GetMainAnimEnd() && !_modelAnim.IsBlending()) {
              _playerState = PlayerState::Idle;
              // ゲージの値をリセット
              _trickValue = 0;
              // 攻撃終了
              _attack->Finish();
              // インターバル時間の設定
              _attack->SetInterval(150.0f);
            }
          }
        }
      }
      // ダッシュ状態に遷移可能な場合
      if (IsChangeDash()) {
        // ダッシュ状態に遷移するかの判定
        if (input.GetButton(XINPUT_BUTTON_RIGHT_SHOULDER, false)) {
          DashStart(); // ダッシュ処理の開始
          return true;
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
      case PlayerState::JumpAttack1:
      case PlayerState::JumpAttack2:
        return key; // 対応するキーを返す
      case PlayerState::Attack3:
      case PlayerState::JumpAttack3:
        return -1;  // 処理は派生しない
      default:
        return -2;  // 攻撃状態ではない
      }
    }

    bool Player::InputAttackCheck(const AppFrame::Application::XBoxState& input, const int key, bool flag) {
      // 入力が行われたかの判定
      if (input.GetButton(key, false)) {
        // 現在の状態に応じて攻撃状態を切り替え
        switch (_playerState) {
        case PlayerState::Jump:
        case PlayerState::Fall:
          // 空中攻撃1に遷移
          SetStateParam(PlayerState::JumpAttack1);
          break;
        default:
          // 攻撃1に遷移
          SetStateParam(PlayerState::Attack1);
          break;
        }
        // 攻撃判定で使用するフレーム番号の取得
        auto frames = attackMap.at(PlayerStateToNumber());
        // 攻撃判定が出るまでのフレーム数の取得
        auto occurrence = occurrenceMap.at(PlayerStateToNumber());
        // 流す音声の文字列の取得
        auto voice = voiceMap.at(PlayerStateToNumber());
        _app.GetSoundComponent().PlayBackGround(voice, 200);
        // フレームとコリジョン情報の設定
        _attack->SetFrame(frames, AddSpheres(static_cast<int>(frames.size())), occurrence);
        _stateComponent->Start();
        _attack->Start();
        _attackFlag = flag;
        return true; // 遷移する
      }
      return false; // 入力無し
    }

    bool Player::InputExciteTrick(const AppFrame::Application::XBoxState& input, const int key) {
      // 入力が行われたかの判定
      if (input.GetButton(key, false)) {
        // 必殺技に遷移する
        _playerState = PlayerState::ExciteTrickReady;
        // 流す音声の文字列の取得
        auto voice = voiceMap.at(PlayerStateToNumber());
        _app.GetSoundComponent().PlayBackGround(voice, 200);
        _attack->Start();
        return true; // 遷移する
      }
      return false; // 入力無し
    }

    AppMath::Vector4 Player::Move(const float leftX, const float leftY) {
      // 移動ベクトル
      auto move = AppMath::Vector4();
      // 攻撃状態の場合
      if (_attack->IsAttack()) {
        return move;  // 移動を行わない
      }
      // ダッシュ中も処理を行わない
      if (_dash->IsDash()) {
        return move;
      }
      // 移動量の生成
      if (_move->Move(leftX, leftY)) {
        // 移動量の取得
        move = _move->MoveVector();
        // 向きベクトルを設定
        _forward = AppMath::Vector4::Normalize(move);
      }
      return move; // 移動量を返す
    }

    void Player::LoadResource() {
      // 各種リソースの読み取り処理
      auto [model, key1] = _app.GetModelServer().GetModel(_modelKey, 1);
      // 取得したモデルハンドルを設定
      _model = model;
    }

    void Player::InputValue(const AppFrame::Application::XBoxState& input) {
      // 左スティックの入力情報
      auto leftStick = input.GetStick(false);
      // float値に変換する
      auto x = static_cast<float>(leftStick.first);
      auto y = static_cast<float>(leftStick.second);
      // デッドゾーン
      auto deadZone = input.GetDeadZone();
      // 
      auto deadX = static_cast<float>(deadZone.first);
      auto deadZ = static_cast<float>(deadZone.second);
      // 入力情報の設定
      _stick = std::make_pair((x / deadX), (y / deadZ));
    }


    void Player::SetState() {
      // 状態の設定
      _id = ObjectId::Player;
      _state = ObjectState::Active;
      _gravity = true; // 重力処理を行う
      // 移動コンポーネントの生成
      _move = std::make_unique<Object::MoveComponent>(*this);
      // 地形の衝突判定を設定
      using Vector = AppFrame::Math::Vector4;
      // 平面の設定
      auto a = Vector(0.0f, 0.0f, 100.0f);
      auto b = Vector(-100.0f, 0.0f, -100.0f);
      auto c = Vector(100.0f, 0.0f, -100.0f);
      _plane = std::make_unique<AppFrame::Math::Plane>(a, b, c);
      // HPの設定
      _playerHP = GyroHP;
      // ソートの設定
      _sort = 2;
      // ゲージの設定
      _gaugeHp.Init(GyroHP);
      _gaugeTrick.Init(TrickMax);
      _stageChange = true;

      _forward = AppMath::Vector4(0.0f, 0.0f, 1.0f);
    }

    void Player::SetRotation(const AppFrame::Math::Vector4 move) {
      // 指定状態の場合は
      if (_playerState == PlayerState::Idle || _playerState == PlayerState::Run || _playerState == PlayerState::Walk) {
        // 移動量のいずれかが基準を超えていたらRunに遷移
        if (IsRun(move)) {
          // 走り状態に遷移
          _playerState = PlayerState::Run;
          if (!_app.GetSoundComponent().CheckSound("dash")) {
            _app.GetSoundComponent().PlayLoop("dash");
          }
          return;
        }
        // 移動量がある場合は歩きモーションに遷移
        // 後程移動量に応じて歩き・ダッシュモーション切り替え
        if (move.LengthSquared()) {
          _playerState = PlayerState::Walk;
          if (!_app.GetSoundComponent().CheckSound("walk")) {
            _app.GetSoundComponent().PlayLoop("walk");
          }
          return;
        }
        // 待機状態に遷移する
        _playerState = PlayerState::Idle;
      }
    }

    bool Player::IsRun(const AppMath::Vector4& move) {
      // 移動量の取得
      auto [x, y , z] = move.GetVector3();
      // 別名定義
      using Utility = AppMath::Utility;
      // 正数に変換
      x = Utility::ToPlus(x) * Utility::ToPlus(x);
      z = Utility::ToPlus(z) * Utility::ToPlus(z);
      // 走り状態かの判定
      if (RunValue <= x || RunValue <= z) {
        return true; // 走り状態に
      }
      return false;  // 走り状態ではない
    }

    void Player::KnockBack(AppMath::Vector4& move) {
      // ノックバック状態ではない場合は処理を行わない
      if (!_knockBack->IsKnockBack()) {
        return;
      }
      // 更新処理呼び出し
      _knockBack->Process();
      // 移動量更新
      move = _knockBack->MoveVector();
    }

    void Player::Animation(PlayerState old) {
      // 状態が切り替わっている場合のみ処理を行う
      if (_playerState == old) {
        return;
      }
      // 遷移番号の取得
      auto number = PlayerStateToNumber();
      // 取得に失敗した場合は処理を行わない
      if (number == -1) {
        return;
      }
      // モデルアニメーション情報の取得
      const auto modelAnim = animMap.at(number);
      auto [key, frame, speed, loop] = modelAnim.ModelAnim();
      // アニメーションをセットする
      _modelAnim.SetBlendAttach(key.data(), frame, speed, loop);
      // エフェクトが登録されている場合は再生する
      if (!modelAnim.Effect() == 0) {
        PlayEffect();
      }
    }

    void Player::StopSE() {
      // 走りSE停止
      if (_playerState != PlayerState::Run) {
        if (_app.GetSoundComponent().CheckSound("dash")) {
          _app.GetSoundComponent().StopSound("dash");
        }
      }
      // 歩きSE停止
      if (_playerState != PlayerState::Walk) {
        if (_app.GetSoundComponent().CheckSound("walk")) {
          _app.GetSoundComponent().StopSound("walk");
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
      // 衝突フラグ
      auto flag = false;
      // オブジェクトとの衝突判定
      if (IsStandObject(newCapsule, newPos)) {
        flag = true;
        _position = newPos;
        _capsule->SetPosition(_position);
      }
      // 障害物と接触していない場合は床との衝突判定を行う
      else flag = StandFloor(newCapsule, newPos);
      // 衝突フラグに応じて処理を切り替える
      switch (flag) {
      case true: // 床との接触有り
        // ジャンプの後始末を行う
        if (_jump->IsJump()) {
          _jump->Finish();
        }
        if (_playerState == PlayerState::Jump || _playerState == PlayerState::Fall || _playerState == PlayerState::JumpAttack1 || _playerState == PlayerState::JumpAttack2 || _playerState == PlayerState::JumpAttack3) {
          _playerState = PlayerState::Idle;
        }
        break;
      case false:
        // 新しい座標をセット
        _position = newPos;
        // コリジョン情報に更新をかける
        _capsule->SetPosition(_position);
        break;
      }
      return flag; // 床に立っている
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
      std::shared_ptr<Enemy::EnemyBase> enemy;
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

    void Player::Extrude(AppMath::Vector4& move) {
      // 地形との衝突判定
      auto newPosition = _position + move;
      // コリジョンと壁の押し出し処理を行う
      auto newCapsule = *_capsule;
      newCapsule.SetPosition(newPosition);
      auto radius = newCapsule.GetRadius(); // 半径の取得
      // モデルハンドルの取得
      auto stageMap = _app.GetStageComponent().GetStageModel();
      // 押し出しフラグ
      auto flag = false;
      // 地形モデル(壁)との衝突判定
      for (auto model : stageMap) {
        // 線分の取得
        auto [start, end] = newCapsule.LineSegment().GetVector();
        // 地形との衝突判定を行う
        auto hit = MV1CollCheck_Capsule(model, 1, UtilityDX::ToVECTOR(start), UtilityDX::ToVECTOR(end), radius);
        // 接触箇所がない場合
        if (!hit.HitNum) {
          // 衝突用情報の後始末を行う
          MV1CollResultPolyDimTerminate(hit);
          continue;
        }
        // 更新フラグ
        if (!flag) flag = true;
        // 別名定義
        using Vector4 = AppMath::Vector4;
        // ヒットしたポリゴン回分押し出す
        for (auto i = 0; i < hit.HitNum; ++i) {
          // 法線ベクトルの取得
          auto normal = Vector4(hit.Dim[i].Normal.x, hit.Dim[i].Normal.y, hit.Dim[i].Normal.z);
          // スライドベクトル
          auto slide = Vector4::Cross(normal, Vector4::Cross(move, normal));
          slide = Vector4::Scale(slide, Vector4(-1.0, 0.0f, -1.0f));
          // slide.SetY(0.0f);
          newPosition.Add(slide);
          newCapsule.SetPosition(newPosition);
        }
        // 衝突判定情報の後始末を行う
        MV1CollResultPolyDimTerminate(hit);
      }
      // 座標を更新する
      if (flag) {
        move.Zero();
        _position = newPosition;
        _capsule->SetPosition(newPosition);
      }
    }

    void Player::Jump() {
      // ジャンプフラグが立っている場合は処理を行わない
      if (_jump->IsJump()) {
        return; // インターバルがない場合は処理を行わない
      }
      // ジャンプ処理を開始する
      _jump->Start(); // ジャンプ開始
      _gravityScale = 0.0f;
      _playerState = PlayerState::Jump;
      _app.GetSoundComponent().PlayBackGround("jump");
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
      // ローカル座標を攻撃座標にセットする
      _attack->Process();
    }

    bool Player::ExiteTrick() {
      return true;
    }

    bool Player::DashStart() {
      // 入力情報の取得
      auto [x, z] = _stick;
      // 入力方向の取得
      auto move = Vector4(x, 0.0f, z);
      // ダッシュを設定
      if (!_dash->SetDash(move, 600.0f, 18000.0f)) {
        return false; // 設定に失敗
      }
      // ダッシュを開始する
      _dash->Start();
      // ダッシュ中は無敵状態にする
      _invincible->InvincibleStart();
      // 状態の変更
      _playerState = PlayerState::Dash;
      _app.GetSoundComponent().PlayBackGround("avoidance");
      return true;
    }

    void Player::Dash(AppMath::Vector4& move) {
      // ダッシュコンポーネントが非活動状態の場合は処理を行わない
      if (_dash->GetDashState() == Object::DashComponent::DashState::NoActive) {
        return;
      }
      // ダッシュの更新に成功したか
      if (_dash->Process()) {
        // 移動量を設定
        move = _dash->GetMovePower();
        // 待機状態に遷移した場合
        if (_dash->IsInterval()) {
          /**
           * @brief  地形に立っているかに応じて待機・降下状態を返す
           * @param  stand 立ちフラグ
           * @return true:Idel状態 false:降下モーション
           */
          auto NextState = [](bool stand) {
            return (stand) ? Player::PlayerState::Idle : Player::PlayerState::Fall;
          };
          // 立ちフラグを返す
          _playerState = NextState(_isStand);
          // インターバル時間の設定
          _dash->SetIniterval(10.0f * 20.0f);
          // 無敵処理を終了する
          _invincible->Finish();
        }
        return;
      }
    }

    bool Player::IsChangeDash() {
      // ダッシュ中の場合は設定しない
      if (_dash->IsDash()) {
        return false;
      }
      // 状態判定
      switch (_playerState) {
      case PlayerState::Idle:
      case PlayerState::Run:
      case PlayerState::Walk:
      case PlayerState::Jump:
      case PlayerState::Fall:
        return true; // 遷移可能
      default:
        return false; // 遷移不可
      }
    }

    void Player::IsDamage() {
      auto objects = _app.GetObjectServer().GetObjects(); // オブジェクトのコピー
      std::shared_ptr<Enemy::EnemyBase> enemy;
      // 衝突判定を行う
      for (auto obj : objects) {
        // 敵の場合のみ処理を行う
        if (obj->GetId() != ObjectId::Enemy) continue;
        // 敵が攻撃状態の場合ダメージ判定に進む
        enemy = std::dynamic_pointer_cast<Enemy::EnemyBase>(obj);
        if (enemy->GetEnemyState() != Enemy::EnemyBase::EnemyState::Attack) continue;
        // 球と球の衝突判定
        if (_capsule->IntersectSphere(std::dynamic_pointer_cast<Enemy::EnemyBase>(obj)->GetCollision())) {
          // ノックバック処理の開始
          _knockBack->Start();
          // ヒットポイントの減少
          _playerHP -= 100;
          _gaugeHp.Sub(100);
          // HPが一定を下回った場合
          if (_playerHP <= 0) {
            _app.GameOver(); // ゲームオーバー処理の呼び出し
          }
          // 無敵時間を開始する
          _invincible->Start();
        }
      }
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
      case PlayerState::JumpAttack1:
      case PlayerState::JumpAttack2:
      case PlayerState::JumpAttack3:
        return true;  // 攻撃状態
      default:
        return false; // 攻撃状態ではない
      }
    }

    bool Player::SetStateParam(PlayerState pState) {
      // 状態の切り替え
      _playerState = pState;
      // 遷移判定フレームの登録が行われているかの判定
      if (chaneMap.contains(_playerState)) {
        // 自機の状態を取得
        auto [start, end] = chaneMap.at(_playerState);
        // 切り替え状態を設定する
        _stateComponent->Set(_modelAnim.GetMainPlayTime(), start, end);
        _stateComponent->Start();
      } 
      else {
        // ステートの設定を終了する
        _stateComponent->Finish();
      }

      // 攻撃判定をセットするか
      if (!attackMap.contains(PlayerStateToNumber())) {
        return true;
      }
      // 流す音声の文字列の取得
      auto voice = voiceMap.at(PlayerStateToNumber());
      _app.GetSoundComponent().PlayBackGround(voice, 200);
      // 攻撃判定で使用するフレーム番号の取得
      auto frames = attackMap.at(PlayerStateToNumber());
      // 攻撃判定が出るまでのフレーム数の取得
      auto occurrence = occurrenceMap.at(PlayerStateToNumber());
      // フレームとコリジョン情報の設定
      _attack->SetFrame(frames, AddSpheres(static_cast<int>(frames.size())), occurrence);
      return true; // 切り替えを完了
    }

    int Player::PlayerStateToNumber() const {
      auto number = -1;
      // プレイヤーの状態に応じた数値を返す
      switch (_playerState) {
        // 待機
      case PlayerState::Idle:
        return StateNumberIdle;
        // 歩き
      case PlayerState::Walk:
        return StateNumberWalk;
        // 走り
      case PlayerState::Run:
        return StateNumberRun;
        // ジャンプ
      case PlayerState::Jump:
        return StateNumberJump;
        // 攻撃1
      case PlayerState::Attack1:
        number = StateNumberLight1;
        break;
        // 攻撃2
      case PlayerState::Attack2:
        number = StateNumberLight2;
        break;
        // 攻撃3
      case PlayerState::Attack3:
        number = StateNumberLight3;
        break;
        // 空中攻撃1
      case PlayerState::JumpAttack1:
        number = StateNumberAirLight1;
        break;
        // 空中攻撃2
      case PlayerState::JumpAttack2:
        number = StateNumberAirLight2;
        break;
        // 空中攻撃3
      case PlayerState::JumpAttack3:
        number = StateNumberAirLight3;
        break;
        // エキサイトトリック前
      case PlayerState::ExciteTrickReady:
        return StateNumberExciteActive;
        // エキサイトトリック中
      case PlayerState::ExciteTrick:
        return StateNumberExciteTrick1;
        // エキサイトトリック後
      case PlayerState::ExciteTrickEnd:
        return StateNumberExciteTrick2;
        // ダッシュ
      case PlayerState::Dash:
        return StateNumberDash;
        // 降下
      case PlayerState::Fall:
        return StateNumberFall;
      default:
        return -1;
      }
      // 強攻撃・弱攻撃かの判定
      auto IsHevyLight = [](bool flag) {
        return (flag == true) ? 1 : 0;
      };
      // 攻撃番号
      return number + IsHevyLight(_attackFlag);
    }

    bool Player::PlayEffect() const {
      auto modelAnim = animMap.at(PlayerStateToNumber());
#ifndef _DEBUG
      auto eRad = -_rotation.GetY();
#else
      auto eRad = -AppMath::Utility::DegreeToRadian(_rotation.GetY());
#endif
      // エフェクトの再生
      _app.GetEffectServer().MakeEffect(modelAnim.Effect(), _position, eRad);
      return true;
    }

    void Player::Invincible() {
      // 無敵状態か
      switch (_invincible->Invincible()) {
      case true:
        // 無敵時間の経過処理を呼び出し
        _invincible->Process();
        break;
      case false:
        // 無敵状態ではない場合、ダメージ判定を行う
        IsDamage();
        break;
      }
    }

    bool Player::StandFloor(Object::CollisionCapsule capsule, const AppMath::Vector4& position) {
      // 線分の取得
      const auto [start, end] = capsule.LineSegment().GetVector();
      // 地形(床)と線分の衝突判定
      for (int i = 0; i < _app.GetStageComponent().GetStageModel().size(); i++) {
        // ステージハンドルの取得
        auto handleMap = _app.GetStageComponent().GetStageModel()[i];
        // 地形と線分の衝突判定
        auto hit = MV1CollCheck_Line(handleMap, 2, UtilityDX::ToVECTOR(end), UtilityDX::ToVECTOR(start));
        // 衝突フラグがない場合
        if (hit.HitFlag == 0) {
          continue;
        }
        // 衝突地点を座標に代入
        _position = UtilityDX::ToVector(hit.HitPosition);
        // 新しい座標をコリジョンに反映
        _capsule->SetPosition(_position);
        return true; // 接触している
      }
      return false;  // 接触していない
    }

    bool Player::IsStandObject(Object::CollisionCapsule capsule, AppMath::Vector4& position) {
      // オブジェクトサーバの取得
      auto object = _app.GetObjectServer();
      // ベクトルの取得
      auto [min, max] = capsule.LineSegment().GetVector();
      // 障害物のみソートする
      for (auto obj : object.GetObjects()) {
        // オブジェクトの判定
        if (obj->GetId() != ObjectBase::ObjectId::Item) continue;
        // 対象との接触判定を行う
        auto item = std::dynamic_pointer_cast<Item::Box>(obj);
        // コリジョン情報の取得
        auto collision = item->GetCollision();
        // めり込んでいる場合は押し出し処理を行う
        if (collision.CheckPoint(min) || collision.CheckPoint(max)) {
          position.SetY(collision.GetMax().GetY());
          return true;
        }
      }
      return false;
    }

    std::vector<std::shared_ptr<Object::CollisionBase>> Player::AddSpheres(const int num, float radius) {
      // 当たり判定を格納するコンテナ
      std::vector<std::shared_ptr<Object::CollisionBase>> collision;
      collision.clear();
      for (auto number = 0; number <= num; ++number) {
        // 生成した当たり判定を登録
        collision.emplace_back(std::make_shared<Object::CollisionSphere>(*this, _position, radius));
      }
      return collision;
    }

    bool Player::OffScreen() {
      // 既に死亡しているか
      if (IsDead()) {
        return true;
      }
      // 画面外に堕ちているか
      const auto y = _position.GetY();
      // y軸が画面外に出た場合は死亡する
      if (_position.GetY() <= 0.0f) {
        // ゲームオーバー
        _state = ObjectState::Dead;
        _app.GameOver();
        return true;
      }
      return false;
    }

    bool Player::Heal(const float heal) {
      // ゲージが最大値の場合は更新を行わない
      const auto max = _gaugeHp.GetMaxGauge();
      // 現在HPの取得
      auto hp = _gaugeHp.GetFloatPoint();
      // 最大値の場合は処理を行わない
      if (_gaugeHp.IsMax()) {
        return false;
      }
      // 自機を回復させる
      _gaugeHp.Add(heal);
      return true;
    }
  } // namespace Player
}// namespace Gyro
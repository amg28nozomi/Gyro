/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  インゲーム処理を行うモード
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ModeGame.h"
#include <memory>
#include <algorithm>
#include "ApplicationMain.h"
#include "Player.h"
#include "EnemyWheel.h"
#include "PrimitiveBase.h"
#include "PrimitivePlane.h"
#include "ObjectServer.h"
#include "StageComponent.h"
#include "ModeGameOver.h"
#include "ModeResult.h"
#include "ModePause.h"
#include "ModeLoading.h"
#include "EnemyDrone.h"
#include "EnemyDroneBoss.h"
#include "EnemyWheel.h"
#include "EnemyWheelBoss.h"

namespace {
    constexpr auto TEXTURE = _T("res/Stage/water.png");
    constexpr auto GravityScale = -9.8f; //!< 重力スケール
    constexpr auto BgmVolume = 50;       //!< BGMの再生ボリューム
} // namespace

namespace Gyro {
  namespace Mode {

    ModeGame::ModeGame(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {
    }

    ModeGame::~ModeGame() {
    }

    bool ModeGame::Enter() {
      // リソースの読み取り処理
      LoadResource();
      // エフェクトリソースの読み取り
      LoadEffectResource();
      // ステージフラグに応じて使用するキー切り替え
      auto k = (_stageFlag) ? "stage" : "boss";
      _appMain.GetStageComponent().CreateStage(k);
      // BGMのループ再生開始
      PlayBgm("bgm", BgmVolume);
      // ゲーム状態の設定
      _gameState = GameState::Play;
      SetSpawn(); // オブジェクトを生成
      // カメラの初期化
      _appMain.GetCamera().Init();
      // ライトの設定
      _light = std::make_unique<Light::Light>();
      // シャドウの設定
      _shadow = std::make_unique<Shadow::Shadow>(_appMain);
      // ゲームフラグの初期化
      _appMain.SetGameOver(false);
      _appMain.SetGameClear(false);
      _appMain.SetGamePause(false);
      // ステージに応じてフラグ切り替え
      _wave1 = (_stageFlag) ? true : false;
      _wave2 = (_stageFlag) ? true : false;
      _wave3 = (_stageFlag) ? true : false;
      _wave4 = (_stageFlag) ? true : false;
      _bossStage = true;
      _waveNum = 0;
      return true;
    }

    bool ModeGame::Exit() {
      // ライトをデフォルトに戻す
      DeleteLightHandleAll();
      // 
      SetLightEnable(true);
      // 生成したオブジェクトを削除
      _appMain.GetObjectServer().Release();
      // 複製したハンドルを削除
      ResetObjectNumber();
      // 生成したエフェクトを削除
      _appMain.GetEffectServer().Release();
      // 生成したモデルを削除
      _appMain.GetStageComponent().ReleaseModel();
      // クリア判定が立っている場合
      if (_appMain.GetGameClear()) {
        _stageFlag = true;
      }
      BossCountReset();
      return true;
    }

    bool ModeGame::Init() {
      // 使用するデータの読み込みを記述する
      _plane.Initialize(40960.0f, 40);
      _plane.Load(TEXTURE);
      _plane.Create();
      // 重力加速度をセットする
      AppMath::GravityBase::SetScale(GravityScale);
      return true;
    }

    bool ModeGame::Input(AppFrame::Application::InputOperation& input) {
      // 入力状態の取得
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // STARTボタンが押された場合、ポーズを呼び出す
      if (device.GetButton(XINPUT_BUTTON_START, App::InputTrigger)) {
        // ポーズ
        Pause();
      }
#ifdef _DEBUG
      // デバッグ時限定:左スティックが押された場合、デバッグフラグを切り替える
      if (device.GetButton(XINPUT_BUTTON_RIGHT_THUMB, App::InputTrigger)) {
        // デバッグフラグの切り替え
        _app.ChengeDebugFlag();
        // サウンドフラグに応じて処理を切り替える
        switch (_app.GetSoundComponent().CheckSound("bgm")) {
          // サウンド再生中
        case AppFrame::Sound::Play:
          // BGMの再生を停止する
          _app.GetSoundComponent().StopSound("bgm");
          break;
          // サウンド停止中
        case AppFrame::Sound::Stop:
          // BGMのループ再生開始
          PlayBgm("bgm", BgmVolume);
          break;
        }
      }
#endif
      return true;
    }

    bool ModeGame::Process() {
      // モード削除予約判定
      PopBack();
      // モードゲームの入力処理
      Input(_app.GetOperation());
      // ゲームオーバー判定
      if (GameOver()) {
        return true;
      }
      // ゲームクリア判定
      if (_appMain.GetGameClear()) {
        Result();
        return true;
      }
      // ポーズ判定
      if (_appMain.GetGamePause()) {
        return true;
      }
      // オブジェクトサーバの更新処理
      _appMain.GetObjectServer().Process();
      // エフェクトの更新処理
      _appMain.GetEffectServer().Process();
      // 地形の更新処理
      _plane.Process();
      // 各種ステージの描画
      _appMain.GetStageComponent().Process();
      // スポーンするタイミング
      SpawnTiming();
      return true;
    }

    bool ModeGame::Draw() const {
      // 影の描画
      _shadow->Draw();
      // 各種ステージの描画
      _appMain.GetStageComponent().Draw();
      // 地形の描画
      _plane.Draw();
      // 各種描画処理
      _appMain.GetObjectServer().Draw();
      // シャドウマップの設定解除
      SetUseShadowMap(0, -1);
      // エフェクトの描画
      _appMain.GetEffectServer().Draw();
      return true;
    }

    bool ModeGame::StageChange(const Stage::StageTransition::StageType& key) {
      // ステージの遷移予約を行う
      return _appMain.GetStageTransition().ChangeReserve(key);
    }

    std::string_view ModeGame::BossStageSpawn() {
      // ボスステージ
      const Object::SpawnTable bossP{
        { Object::TypePlayer, {0.0f, 1000.f, -200.f}, {}, {1.0f, 1.0f, 1.0f} },
        { Object::TypeSkySphere, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.5f, 1.5f, 1.5f}},
      };
      const Object::EnemyTable bossE{
        { Object::EnemyWheelBoss, { -200.0f, 394.0f, -10000.0f}, {0.0f, -180.0f, 0.0f }, {5.0f, 5.0f, 5.0f}},
        { Object::EnemyDroneBoss, { 300.0f, 394.0f, -10000.0f}, {0.0f, -180.0f, 0.0f }, {7.0f, 7.0f, 7.0f}},
      };
      // スポーン情報
      Object::SpawnData bossTable{
      {0, std::make_tuple(bossP, bossE)},
      };
      // ボスステージキー
      std::string_view key = "bossTable";
      // スポーンテーブルの登録
      _appMain.GetSpawnServer().AddSpawnTable(key.data(), bossTable);
      return key;
    }

    bool ModeGame::ToGameClear() {
      // ボスカウントをインクリメント
      ++_bossCount;
      // ゲームクリアに遷移するかの判定を行う
      if (IsGameClear()) {
        _stageFlag = true;
        return true; // 遷移する
      }
      return false; // クリアに遷移しない
    }

    void ModeGame::LoadResource() {
      // リソースの読み込みは行われているか
      if (_isLoad) {
        return; // 読み込み済み
      }
      // 別名定義
      using ModelServer = AppFrame::Model::ModelServer;
      // 各種モデルハンドルの読み込み
      const ModelServer::ModelDatas mv1Models{
        {"enemyWheel", "res/Enemy/Wheel/enemy1_set.mv1"},                 // 地上敵
        {"enemyWheelBoss", "res/Enemy/Wheel/enemy1_boss_set.mv1"},        // 地上敵ボス
        {"enemyDrone", "res/Enemy/Drone/enemy2 Multimotion fin.mv1"},     // 空中敵
        {"enemyDroneBoss", "res/Enemy/Drone/enemy2 Bos Multimotion fin1.mv1"},  // 空中敵ボス
      };
      // モデルサーバで読み取りを行う
      _app.GetModelServer().AddMV1Model(mv1Models);
      // サウンド情報の読み取り
      using SoundServer = AppFrame::Sound::SoundServer;
      // Sound情報の設定
      const SoundServer::SoundMap soundMap{
        {"bgm", "res/Sound/BGM/Stage.mp3"},
        {"walk", "res/Sound/SE/Player/Walk.wav"},            // 歩きSE
        {"dash", "res/Sound/SE/Player/Dash.wav"},            // 走りSE
        {"jump", "res/Sound/SE/Player/Jump.wav"},            // ジャンプSE
        {"landing", "res/Sound/SE/Player/Landing.wav"},      // 着地SE
        {"avoidance", "res/Sound/SE/Player/Avoidance.wav"},  // 回避SE
        {"ready", "res/Sound/SE/Player/TrickReady.wav"},     // 必殺発動SE
        {"barst", "res/Sound/SE/Player/TrickBarst.wav"},     // 必殺攻撃SE
        {"wMove", "res/Sound/SE/Enemy/WheelMove.wav"},       // 地上移動SE
        {"wAttack", "res/Sound/SE/Enemy/WheelAttack.wav"},   // 地上攻撃SE
        {"dAttack", "res/Sound/SE/Enemy/DroneAttack.wav"},   // 空中攻撃SE
        {"hitLow", "res/Sound/SE/Enemy/EnemyHitLow.wav"},       // ヒット弱SE
        {"hitHigh", "res/Sound/SE/Enemy/EnemyHitHigh.wav"},     // ヒット強SE
        {"destroy", "res/Sound/SE/Enemy/EnemyDestroy.wav"},     // 破壊SE
        // プレイヤー声
        {"idle", "res/Sound/SE/Player/Voice/idle.wav"},         // 待機
        {"jump", "res/Sound/SE/Player/Voice/jump.wav"},         // ジャンプ
        {"damage", "res/Sound/SE/Player/Voice/damage.wav"},     // ダメージ
        {"excite1", "res/Sound/SE/Player/Voice/excite1.wav"},   // 必殺技構え
        {"excite2", "res/Sound/SE/Player/Voice/excite2.wav"},   // 必殺技中
        {"excite3", "res/Sound/SE/Player/Voice/excite3.wav"},   // 必殺技後
        {"low1", "res/Sound/SE/Player/Voice/low1.wav"},         // 弱攻撃1
        {"low2", "res/Sound/SE/Player/Voice/low2.wav"},         // 弱攻撃2
        {"low3", "res/Sound/SE/Player/Voice/low3.wav"},         // 弱攻撃3
        {"lowex", "res/Sound/SE/Player/Voice/lowex.wav"},       // 弱攻撃EX
        {"high1", "res/Sound/SE/Player/Voice/high1.wav"},       // 強攻撃1
        {"high2", "res/Sound/SE/Player/Voice/high2.wav"},       // 強攻撃2
        {"high3", "res/Sound/SE/Player/Voice/high3.wav"},       // 強攻撃3
        {"jlow1", "res/Sound/SE/Player/Voice/jweak1.wav"},      // 空中弱攻撃1
        {"jlow2", "res/Sound/SE/Player/Voice/jlow2.wav"},       // 空中弱攻撃2
        {"jlow3", "res/Sound/SE/Player/Voice/jlow3.wav"},       // 空中弱攻撃3
        {"jhigh1", "res/Sound/SE/Player/Voice/jhigh.wav"},      // 空中強攻撃1
        {"jhigh2", "res/Sound/SE/Player/Voice/jhigh2.wav"},     // 空中強攻撃2
      };
      // サウンドサーバに登録
      _app.GetSoundServer().AddSounds(soundMap);
      // 読み込み完了
      _isLoad = true;
    }

    void ModeGame::LoadEffectResource() {
      // リソースの読み込みは行われているか
      if (_isEffectLoad) {
        return; // 読み込み済み
      }
      using EffectLoadServer = Effect::EffectLoadServer;
      // エフェクトハンドルの読み込み
      const EffectLoadServer::EffectMap effectMap{
        {EffectKey::PlayerDash, "res/Effect/Player/Dash/player_dash.efkefc", 5.0f},
        {EffectKey::PlayerJump, "res/Effect/Player/Jump/jump.efkefc", 5.0f},
        {EffectKey::PlayerLanding, "res/Effect/Player/Landing/landing.efkefc", 5.0f},
        {EffectKey::PlayerHit, "res/Effect/Player/Hit/Player_hit.efkefc", 5.0f},
        {EffectKey::PlayerAvoidance, "res/Effect/Player/Avoidance/player_avoidance.efkefc", 5.0f},
        {EffectKey::PlayerWeakAttack1, "res/Effect/Player/WeakAttack1/player_weakattack_1.efkefc", 5.0f},
        {EffectKey::PlayerWeakAttack2, "res/Effect/Player/WeakAttack2/player_weakattack_2.efkefc", 5.0f},
        {EffectKey::PlayerWeakAttack3, "res/Effect/Player/WeakAttack3/player_weakattack_3.efkefc", 5.0f},
        {EffectKey::PlayerWeakAttackEX, "res/Effect/Player/WeakAttackEX/player_weakattack_EX.efkefc", 5.0f},
        {EffectKey::PlayerHeavyAttack1, "res/Effect/Player/HeavyAttack1/HeavyAttack1.efkefc", 30.0f},
        {EffectKey::PlayerHeavyAttack2, "res/Effect/Player/HeavyAttack2/Player_attack_heavy_02.efkefc", 10.0f},
        {EffectKey::PlayerHeavyAttack3, "res/Effect/Player/HeavyAttack3/HeavyAttack3.efkefc", 20.0f},
        {EffectKey::PlayerAirWeakAttack1, "res/Effect/Player/AirWeakAttack1/Player_attack_air_normal_01.efkefc", 10.0f},
        {EffectKey::PlayerAirWeakAttack2, "res/Effect/Player/AirWeakAttack2/Player_attack_air_normal_02.efkefc", 10.0f},
        {EffectKey::PlayerAirWeakAttack3, "res/Effect/Player/AirWeakAttack3/Player_attack_air_normal_03.efkefc", 10.0f},
        {EffectKey::PlayerAirHeavyAttack1, "res/Effect/Player/AirHeavyAttack1/Player_attack_air_heavy_01.efkefc", 10.0f},
        {EffectKey::PlayerAirHeavyAttack2, "res/Effect/Player/AirHeavyAttack2/Player_attack_air_heavy_02.efkefc", 5.0f},
        {EffectKey::PlayerUltActivate, "res/Effect/Player/UltActivate/Player_ult_activate.efkefc", 5.0f},
        {EffectKey::PlayerUltSlash, "res/Effect/Player/UltSlash/Player_ult_slash.efkefc", 20.0f},
        {EffectKey::EnemyEyeLight, "res/Effect/Enemy/EyeLight/Enemy_EyeLight.efkefc", 20.0f},
        {EffectKey::EnemyGroundAttack1, "res/Effect/Enemy/GroundAttack1/Enemy_ground_attack1.efkefc", 10.0f},
        {EffectKey::EnemyGroundAttack2, "res/Effect/Enemy/GroundAttack2/Enemy_ground_attack2.efkefc", 10.0f},
        {EffectKey::EnemyAirAttack, "res/Effect/Enemy/AirAttack/Enemy_air_attack.efkefc", 15.0f},
        {EffectKey::EnemyHit, "res/Effect/Enemy/Hit/Enemy_Hit.efkefc", 20.0f},
        {EffectKey::EnemyExprosion, "res/Effect/Enemy/Exprosion/Enemy_Exprosion.efkefc", 10.0f},
        {EffectKey::EnemyBossEyeLight, "res/Effect/Enemy/Boss/EyeLight/Enemy_EyeLight.efkefc", 40.0f},
        {EffectKey::EnemyBossGroundAttack1, "res/Effect/Enemy/Boss/GroundAttack1/Enemy_ground_attack1.efkefc", 20.0f},
        {EffectKey::EnemyBossGroundAttack2, "res/Effect/Enemy/Boss/GroundAttack2/Enemy_ground_attack2.efkefc", 20.0f},
        {EffectKey::EnemyBossAirAttack, "res/Effect/Enemy/Boss/AirAttack/Enemy_air_attack.efkefc", 30.0f},
        {EffectKey::EnemyBossHit, "res/Effect/Enemy/Boss/Hit/Enemy_Hit.efkefc", 40.0f},
        {EffectKey::EnemyBossExprosion, "res/Effect/Enemy/Boss/Exprosion/Enemy_Exprosion.efkefc", 20.0f},
        {EffectKey::StageBarrier, "res/Effect/Stage/Barrier/stage_barrier.efkefc", 5.0f},
        {EffectKey::StageBoxDestroy, "res/Effect/Stage/BoxDestroy/Box_Destroy.efkefc", 5.0f},
        {EffectKey::StageHeal, "res/Effect/Stage/Heal/Player_heal.efkefc", 5.0f}
      };
      // エフェクトサーバに登録
      _appMain.GetEffectLoadServer().AddEffects(effectMap);
      // 読み込み完了
      _isEffectLoad = true;
    }

    void ModeGame::SetSpawn() {
      // 生成キー
      std::string stageKey;
      // 初期ステージの場合
      if (_stageFlag) {
        // スポーン情報の設定
        const Object::SpawnTable normal{
          // 自機の生成情報
          // 引数1:オブジェクトタイプ(0:自機　1:敵)
          // 引数2:ローカル座標
          // 引数3:向き
          // 引数4:スケール
          { Object::TypePlayer, {0.0f, 675.0f, 1800.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
          { Object::TypeSkySphere, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.5f, 1.5f, 1.5f}},
        };
        // 空のスポーン情報
        const Object::SpawnTable none{
        };
        // エネミーテーブル
        const Object::EnemyTable wave1{
          // 陸上型エネミーの配置情報
          { Object::EnemyWheel, { 100.0f, 705.0f, -200.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
          { Object::EnemyWheel, { -200.0f, 705.0f, -200.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        };
        const Object::EnemyTable wave2{
          { Object::EnemyDrone, { 100.0f, 845.0f, -4500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
        };
        const Object::EnemyTable wave3{
          { Object::EnemyWheel, { 4100.0f, 480.0f, -7500.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
          { Object::EnemyWheel, { 4200.0f, 480.0f, -7500.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
          { Object::EnemyDrone, { 4400.0f, 480.0f, -7500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
        };
        const Object::EnemyTable wave4{
          { Object::EnemyDrone, { 2100.0f, 765.0f, -11200.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
          { Object::EnemyWheel, { 2200.0f, 765.0f, -11200.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
          { Object::EnemyWheel, { 2300.0f, 765.0f, -11200.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
          { Object::EnemyDrone, { 2400.0f, 765.0f, -11200.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
        };
        const Object::EnemyTable wave5{
          { Object::EnemyWheel, { 1600.0f, 1200.0f, -15500.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
          { Object::EnemyDrone, { 1700.0f, 1200.0f, -15500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
          { Object::EnemyDrone, { 1800.0f, 1200.0f, -15500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
          { Object::EnemyWheel, { 1900.0f, 1200.0f, -15500.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        };
        // アイテムテーブル
        const Object::ItemTable item{
          { "player", 1, {0.0f, 200.0f, -100.0f}, {}, {1.0f, 1.0f, 1.0f}}
        };
        // 各種テーブルを基にスポーンテーブルを作成
        Object::SpawnData3 table1{
          {0, std::make_tuple(normal, wave1, item)},
        };
        Object::SpawnData table2{
          {0, std::make_tuple(none, wave2)},
        };
        Object::SpawnData table3{
          {0, std::make_tuple(none, wave3)},
        };
        Object::SpawnData table4{
          {0, std::make_tuple(none, wave4)},
        };
        Object::SpawnData table5{
          {0, std::make_tuple(none, wave5)},
        };
        // スポーンテーブルの登録
        _appMain.GetSpawnServer().AddSpawnTable("wave1", table1);
        _appMain.GetSpawnServer().AddSpawnTable("wave2", table2);
        _appMain.GetSpawnServer().AddSpawnTable("wave3", table3);
        _appMain.GetSpawnServer().AddSpawnTable("wave4", table4);
        _appMain.GetSpawnServer().AddSpawnTable("wave5", table5);
        stageKey = "wave1";
      }
      // ボスステージの場合
      else {
        stageKey = BossStageSpawn().data();
      }
#ifndef _DEBUG
      _appMain.GetSpawnServer().SetStage(stageKey);
#else
      try {
        _appMain.GetSpawnServer().SetStage(stageKey);
      } catch (std::logic_error error) {
        OutputDebugString(error.what());
      }
#endif
      // 指定したスポーン情報を基にオブジェクトを生成する
      _appMain.GetSpawnServer().Spawn(0);
    }

    void ModeGame::SpawnTiming() {
      // ウェーブ数
      const auto waveMax = 4;
      // 自機の取得
      auto player = _appMain.GetObjectServer().GetPlayer();
      // 取得に失敗した場合は更新を行わない
      if (player == nullptr) {
        return;
      }
      // プレイヤーの位置を見て敵スポーンさせる
      const auto pPos = player->GetPosition();
      // 生成判定
      if (pPos.GetZ() < -2244.f && _wave1 == true) {
        _appMain.GetSpawnServer().SetStage("wave2");
        _appMain.GetSpawnServer().Spawn(0);
        _waveNum++;
        _wave1 = false;
      }else if (pPos.GetZ() < -6600.f && _wave2 == true) {
        _appMain.GetSpawnServer().SetStage("wave3");
        _appMain.GetSpawnServer().Spawn(0);
        _waveNum++;
        _wave2 = false;
      }else if (pPos.GetZ() < -9600.f && _wave3 == true) {
        _appMain.GetSpawnServer().SetStage("wave4");
        _appMain.GetSpawnServer().Spawn(0);
        _waveNum++;
        _wave3 = false;
      }else if (pPos.GetZ() < -13500.f && _wave4 == true) {
        _appMain.GetSpawnServer().SetStage("wave5");
        _appMain.GetSpawnServer().Spawn(0);
        _waveNum++;
        _wave4 = false;
      }
      // 最終ウェーブ時に
      if (waveMax <= _waveNum && _bossStage == true) {
        //// オブジェクトのコピー
        //auto objects = _appMain.GetObjectServer().GetObjects();
        //// 動的配列に一致する要素があるか判定する
        //auto activeEnemy = std::any_of(objects.begin(), objects.end(),
        //  [](std::shared_ptr<Object::ObjectBase>& obj) {
        //    // 生存状態の敵はいるか
        //    return (obj->GetId() == Object::ObjectBase::ObjectId::Enemy) && obj->GetState() == Object::ObjectBase::ObjectState::Active; });
        //if (!activeEnemy) {
        //  // いないならステージの切り替え
        //  StageChange("boss");
        //}else {
        //  for (auto obj : objects) {
        //    // 敵なら続く
        //    if (obj->GetId() != Object::ObjectBase::ObjectId::Enemy)continue;
        //    auto enemy = std::dynamic_pointer_cast<Enemy::EnemyBase>(obj).get()->GetState();
        //    enemy = Object::ObjectBase::ObjectState::Dead;
        //  }
        //  // ステージの切り替え
        //  StageChange("boss");
        //}
        // ステージの切り替え
        //StageChange("boss");
        // モードローディングへ遷移
        Loading();
        _appMain.GetSpawnServer().SetStage(BossStageSpawn().data());
        // 指定したスポーン情報を基にオブジェクトを生成する
        _appMain.GetSpawnServer().Spawn(0);
        _stageFlag = false;
        _bossStage = false;
      }
    }

    bool ModeGame::GameOver() {
      // ゲームオーバーフラグが立っているかの判定
      if (_gameState != GameState::GameOver) {
        return false; // ゲームオーバーではないため処理を行わない
      }
      // キーが登録されているか
      bool key = _app.GetModeServer().Contains("GameOver");
      if (!key) {
        // モードゲームオーバーの登録
        _appMain.GetModeServer().AddMode("GameOver", std::make_shared<Mode::ModeGameOver>(_appMain));
      }
      // モードゲームオーバー遷移
      _appMain.GetModeServer().TransionToMode("GameOver");
      // BGMの再生を停止する
      _appMain.GetSoundComponent().StopSound("bgm");
      // 消去予約
      _popBack = true;
      return true;
    }

    void ModeGame::Result() {
      // キーが登録されているか
      bool key = _app.GetModeServer().Contains("Result");
      if (!key) {
        // モードリザルトの登録
        _appMain.GetModeServer().AddMode("Result", std::make_shared<Mode::ModeResult>(_appMain));
      }
      // モードリザルト遷移
      _appMain.GetModeServer().TransionToMode("Result");
      // BGMの再生を停止する
      _appMain.GetSoundComponent().StopSound("bgm");
      // 消去予約
      _popBack = true;
    }

    void ModeGame::ToGameOver() {
      _gameState = GameState::GameOver;
    }

    void ModeGame::Pause() {
      // キーが登録されているか
      bool key = _app.GetModeServer().Contains("Pause");
      if (!key) {
        // モードポーズの登録
        _appMain.GetModeServer().AddMode("Pause", std::make_shared<Mode::ModePause>(_appMain));
      }
      // モードポーズ遷移
      _appMain.GetModeServer().PushBack("Pause");
      // ポーズ開始
      _appMain.SetGamePause(true);
    }

    void ModeGame::Loading() {
      // キーが登録されているか
      bool key = _appMain.GetModeServer().Contains("Loading");
      if (!key) {
        // モードロードディングの登録
        _appMain.GetModeServer().AddMode("Loading", std::make_shared<Mode::ModeLoading>(_appMain));
      }
      // モードロードディング遷移
      _appMain.GetModeServer().PushBack("Loading");
    }

    void ModeGame::ResetObjectNumber() {
      // 各種オブジェクト番号を初期化
      Enemy::EnemyDrone::ModelNumberReset();
      Enemy::EnemyDroneBoss::ModelNumberReset();
      Enemy::EnemyWheel::ModelNumberReset();
      Enemy::EnemyWheelBoss::ModelNumberReset();
      // オブジェクトサーバから複製品を削除する
      _appMain.GetModelServer().DeleteDuplicateModels("", true);
    }
  } // namespace Mode
} // namespace Gyro
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
      // ステージの切り替え
      StageChange("stage");
      // オブジェクトを生成
      SetSpawn();
      // BGMのループ再生開始
      _app.GetSoundComponent().PlayLoop("bgm");
      // 再生音量の設定
      _app.GetSoundComponent().SetVolume("bgm", BgmVolume);
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
      return true;
    }

    bool ModeGame::Exit() {
      // ライトをデフォルトに戻す
      DeleteLightHandleAll();
      SetLightEnable(true);
      // 生成したオブジェクトを削除
      _appMain.GetObjectServer().Release();
      // 生成したエフェクトを削除
      _appMain.GetEffectServer().Release();
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
      // STARTボタンが押された場合、アプリケーションを終了する
      if (device.GetButton(XINPUT_BUTTON_START, App::InputTrigger)) {
        _appMain.RequestTerminate(); // アプリケーションの終了処理を呼び出し
        // ポーズ
        //Pause();
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
          // BGMの再生開始
          _app.GetSoundComponent().PlayLoop("bgm");
          // 再生音量の設定
          _app.GetSoundComponent().SetVolume("bgm", 50);
          break;
        }
      }
#endif
      return true;
    }

    bool ModeGame::Process() {
      // モードゲームの入力処理
      Input(_app.GetOperation());
      // ゲームオーバー判定
      if (_appMain.GetGameOver()) {
        GameOver();
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

    bool ModeGame::StageChange(std::string_view key) {
      // ステージ素材の削除
      _appMain.GetStageComponent().ReleaseStageInfo();
      // ステージコンポーネントの初期化
      if (!_appMain.GetStageComponent().Init(key.data())) {
        return false;
      }
      // ステージキーを設定
      _key = key.data();
      // フェードイン・フェードアウトをセットする

      return true; // 設定成功
    }

    Application::ApplicationMain& ModeGame::GetAppMain() {
      return _appMain;
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
        {"enemyDroneBoss", "res/Enemy/Drone/enemy2 Bos Multimotion fin.mv1"},  // 空中敵ボス
      };
      // モデルサーバで読み取りを行う
      _app.GetModelServer().AddMV1Model(mv1Models);
      // サウンド情報の読み取り
      using SoundServer = AppFrame::Sound::SoundServer;
      // Sound情報の設定
      const SoundServer::SoundMap soundMap{
        {"bgm", "res/Sound/Stage.mp3"}
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
        {EffectKey::PlayerWeakAttack1, "res/Effect/Player/WeakAttack1/player_weakattack_1.efkefc", 5.0f},
        {EffectKey::PlayerWeakAttack2, "res/Effect/Player/WeakAttack2/player_weakattack_2.efkefc", 5.0f},
        {EffectKey::PlayerWeakAttack3, "res/Effect/Player/WeakAttack3/player_weakattack_3.efkefc", 5.0f},
        {EffectKey::PlayerWeakAttackEX, "res/Effect/Player/WeakAttackEX/player_weakattack_EX.efkefc", 5.0f},
        {EffectKey::PlayerHeavyAttack1, "res/Effect/Player/HeavyAttack1/HeavyAttack1.efkefc", 30.0f},
        {EffectKey::PlayerHeavyAttack2, "res/Effect/Player/HeavyAttack2/Player_attack_heavy_02.efkefc", 15.0f},
        {EffectKey::PlayerHeavyAttack3, "res/Effect/Player/HeavyAttack3/HeavyAttack3.efkefc", 20.0f},
        {EffectKey::PlayerAirWeakAttack1, "res/Effect/Player/AirWeakAttack1/Player_attack_air_normal_01.efkefc", 5.0f},
        {EffectKey::PlayerAirWeakAttack2, "res/Effect/Player/AirWeakAttack2/Player_attack_air_normal_02.efkefc", 5.0f},
        {EffectKey::PlayerAirWeakAttack3, "res/Effect/Player/AirWeakAttack3/Player_attack_air_normal_03.efkefc", 5.0f},
        {EffectKey::PlayerAirHeavyAttack1, "res/Effect/Player/AirHeavyAttack1/Player_attack_air_heavy_01.efkefc", 5.0f},
        {EffectKey::PlayerAirHeavyAttack2, "res/Effect/Player/AirHeavyAttack2/Player_attack_air_heavy_02.efkefc", 5.0f},
        {EffectKey::PlayerUltActivate, "res/Effect/Player/Ult_Activate/Player_ult_activate.efkefc", 5.0f},
        {EffectKey::PlayerUltSlash, "res/Effect/Player/Ult_Slash/Player_ult_slash.efkefc", 5.0f},
        {EffectKey::PlayerJump, "res/Effect/Player/Jump/jump.efkefc", 5.0f},
        {EffectKey::PlayerHit, "res/Effect/Player/Hit/Hit.efkefc", 5.0f},
        {EffectKey::EnemyEyeLight, "res/Effect/Enemy/EyeLight/Enemy_EyeLight.efkefc", 20.0f},
        {EffectKey::EnemyGroundAttack, "res/Effect/Enemy/GroundAttack/Enemy_ground_attack.efkefc", 10.0f},
        {EffectKey::EnemyAirAttack, "res/Effect/Enemy/AirAttack/Enemy_air_attack.efkefc", 15.0f},
        {EffectKey::EnemyHit, "res/Effect/Enemy/Hit/Enemy_Hit.efkefc", 20.0f},
        {EffectKey::EnemyExprosion, "res/Effect/Enemy/Exprosion/Enemy_Exprosion.efkefc", 10.0f},
        {EffectKey::EnemyBossEyeLight, "res/Effect/Enemy/Boss/EyeLight/Enemy_EyeLight.efkefc", 40.0f},
        {EffectKey::EnemyBossGroundAttack, "res/Effect/Enemy/Boss/GroundAttack/Enemy_ground_attack.efkefc", 20.0f},
        {EffectKey::EnemyBossAirAttack, "res/Effect/Enemy/Boss/AirAttack/Enemy_air_attack.efkefc", 30.0f},
        {EffectKey::EnemyBossHit, "res/Effect/Enemy/Boss/Hit/Enemy_Hit.efkefc", 40.0f},
        {EffectKey::EnemyBossExprosion, "res/Effect/Enemy/Boss/Exprosion/Enemy_Exprosion.efkefc", 20.0f},
        {EffectKey::StageBarrier, "res/Effect/Stage/stage_barrier/stage_barrier.efkefc", 5.0f},
        {EffectKey::StageBoxDestroy, "res/Effect/Stage/Box_Destroy/Box_Destroy.efkefc", 5.0f}
      };
      // エフェクトサーバに登録
      _appMain.GetEffectLoadServer().AddEffects(effectMap);
      // 読み込み完了
      _isEffectLoad = true;
    }

    void ModeGame::SetSpawn() {
      // スポーン情報の設定
      const Object::SpawnTable normal {
        // 自機の生成情報
        // 引数1:オブジェクトタイプ(0:自機　1:敵)
        // 引数2:ローカル座標
        // 引数3:向き
        // 引数4:スケール
        { Object::TypePlayer, {0.0f, 675.0f, 1800.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
        { Object::TypeSkySphere, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {3.0f, 3.0f, 3.0f}}
      };
      // 空のスポーン情報
      const Object::SpawnTable none{
      };
      // エネミーテーブル
      const Object::EnemyTable wave1{
        // 陸上型エネミーの配置情報
        { Object::EnemyWheel, { 100.0f, 705.0f, -200.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { -200.0f, 705.0f, -200.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        /*{ Object::EnemyWheel, { 300.0f, 705.0f, -200.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { -400.0f, 705.0f, -200.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},*/
      };
      const Object::EnemyTable wave2{
        { Object::EnemyDrone, { 100.0f, 845.0f, -4500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
        { Object::EnemyDrone, { -200.0f, 845.0f, -4500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
        /*{ Object::EnemyDrone, { 300.0f, 845.0f, -4500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
        { Object::EnemyDrone, { -400.0f, 845.0f, -4500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},*/
      };
      const Object::EnemyTable wave3{
        { Object::EnemyWheel, { 4100.0f, 480.0f, -7500.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { 4200.0f, 480.0f, -7500.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        /*{ Object::EnemyDrone, { 4300.0f, 480.0f, -7500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
        { Object::EnemyDrone, { 4400.0f, 480.0f, -7500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},*/
      };
      const Object::EnemyTable wave4{
        { Object::EnemyDrone, { 2100.0f, 765.0f, -11200.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
        { Object::EnemyWheel, { 2200.0f, 765.0f, -11200.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        /*{ Object::EnemyWheel, { 2300.0f, 765.0f, -11200.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyDrone, { 2400.0f, 765.0f, -11200.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},*/
      };
      const Object::EnemyTable wave5{
        { Object::EnemyWheel, { 1600.0f, 1200.0f, -15500.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyDrone, { 1700.0f, 1200.0f, -15500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
        /*{ Object::EnemyDrone, { 1800.0f, 1200.0f, -15500.0f}, {0.0f, -180.0f, 0.0f }, {4.0f, 4.0f, 4.0f}},
        { Object::EnemyWheel, { 1900.0f, 1200.0f, -15500.0f}, {0.0f, -180.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},*/
      };
      // 各種テーブルを基にスポーンテーブルを作成
      Object::SpawnData table{
        {0, std::make_tuple(normal, wave1)},
        {1, std::make_tuple(none, wave2)},
        {2, std::make_tuple(none, wave3)},
        {3, std::make_tuple(none, wave4)},
        {4, std::make_tuple(none, wave5)},
      };
      // スポーンテーブルの登録
      _appMain.GetSpawnServer().AddSpawnTable("test", table);
#ifndef _DEBUG
      _appMain.GetSpawnServer().SetStage("test");
#else
      try {
        _appMain.GetSpawnServer().SetStage("test");
      } catch (std::logic_error error) {
        OutputDebugString(error.what());
      }
#endif
      // 指定したスポーン情報を基にオブジェクトを生成する
      _appMain.GetSpawnServer().Spawn(0);
    }

    void ModeGame::SpawnTiming() {
      auto waveMax = 4;
      // プレイヤーの位置を見て敵スポーンさせる
      auto pPos = _appMain.GetObjectServer().GetPlayer().get()->GetPosition();
      if (pPos.GetZ() < -2244.f && _wave1 == true) {
        _appMain.GetSpawnServer().Spawn(1);
        _waveNum++;
        _wave1 = false;
      }else if (pPos.GetZ() < -6600.f && _wave2 == true) {
        _appMain.GetSpawnServer().Spawn(2);
        _waveNum++;
        _wave2 = false;
      }else if (pPos.GetZ() < -9600.f && _wave3 == true) {
        _appMain.GetSpawnServer().Spawn(3);
        _waveNum++;
        _wave3 = false;
      }else if (pPos.GetZ() < -13500.f && _wave4 == true) {
        _appMain.GetSpawnServer().Spawn(4);
        _waveNum++;
        _wave4 = false;
      }
      // 最終ウェーブ時に
      if (waveMax <= _waveNum && _bossStage == true) {
        // オブジェクトのコピー
        //auto objects = _appMain.GetObjectServer().GetObjects();
        //// 動的配列に一致する要素があるか判定する
        //auto activeEnemy = std::any_of(objects.begin(), objects.end(),
        //  [](std::shared_ptr<Object::ObjectBase>& obj) {
        //    // 生存状態の敵はいるか
        //    return (obj->GetId() == Object::ObjectBase::ObjectId::Enemy) && obj->GetState() == Object::ObjectBase::ObjectState::Active; });
        //if (!activeEnemy) {
        //  // ステージの切り替え
        //  StageChange("boss");
        //}

        // ステージの切り替え
        StageChange("boss");
        // ボスステージ
        const Object::SpawnTable bossP{
          { Object::TypeSkySphere, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {3.0f, 3.0f, 3.0f}},
        };
        const Object::EnemyTable bossE{
          { Object::EnemyWheelBoss, { -200.0f, 720.0f, -10000.0f}, {0.0f, -180.0f, 0.0f }, {5.0f, 5.0f, 5.0f}},
          { Object::EnemyDroneBoss, { 300.0f, 720.0f, -10000.0f}, {0.0f, -180.0f, 0.0f }, {7.0f, 7.0f, 7.0f}},
        };
        // スポーン情報
        Object::SpawnData bossTable{
        {0, std::make_tuple(bossP, bossE)},
        };
        // スポーンテーブルの登録
        _appMain.GetSpawnServer().AddSpawnTable("bossTable", bossTable);
        _appMain.GetSpawnServer().SetStage("bossTable");
        // 指定したスポーン情報を基にオブジェクトを生成する
        _appMain.GetSpawnServer().Spawn(0);
        _bossStage = false;
      }
    }

    void ModeGame::GameOver() {
      // モードゲームの削除
      _appMain.GetModeServer().PopBuck();
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
    }

    void ModeGame::Result() {
      // モードゲームの削除
      _appMain.GetModeServer().PopBuck();
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
    }

    void ModeGame::Pause() {
      // キーが登録されているか
      bool key = _app.GetModeServer().Contains("Pause");
      if (!key) {
        // モードポーズの登録
        _appMain.GetModeServer().AddMode("Pause", std::make_shared<Mode::ModePause>(_appMain));
      }
      // モードポーズ遷移
      _appMain.GetModeServer().TransionToMode("Pause");
      // ポーズ開始
      _appMain.SetGamePause(true);
    }
  } // namespace Mode
} // namespace Gyro
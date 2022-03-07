/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  インゲーム処理を行うモード
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ModeGame.h"
#include <memory>
#include "ApplicationMain.h"
#include "Player.h"
#include "EnemyWheel.h"
#include "PrimitiveBase.h"
#include "PrimitivePlane.h"
#include "ObjectServer.h"
#include "StageComponent.h"
#include "ModeGameOver.h"

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

      return true;
    }

    bool ModeGame::Exit() {
      // ライトをデフォルトに戻す
      DeleteLightHandleAll();
      SetLightEnable(true);
      // 生成したオブジェクトを削除
      _appMain.GetObjectServer().Release();
      return true;
    }

    bool ModeGame::Init() {
      // 使用するデータの読み込みを記述する
      _plane.Initialize(35840.0, 35);
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
      bool gameover = _appMain.GetObjectServer().GetPlayer()->GetGameOver();
      if (gameover) {
        GameOver();
        return true;
      }
      // オブジェクトサーバの更新処理
      _appMain.GetObjectServer().Process();
      // エフェクトの更新処理
      _appMain.GetEffect().Process();
      // 地形の更新処理
      _plane.Process();
      // 各種ステージの描画
      _appMain.GetStageComponent().Process();
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
      _appMain.GetEffect().Draw();
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
        {"enemy", "res/Enemy/Wheel/Enemy_multimotion.mv1"}, // 敵
        {"stage", "res/Stage/houseGEO_1.mv1"}               // ステージ
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
        {Effect::PlayerWeakAttack1, "res/Effect/Player/WeakAttack1/player_weakattack_1.efkefc", 5.0f},
        {Effect::PlayerWeakAttack2, "res/Effect/Player/WeakAttack2/player_weakattack_2.efkefc", 5.0f},
        {Effect::PlayerWeakAttack3, "res/Effect/Player/WeakAttack3/player_weakattack_3.efkefc", 5.0f},
        {Effect::PlayerWeakAttackEX, "res/Effect/Player/WeakAttackEX/player_weakattack_EX.efkefc", 5.0f},
        {Effect::PlayerHeavyAttack1, "res/Effect/Player/HeavyAttack1/HeavyAttack1.efkefc", 20.0f},
        {Effect::PlayerHeavyAttack3, "res/Effect/Player/HeavyAttack3/HeavyAttack3.efkefc", 20.0f},
        {Effect::PlayerAirWeakAttack1, "res/Effect/Player/AirWeakAttack1/Player_attack_air_normal_01.efkefc", 5.0f},
        {Effect::PlayerAirWeakAttack2, "res/Effect/Player/AirWeakAttack2/Player_attack_air_normal_02.efkefc", 5.0f},
        {Effect::PlayerAirWeakAttack3, "res/Effect/Player/AirWeakAttack3/Player_attack_air_normal_03.efkefc", 5.0f},
        {Effect::PlayerAirHeavyAttack1, "res/Effect/Player/AirHeavyAttack1/Player_attack_air_heavy_01.efkefc", 5.0f},
        {Effect::PlayerAirHeavyAttack2, "res/Effect/Player/AirHeavyAttack2/Player_attack_air_heavy_02.efkefc", 5.0f},
        {Effect::PlayerUltActivate, "res/Effect/Player/Ult_Activate/Player_ult_activate.efkefc", 5.0f},
        {Effect::PlayerUltSlash, "res/Effect/Player/Ult_Slash/Player_ult_slash.efkefc", 5.0f},
        {Effect::PlayerJump, "res/Effect/Player/Jump/jump.efkefc", 5.0f},
        {Effect::PlayerHit, "res/Effect/Player/Hit/Hit.efkefc", 5.0f},
        {Effect::EnemyEyeLight, "res/Effect/Enemy/EyeLight/Enemy_EyeLight.efkefc", 20.0f},
        {Effect::EnemyGroundAttack, "res/Effect/Enemy/GroundAttack/Enemy_ground_attack.efkefc", 10.0f},
        {Effect::EnemyHit, "res/Effect/Enemy/Hit/Enemy_Hit.efkefc", 20.0f},
        {Effect::EnemyExprosion, "res/Effect/Enemy/Exprosion/Enemy_Exprosion.efkefc", 10.0f},
        {Effect::StageBarrier, "res/Effect/Stage/stage_barrier/stage_barrier.efkefc", 5.0f},
        {Effect::BoxDestroy, "res/Effect/Stage/Box_Destroy/Box_Destroy.efkefc", 5.0f}
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
        { Object::TypePlayer, {0.0f, 200.0f, -200.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
        { Object::TypeSkySphere, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}}
      };
      // エネミーテーブル
      const Object::EnemyTable enemy {
        // 陸上型エネミーの配置情報
        { Object::EnemyWheel, { 100.0f, 250.0f, 100.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { -200.0f, 250.0f, 200.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { 300.0f, 250.0f, 200.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { -400.0f, 250.0f, 200.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
      };
      // 各種テーブルを基にスポーンテーブルを作成
      Object::SpawnData table{
        {0, std::make_tuple(normal, enemy)}
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
  } // namespace Mode
} // namespace Gyro
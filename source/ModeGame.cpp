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
#include "Enemy/EnemyWheel.h"
#include "PrimitiveBase.h"
#include "PrimitivePlane.h"
#include "ObjectServer.h"
#include "SpawnServer.h"

namespace {
    constexpr auto TEXTURE = _T("res/Groundplants1_D.jpg");
}

namespace Gyro {
  namespace Mode {

    ModeGame::ModeGame(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {
    }

    ModeGame::~ModeGame() {
    }

    bool ModeGame::Enter() {
      // オブジェクトを生成
      SetSpawn();
      return true;
    }

    bool ModeGame::Exit() {
      // 生成したオブジェクトを取り除く
      _appMain.GetObjectServer().Release();
      return true;
    }

    bool ModeGame::Init() {
      LoadResource(); // 各種リソースの読み取りを行う
      // 使用するデータの読み込みを記述する
      _plane.Initialize(45000.0, 150);
      _plane.Load(TEXTURE);
      _plane.Create();
      // 重力加速度をセットする
      AppMath::GravityBase::SetScale(-9.8f);
      return true;
    }

    bool ModeGame::Input(AppFrame::Application::InputOperation& input) {
      // 入力状態の取得
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // STARTボタンが押された場合、アプリケーションを終了する
      if (device.GetButton(XINPUT_BUTTON_START, App::InputTrigger)) {
        _appMain.RequestTerminate();
      }
#ifdef _DEBUG
      // デバッグ時限定:左スティックが押された場合、デバッグフラグを切り替える
      if (device.GetButton(XINPUT_BUTTON_RIGHT_THUMB, App::InputTrigger)) {
        _app.GetSoundComponent().PlayLoop("bgm");
        _app.ChengeDebugFlag(); // デバッグフラグの切り替え
      }
#endif
      return true;
    }

    bool ModeGame::Process() {
      // 入力処理
      Input(_app.GetOperation());
      // オブジェクトサーバの更新処理実行
      _appMain.GetObjectServer().Process();
      _plane.Process();
      _plane.Render();
      return true;
    }

    bool ModeGame::Draw() const {
      // 描画処理呼び出し
      _appMain.GetObjectServer().Draw();
      // 並行光源を 1 つ追加する
      VECTOR light_dir = VGet(0.0f, 1.0f, 0.0f);
      auto light_handle = CreateDirLightHandle(light_dir);

      return true;
    }

    Application::ApplicationMain& ModeGame::GetAppMain() {
      return _appMain;
    }

    void ModeGame::LoadResource() const {
      using ModelServer = AppFrame::Model::ModelServer;
      // 各種モデルハンドルの読み込み
      const ModelServer::ModelDatas mv1Models{
        {"player" , "res/Player/Gyro Multimotion7.mv1"},    // 自機
        {"enemy", "res/Enemy/Wheel/Enemy_multimotion.mv1"}, // 敵
        {"sky", "res/SkySphere/skysphere.mv1"},       // スカイスフィア
        {"stage", "res/Stage/houseGEO_1.mv1"}         // ステージ
      };
      // モデルサーバで読み取りを行う
      _app.GetModelServer().AddMV1Model(mv1Models);
      // サウンド情報の読み取り
      using SoundServer = AppFrame::Sound::SoundServer;
      // 
      const SoundServer::SoundMap soundMap{
        {"test", "res/Sound/pose.wav"},
        {"bgm", "res/Sound/stage1.wav"}
      };
      // サウンドサーバに登録
      _app.GetSoundServer().AddSounds(soundMap);
      // エフェクト情報の読み取り
      LoadEffectResource();
    }

    void ModeGame::SetSpawn() {
      // スポーン情報の設定
      const Object::SpawnTable normal {
        // 自機の生成情報
        // 引数1:オブジェクトタイプ(0:自機　1:敵)
        // 引数2:ローカル座標
        // 引数3:向き
        // 引数4:スケール
        { Object::TypePlayer, {0.0f, 0.0f, 0.0f,}, {0.0f, 0.0f, 0.0f,}, {1.0f, 1.0f, 1.0f}}
      };
      // エネミーテーブル
      const Object::EnemyTable enemy {
        // 陸上型エネミーの配置情報
        { Object::EnemyWheel, { 100.0f, 0.0f, 100.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { 200.0f, 0.0f, 200.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}}
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
      _appMain.GetSpawnServer().Spawn(0);
    }

    void ModeGame::LoadEffectResource() const {
        using EffectServer = Effect::EffectServer;
        // エフェクトキー定数化
        const std::string_view eExprosion = "E_Exprosion";
        const std::string_view eEyeLight = "E_EyeLight";
        const std::string_view eHit = "E_Hit";
        const std::string_view pUltActivate = "P_ult_activate";
        const std::string_view pUltSlash = "P_ult_slash";
        // エフェクトハンドルの読み込み
        const EffectServer::EffectMap effectMap{
            {eExprosion, "res/Effect/Enemy_Exprosion/Enemy_Exprosion.efkefc"},
            {eEyeLight, "res/Effect/Enemy_EyeLight/Enemy_EyeLight.efkefc"},
            {eHit, "res/Effect/Enemy_Hit/Enemy_Hit.efkefc"},
            {pUltActivate, "res/Effect/Player_ult_activate/Player_ult_activate.efkefc"},
            {pUltSlash, "res/Effect/Player_ult_slash/Player_ult_slash.efkefc"}
        };
        // エフェクト拡大率の登録
        const EffectServer::EffectMagniMap effectMagniMap{
            {eExprosion, 5.0f},
            {eEyeLight, 20.0f},
            {eHit, 10.0f},
            {pUltActivate, 10.0f},
            {pUltSlash, 5.0f}
        };
        // エフェクトサーバに登録
        _appMain.GetEffectServer().AddEffects(effectMap, effectMagniMap);
    }
  } // namespace Mode
} // namespace Gyro
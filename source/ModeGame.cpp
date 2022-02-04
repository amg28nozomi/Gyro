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
      _appMain.GetObjectServer().Register(std::move(std::make_shared<Player::Player>(_appMain)));
      _appMain.GetObjectServer().Register(std::move(std::make_shared<Enemy::EnemyWheel>(_appMain)));
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
        {"player" , "res/Player/Gyro multibag.mv1"},  // 自機
        {"enemy", "res/Enemy/Enemy_multimotion.mv1"}, // 敵
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
    }
  } // namespace Mode
} // namespace Gyro
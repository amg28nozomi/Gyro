/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  インゲーム処理を行うモード
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ModeGame.h"
#include "ApplicationMain.h"

namespace Gyro {
  namespace Mode {

    ModeGame::ModeGame(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {
    }

    ModeGame::~ModeGame() {
    }

    bool ModeGame::Enter() {
      // オブジェクトの生成を行う
      return true;
    }

    bool ModeGame::Exit() {
      // 生成したオブジェクトの後始末を行う
      return true;
    }

    bool ModeGame::Init() {
      // 使用するデータの読み込みを記述する
      _player.Init();
      _plane.Initialize(45000.0, 150);
      _plane.Load(TEXTURE);
      _plane.Create();
      return true;
    }

    bool ModeGame::Input(AppFrame::Application::InputOperation& input) {
      // 入力状態の取得
      auto device = input.GetJoypadState();
      // Aキーが入力された場合
      if (device.GetKey() ^ PAD_INPUT_10) {
        // アプリケーションの終了要請を行う
        _app.RequestTerminate();
      }
      return true;
    }

    bool ModeGame::Process() {
      return true;
    }

    bool ModeGame::Draw() const {
      return true;
    }

    Application::ApplicationMain& ModeGame::GetAppMain() {
      return _appMain;
    }
  } // namespace Mode
} // namespace Gyro
/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  インゲーム処理を行うモード
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ModeGame.h"
#include "ApplicationMain.h"
#include "Player.h"
#include "PrimitiveBase.h"
#include "PrimitivePlane.h"

namespace {
    constexpr auto TEXTURE = _T("res/Groundplants1_D.jpg");
}

namespace Gyro {
  namespace Mode {

    ModeGame::ModeGame(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app), _player(app) {
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
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // STARTボタンが押された場合、アプリケーションを終了する
      if (device.GetButton(XINPUT_BUTTON_START, App::InputTrigger)) {
        _app.RequestTerminate();
      }
      return true;
    }

    bool ModeGame::Process() {
      Input(_app.GetOperation());
      _player.Process();
      _plane.Process();
      _plane.Render();
      return true;
    }

    bool ModeGame::Draw() const {
        _player.Draw();

        // 並行光源を 1 つ追加する
        VECTOR light_dir = VGet(-1.0f, -1.0f, -1.0f);
        auto light_handle = CreateDirLightHandle(light_dir);

      return true;
    }

    Application::ApplicationMain& ModeGame::GetAppMain() {
      return _appMain;
    }
  } // namespace Mode
} // namespace Gyro
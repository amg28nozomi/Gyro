#include "ModeGame.h"
#include "ApplicationMain.h"

namespace Gyro {
  namespace Mode {

    ModeGame::ModeGame(AppFrame::Application::ApplicationBase& app) : ModeBase(app) {
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
  } // namespace Mode
} // namespace Gyro
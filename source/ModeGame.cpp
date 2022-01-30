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
        _app.RequestTerminate();
      }
#ifdef _DEBUG
      // デバッグ時限定:左スティックが押された場合、デバッグフラグを切り替える
      if (device.GetButton(XINPUT_BUTTON_RIGHT_THUMB, App::InputTrigger)) {
        _app.ChangeDebugFlag();
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
  } // namespace Mode
} // namespace Gyro
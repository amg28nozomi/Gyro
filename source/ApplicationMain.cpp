/*****************************************************************//**
 * @file   ApplicationMain.cpp
 * @brief  アプリケーションベースのサブクラスの定義
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ApplicationMain.h"
#include "appframe.h"
#include <DxLib.h>
#include "ModeGame.h"

namespace Gyro {
  namespace Application {
    // アプリケーションの実体
    ApplicationMain application;
    
    ApplicationMain::ApplicationMain() : ApplicationBase() {
      // 実体の登録を行うか
      if (SetInstance()) {
        // 実体作成
        _instance = std::make_shared<ApplicationMain>();
      }
    }

    bool ApplicationMain::Init() {
      if (!ApplicationBase::Init()) {
        return false; // 初期化失敗
      }
      // モードゲームの登録
      _modeServer->AddMode("Game", std::make_shared<Mode::ModeGame>(*this));
      _modeServer->TransionToMode("Game");
      return true;
    }

    bool ApplicationMain::Input() {
      auto flag = ApplicationBase::Input();
      // 入力状態の取得
      //auto state = _input->GetJoypadState();
      //// ゲームを終了するかの判定
      //if (state.GetKey() & PAD_INPUT_1) {
      //  _state = State::Quit;
      //  return true;
      //}
      return flag;
    }

    bool ApplicationMain::Process() {
      return ApplicationBase::Process();
    }
  } // namespace Application
} // namespace Gyro
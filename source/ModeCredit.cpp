/*****************************************************************//**
 * @file    ModeCredit.cpp
 * @brief   モードクレジットクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "ModeCredit.h"
#include "ModeTitle.h"

namespace Gyro {
  namespace Mode {
    ModeCredit::ModeCredit(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeCredit::~ModeCredit() {

    }

    bool ModeCredit::Init() {
      return true;
    }

    bool ModeCredit::Enter() {
      // リソース読み込み
      LoadResource();
      return true;
    }

    bool ModeCredit::Exit() {
      // 変数解放
      Release();
      return true;
    }

    bool ModeCredit::Input(AppFrame::Application::InputOperation& input) {
      // 入力状態の取得
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // Bボタンが押された場合、タイトルバック
      if (device.GetButton(XINPUT_BUTTON_B, App::InputTrigger)) {
        _backTitle = true;
      }
      return true;
    }

    bool ModeCredit::Process() {
      // 入力処理
      Input(_appMain.GetOperation());
      // タイトルバックされた
      if (_backTitle) {
        // モード切り替え
        ChangeMode();
      }
      return true;
    }

    bool ModeCredit::Draw() const {
      // クレジット画像描画
      DrawGraph(0, 0, _creditHandle, false);
      return true;
    }

    void ModeCredit::Release() {
      // 変数解放
      _creditHandle = -1;
      _backTitle = false;
    }

    void ModeCredit::LoadResource() {
      // クレジット画像読み込み
      _creditHandle = LoadGraph("res/Credit/Credit.png");
    }

    void ModeCredit::ChangeMode() {
      // モードクレジットの削除
      _appMain.GetModeServer().PopBuck();
      // モードタイトル遷移
      _appMain.GetModeServer().TransionToMode("Title");
      // 鐘の音SEの再生
      _app.GetSoundComponent().PlayBackGround("bell");
    }
  } // namespace Mode
} // namespace Gyro
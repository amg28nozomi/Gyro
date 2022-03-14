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
      // 変数初期化
      _backTitle = false;
      return true;
    }

    bool ModeCredit::Exit() {
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
      DrawExtendGraph(0, 0, 1920, 1080, _creditHandle, false);
      return true;
    }

    void ModeCredit::LoadResource() {
      // リソースの読み込みは行われているか
      if (_isLoad) {
        return; // 読み込み済み
      }


      //// クレジット画像読み込み
      //_creditHandle = _app.GetResourceServer().LoadDivGraph()
      //  LoadGraph("res/Credit/Credit.png");
      //// 読み込み完了
      //_isLoad = true;
    }

    void ModeCredit::ChangeMode() {
      // モードクレジットの削除
      _appMain.GetModeServer().PopBuck();
      // モードタイトル遷移
      _appMain.GetModeServer().TransionToMode("Title");
    }
  } // namespace Mode
} // namespace Gyro
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
      // 削除予約初期化
      _popBack = false;
      return true;
    }

    bool ModeCredit::Exit() {
      // 変数解放
      _backTitle = false;
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

    void ModeCredit::LoadResource() {
      // リソースの読み込みは行われているか
      if (_isLoad) {
        return; // 読み込み済み
      }
      // 別名定義
      using ResourceServer = AppFrame::Resource::ResourceServer;
      // 画像情報の設定
      const ResourceServer::DivGraphTable divGraphMap{
        {"Credit", {"res/Credit/Credit.png", 1, 1, 1, 1920, 1080}}  // クレジット
      };
      // リソースサーバに登録
      _appMain.GetResourceServer().LoadDivGraph(divGraphMap);
      // 画像読み込み
      _creditHandle = _appMain.GetResourceServer().GetHandle("Credit");
      // 読み込み完了
      _isLoad = true;
    }

    void ModeCredit::ChangeMode() {
      // モードタイトル遷移
      _appMain.GetModeServer().TransionToMode("Title");
      // 消去予約
      _popBack = true;
      // 鐘の音SEの再生
      _app.GetSoundComponent().PlayBackGround("bell", 75);
    }
  } // namespace Mode
} // namespace Gyro
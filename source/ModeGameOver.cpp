/*****************************************************************//**
 * @file    ModeGameOver.cpp
 * @brief   モードゲームオーバークラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "ModeGameOver.h"
#include <appframe.h>
#include "ModeGame.h"
#include "ModeTitle.h"

namespace Gyro {
  namespace Mode {
    ModeGameOver::ModeGameOver(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeGameOver::~ModeGameOver() {

    }

    bool ModeGameOver::Init() {
      return true;
    }

    bool ModeGameOver::Enter() {


      // リソース読み込み
      LoadResource();
      // 変数初期化
      _retry = 0;
      _backTitle = 0;
      _decision = false;
      return true;
    }

    bool ModeGameOver::Exit() {
      return true;
    }

    bool ModeGameOver::Input(AppFrame::Application::InputOperation& input) {
      // 入力状態の取得
      auto device = input.GetXBoxState();
      auto [leftX, leftY] = device.GetStick(false);
      namespace App = AppFrame::Application;
      // 左スティック入力
      if (leftY > 100) {
        _retry = 1;
        _backTitle = 0;
      }
      else if (leftY < -100) {
        _retry = 0;
        _backTitle = 1;
      }
      // Aボタンが押された場合、選択決定
      if (device.GetButton(XINPUT_BUTTON_A, App::InputTrigger)) {
        _decision = true;
      }
      return true;
    }

    bool ModeGameOver::Process() {
      // 入力処理
      Input(_appMain.GetOperation());
      // 選択決定された
      if (_decision) {
        // モード切り替え
        ChangeMode();
      }
      return true;
    }

    bool ModeGameOver::Draw() const {
      // ポーズ描画
      DrawGraph(0, 0, _gameOverHandle, true);
      // 選択によって描画切り替え
      DrawGraph(0, 0, _retryHandle[_retry], true);
      DrawGraph(0, 0, _backTitleHandle[_backTitle], true);
      return true;
    }

    void ModeGameOver::LoadResource() {
      // リソースの読み込みは行われているか
      if (_isLoad) {
        return; // 読み込み済み
      }
      // 別名定義
      using ResourceServer = AppFrame::Resource::ResourceServer;
      const ResourceServer::DivGraphTable table = {
        { "gameover", {"res/GameOver/gameover.png", 1, 1, 1, 1920, 1080}},
        { "retry0", {"res/GameOver/retry0.png", 1, 1, 1, 1920, 1080}},
        { "retry1", {"res/GameOver/retry1.png", 1, 1, 1, 1920, 1080}},
        { "backtitle0", {"res/GameOver/backtitle0.png", 1, 1, 1, 1920, 1080}},
        { "backtitle1", {"res/GameOver/backtitle1.png", 1, 1, 1, 1920, 1080}}
      };
      // 素材の読み込み
      _app.GetResourceServer().LoadDivGraph(table);
      // 画像読み込み
      _gameOverHandle = _app.GetResourceServer().GetHandle("gameover");
      _retryHandle[0] = _app.GetResourceServer().GetHandle("retry0");
      _retryHandle[1] = _app.GetResourceServer().GetHandle("retry1");
      _backTitleHandle[0] = _app.GetResourceServer().GetHandle("backtitle0");
      _backTitleHandle[1] = _app.GetResourceServer().GetHandle("backtitle1");
      // 読み込み完了
      _isLoad = true;
    }

    void ModeGameOver::ChangeMode() {
      // モードゲームオーバーの削除
      _appMain.GetModeServer().PopBuck();
      // リトライ選択時
      if (_retry == 1) {
        // モードゲーム遷移
        _appMain.GetModeServer().TransionToMode("Game");
      }
      // タイトルバック選択時
      if (_backTitle == 1) {
        // モードタイトル遷移
        _appMain.GetModeServer().TransionToMode("Title");
      }
    }
  } // namespace Mode
} // namespace Gyro
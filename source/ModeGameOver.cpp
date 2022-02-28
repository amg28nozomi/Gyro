/*****************************************************************//**
 * @file    ModeGameOver.cpp
 * @brief   モードゲームオーバークラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "ModeGameOver.h"
#include "ModeTitle.h"

namespace Gyro {
  namespace Mode {
    ModeGameOver::ModeGameOver(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeGameOver::~ModeGameOver() {

    }

    bool ModeGameOver::Init() {
      // リソース読み込み
      LoadResource();
      return true;
    }

    bool ModeGameOver::Enter() {
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
      // 画像読み込み
      _gameOverHandle = LoadGraph("res/GameOver/gameover.png");
      _retryHandle[0] = LoadGraph("res/GameOver/retry0.png");
      _retryHandle[1] = LoadGraph("res/GameOver/retry1.png");
      _backTitleHandle[0] = LoadGraph("res/GameOver/backtitle0.png");
      _backTitleHandle[1] = LoadGraph("res/GameOver/backtitle1.png");
    }

    void ModeGameOver::ChangeMode() {
      // モードゲームオーバーの削除
      _appMain.GetModeServer().PopBuck();
      // タイトルバック選択時
      if (_backTitle == 1) {
        // モードタイトルの登録
        _appMain.GetModeServer().AddMode("Title", std::make_shared<Mode::ModeTitle>(_appMain));
        _appMain.GetModeServer().TransionToMode("Title");
      }
    }
  }
}
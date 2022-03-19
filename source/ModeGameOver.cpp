/*****************************************************************//**
 * @file    ModeGameOver.cpp
 * @brief   モードゲームオーバークラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "ModeGameOver.h"
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
      // 画像切り替え番号の初期化
      _retry = 0;
      _backTitle = 0;
      return true;
    }

    bool ModeGameOver::Exit() {
      // 変数解放
      Release();
      return true;
    }

    bool ModeGameOver::Input(AppFrame::Application::InputOperation& input) {
      // 入力状態の取得
      auto device = input.GetXBoxState();
      auto [leftX, leftY] = device.GetStick(false);
      namespace App = AppFrame::Application;
      // 左スティック上下入力
      LeftStickYInput(leftY);
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
      // ゲームオーバー描画描画
      DrawGraph(0, 0, _gameOverHandle, true);
      // 選択によって描画切り替え
      DrawGraph(0, 0, _retryHandle[_retry], true);
      DrawGraph(0, 0, _backTitleHandle[_backTitle], true);
      return true;
    }

    void ModeGameOver::Release() {
      // 変数解放
      _gameOverHandle = -1;
      _retryHandle[0] = -1;
      _retryHandle[1] = -1;
      _backTitleHandle[0] = -1;
      _backTitleHandle[1] = -1;
      _isStick = false;
      _decision = false;
    }

    void ModeGameOver::LoadResource() {
      // 画像読み込み
      _gameOverHandle = LoadGraph("res/GameOver/gameover.png");
      _retryHandle[0] = LoadGraph("res/GameOver/retry0.png");
      _retryHandle[1] = LoadGraph("res/GameOver/retry1.png");
      _backTitleHandle[0] = LoadGraph("res/GameOver/backtitle0.png");
      _backTitleHandle[1] = LoadGraph("res/GameOver/backtitle1.png");
    }

    void ModeGameOver::LeftStickYInput(const int leftY) {
      if (leftY == 0) {
        // スティック入力なし
        _isStick = false;
        return;
      }
      // 入力され続けている場合中断
      if (_isStick) {
        return;
      }
      // 入力値の正負判定
      bool flag = 0 <= leftY;
      // 画像切り替え番号の設定
      _retry = flag ? 1 : 0;
      _backTitle = flag ? 0 : 1;
      // スティック入力あり
      _isStick = true;
      // カーソルSEの再生
      _app.GetSoundComponent().PlayBackGround("cursor", 75);
    }

    void ModeGameOver::ChangeMode() {
      // モードゲームオーバーの削除
      _appMain.GetModeServer().PopBuck();
      // 鐘の音SEの再生
      _app.GetSoundComponent().PlayBackGround("bell", 75);
      // リトライ選択時
      if (_retry == 1) {
        // モードゲーム遷移
        _appMain.GetModeServer().TransionToMode("Game");
        return;
      }
      // タイトルバック選択時
      if (_backTitle == 1) {
        // モードタイトル遷移
        _appMain.GetModeServer().TransionToMode("Title");
        return;
      }
    }
  } // namespace Mode
} // namespace Gyro
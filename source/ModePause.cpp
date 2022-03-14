/*****************************************************************//**
 * @file    ModePause.cpp
 * @brief   モードポーズクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "ModePause.h"

namespace Gyro {
  namespace Mode {
    ModePause::ModePause(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModePause::~ModePause() {

    }

    bool ModePause::Init() {
      return true;
    }

    bool ModePause::Enter() {
      // リソース読み込み
      LoadResource();
      // 変数初期化
      _continue = 0;
      _quitGame = 0;
      _decision = false;
      // ポーズインSE再生
      _app.GetSoundComponent().PlayBackGround("pauseIn");
      return true;
    }

    bool ModePause::Exit() {
      return true;
    }

    bool ModePause::Input(AppFrame::Application::InputOperation& input) {
      // 入力状態の取得
      auto device = input.GetXBoxState();
      auto [leftX, leftY] = device.GetStick(false);
      namespace App = AppFrame::Application;
      // 左スティック入力
      if (0 < leftY) {
        // 上選択(コンテニュー)
        _continue = 1;
        _quitGame = 0;
      }
      else if (leftY < 0) {
        // 下選択(ゲーム終了)
        _continue = 0;
        _quitGame = 1;
      }
      // Aボタンが押された場合、選択決定
      if (device.GetButton(XINPUT_BUTTON_A, App::InputTrigger)) {
        _decision = true;
      }
      // STARTボタンが押された場合、コンテニュー
      if (device.GetButton(XINPUT_BUTTON_START, App::InputTrigger)) {
        _continue = 1;
        _quitGame = 0;
        _decision = true;
      }
      return true;
    }

    bool ModePause::Process() {
      // 入力処理
      Input(_appMain.GetOperation());
      // 選択決定された
      if (_decision) {
        // モード切り替え
        ChangeMode();
      }
      return true;
    }

    bool ModePause::Draw() const {
      // ポーズ描画
      DrawGraph(0, 0, _pauseHandle, true);
      // 選択によって描画切り替え
      DrawGraph(0, 0, _continueHandle[_continue], true);
      DrawGraph(0, 0, _quitGameHandle[_quitGame], true);
      return true;
    }

    void ModePause::LoadResource() {
      // リソースの読み込みは行われているか
      if (_isLoad) {
        return; // 読み込み済み
      }
      // 画像読み込み
      _pauseHandle = LoadGraph("res/Pause/pause.png");
      _continueHandle[0] = LoadGraph("res/Pause/continue0.png");
      _continueHandle[1] = LoadGraph("res/Pause/continue1.png");
      _quitGameHandle[0] = LoadGraph("res/Pause/quitgame0.png");
      _quitGameHandle[1] = LoadGraph("res/Pause/quitgame1.png");
      // サウンド情報の読み込み
      using SoundServer = AppFrame::Sound::SoundServer;
      const SoundServer::SoundMap soundMap{
        {"pauseIn", "res/Sound/SE/System/PauseIn.wav"},    // ポーズインSE
        {"pauseOut", "res/Sound/SE/System/PauseOut.wav"},  // ポーズアウトSE
      };
      // サウンドサーバに登録
      _appMain.GetSoundServer().AddSounds(soundMap);
      // 読み込み完了
      _isLoad = true;
    }

    void ModePause::ChangeMode() {
      // モードポーズの削除
      _appMain.GetModeServer().PopBuck();
      // ポーズ終了
      _appMain.SetGamePause(false);
      // コンティニュー選択時
      if (_continue == 1) {
        // ポーズアウトSE再生
        _app.GetSoundComponent().PlayBackGround("pauseOut");
      }
      // ゲーム終了選択時
      if (_quitGame == 1) {
        // アプリケーションの終了処理を呼び出し
        _appMain.RequestTerminate();
      }
    }
  } // namespace Mode
} // namespace Gyro
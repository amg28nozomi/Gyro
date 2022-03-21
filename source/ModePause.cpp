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
      // 画像切り替え番号の初期化
      _continue = 0;
      _quitGame = 0;
      // ポーズインSE再生
      _app.GetSoundComponent().PlayBackGround("pauseIn");
      return true;
    }

    bool ModePause::Exit() {
      // 変数解放
      _isStick = false;
      _decision = false;
      return true;
    }

    bool ModePause::Input(AppFrame::Application::InputOperation& input) {
      // 入力状態の取得
      auto device = input.GetXBoxState();
      auto [leftX, leftY] = device.GetStick(false);
      namespace App = AppFrame::Application;
      // 左スティック上下入力
      LeftStickYInput(leftY);
      // Aボタンが押された場合、選択決定
      if (device.GetButton(XINPUT_BUTTON_A, App::InputTrigger)) {
        _decision = true;
        return true;
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
      // 別名定義
      using ResourceServer = AppFrame::Resource::ResourceServer;
      // 画像情報の設定
      const ResourceServer::DivGraphTable divGraphMap{
        {"pause", {"res/Pause/pause.png", 1, 1, 1, 1920, 1080}},          // ポーズ
        {"continue0", {"res/Pause/continue0.png", 1, 1, 1, 1920, 1080}},  // コンテニュー0
        {"continue1", {"res/Pause/continue1.png", 1, 1, 1, 1920, 1080}},  // コンテニュー1
        {"quitgame0", {"res/Pause/quitgame0.png", 1, 1, 1, 1920, 1080}},  // ゲーム終了0
        {"quitgame1", {"res/Pause/quitgame1.png", 1, 1, 1, 1920, 1080}}   // ゲーム終了1
      };
      // リソースサーバに登録
      _appMain.GetResourceServer().LoadDivGraph(divGraphMap);
      // 別名定義
      using SoundServer = AppFrame::Sound::SoundServer;
      // サウンド情報の設定
      const SoundServer::SoundMap soundMap{
        {"pauseIn", "res/Sound/SE/System/PauseIn.wav"},    // ポーズインSE
        {"pauseOut", "res/Sound/SE/System/PauseOut.wav"},  // ポーズアウトSE
      };
      // サウンドサーバに登録
      _appMain.GetSoundServer().AddSounds(soundMap);
      // 画像読み込み
      _pauseHandle = _appMain.GetResourceServer().GetHandle("pause");
      _continueHandle[0] = _appMain.GetResourceServer().GetHandle("continue0");
      _continueHandle[1] = _appMain.GetResourceServer().GetHandle("continue1");
      _quitGameHandle[0] = _appMain.GetResourceServer().GetHandle("quitgame0");
      _quitGameHandle[1] = _appMain.GetResourceServer().GetHandle("quitgame1");
      // 読み込み完了
      _isLoad = true;
    }

    void ModePause::LeftStickYInput(const int leftY) {
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
      _continue = flag ? 1 : 0;
      _quitGame = flag ? 0 : 1;
      // スティック入力あり
      _isStick = true;
      // カーソルSEの再生
      _app.GetSoundComponent().PlayBackGround("cursor", 75);
    }

    void ModePause::ChangeMode() {
      // モードポーズの削除
      _appMain.GetModeServer().PopBuck();
      // ポーズ終了
      _appMain.SetGamePause(false);
      // ポーズアウトSE再生
      _app.GetSoundComponent().PlayBackGround("pauseOut");
      // ゲーム終了選択時
      if (_quitGame == 1) {
        // アプリケーションの終了処理を呼び出し
        _appMain.RequestTerminate();
      }
    }
  } // namespace Mode
} // namespace Gyro
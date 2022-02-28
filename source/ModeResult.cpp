/*****************************************************************//**
 * @file    ModeResult.cpp
 * @brief   モードリザルトクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "ModeResult.h"
#include "ModeTitle.h"

namespace {
  constexpr int BgmVolume = 50;  //!< BGMの再生ボリューム
}

namespace Gyro {
  namespace Mode {
    ModeResult::ModeResult(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeResult::~ModeResult() {

    }

    bool ModeResult::Init() {
      // リソース読み込み
      LoadResource();
      // スタジオ初期化
      _studio = std::make_unique<Studio::Studio>(_appMain);
      _studio->Init();
      return true;
    }

    bool ModeResult::Enter() {
      // BGMの再生開始
      _appMain.GetSoundComponent().PlayLoop("result");
      // 再生音量の設定
      _appMain.GetSoundComponent().SetVolume("result", BgmVolume);
      return true;
    }

    bool ModeResult::Exit() {
      // カメラの初期化
      _appMain.GetCamera().Init();
      // スタジオ解放
      _studio->Release();
      return true;
    }

    bool ModeResult::Input(AppFrame::Application::InputOperation& input) {
      // 入力状態の取得
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // Bボタンが押された場合、タイトルバック
      if (device.GetButton(XINPUT_BUTTON_B, App::InputTrigger)) {
        _backTitle = true;
        // ジャイロアニメ変更
        _studio->GyroChangeAnim("GyroExciteTrickActive");
      }
      return true;
    }

    bool ModeResult::Process() {
      // 入力処理
      Input(_appMain.GetOperation());
      // スタジオ更新
      _studio->Process();
      // タイトルバックされた
      if (_backTitle) {
        // ジャイロのアニメーションが終わったら
        if (_studio->IsGyroAnimEnd()) {
          // モード切り替え
          ChangeMode();
        }
      }
      return true;
    }

    bool ModeResult::Draw() const {
      // スタジオ描画
      _studio->Draw();
      // リザルト描画
      DrawGraph(0, 0, _resultHandle, true);
      return true;
    }

    void ModeResult::LoadResource() {
      // 画像読み込み
      _resultHandle = LoadGraph("res/Result/result.png");
      // サウンド情報の読み込み
      using SoundServer = AppFrame::Sound::SoundServer;
      const SoundServer::SoundMap soundMap{
        {"result", "res/Sound/Result.mp3"}  // リザルト
      };
      // サウンドサーバに登録
      _appMain.GetSoundServer().AddSounds(soundMap);
    }

    void ModeResult::ChangeMode() {
      // モードリザルトの削除
      _appMain.GetModeServer().PopBuck();
      // モードタイトルの登録
      _appMain.GetModeServer().AddMode("Title", std::make_shared<Mode::ModeTitle>(_appMain));
      _appMain.GetModeServer().TransionToMode("Title");
      // BGMの再生を停止する
      _appMain.GetSoundComponent().StopSound("result");
    }
  }
}
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
  constexpr int BGMVolume = 50;  //!< BGMの再生ボリューム
}

namespace Gyro {
  namespace Mode {
    ModeResult::ModeResult(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeResult::~ModeResult() {

    }

    bool ModeResult::Init() {
      // スタジオ生成
      _studio = std::make_unique<Studio::Studio>(_appMain);
      return true;
    }

    bool ModeResult::Enter() {
      // リソース読み込み
      LoadResource();
      // スタジオ初期化
      _studio->Init();
      // BGMの再生開始
      PlayBgm("result", BGMVolume);
      return true;
    }

    bool ModeResult::Exit() {
      // 変数解放
      _backTitle = false;
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
      // リソースの読み込みは行われているか
      if (_isLoad) {
        return; // 読み込み済み
      }
      // 別名定義
      using ResourceServer = AppFrame::Resource::ResourceServer;
      // 画像情報の設定
      const ResourceServer::DivGraphTable divGraphMap{
        {"result", {"res/Result/result.png", 1, 1, 1, 1920, 1080}}  // ポーズ
      };
      // リソースサーバに登録
      _appMain.GetResourceServer().LoadDivGraph(divGraphMap);
      // 別名定義
      using SoundServer = AppFrame::Sound::SoundServer;
      // サウンド情報の設定
      const SoundServer::SoundMap soundMap{
        {"result", "res/Sound/BGM/Result.mp3"}  // リザルト
      };
      // サウンドサーバに登録
      _appMain.GetSoundServer().AddSounds(soundMap);
      // 画像読み込み
      _resultHandle = _appMain.GetResourceServer().GetHandle("result");
      // 読み込み完了
      _isLoad = true;
    }

    void ModeResult::ChangeMode() {
      // モードリザルトの削除
      _appMain.GetModeServer().PopBuck();
      // 鐘の音SEの再生
      _appMain.GetSoundComponent().PlayBackGround("bell", 75);
      // モードタイトル遷移
      _appMain.GetModeServer().TransionToMode("Title");
      // リザルトBGMの再生を停止する
      _appMain.GetSoundComponent().StopSound("result");
    }
  } // namespace Mode
} // namespace Gyro
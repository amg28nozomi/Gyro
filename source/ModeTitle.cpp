/*****************************************************************//**
 * @file    ModeTitle.cpp
 * @brief   モードタイトルクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "ModeTitle.h"
#include "UtilityDX.h"
#include "ModeGame.h"

namespace {
  constexpr int BgmVolume = 50;  //!< BGMの再生ボリューム
}

namespace Gyro {
  namespace Mode {
    ModeTitle::ModeTitle(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeTitle::~ModeTitle() {

    }

    bool ModeTitle::Init() {
      // リソース読み込み
      LoadResource();
      // スタジオ初期化
      _studio = std::make_unique<Studio::Studio>(_appMain);
      _studio->Init();
      return true;
    }

    bool ModeTitle::Enter() {
      // BGMの再生開始
      _appMain.GetSoundComponent().PlayLoop("title");
      // 再生音量の設定
      _appMain.GetSoundComponent().SetVolume("title", BgmVolume);
      return true;
    }

    bool ModeTitle::Exit() {
      // カメラの初期化
      _appMain.GetCamera().Init();
      // スタジオ解放
      _studio->Release();
      return true;
    }

    bool ModeTitle::Input(AppFrame::Application::InputOperation& input) {
      // 入力状態の取得
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // Aボタンが押された場合、ゲーム開始
      if (device.GetButton(XINPUT_BUTTON_A, App::InputTrigger)) {
        if (_start == false) {
          _start = true;
          // ジャイロアニメ変更
          _studio->GyroChangeAnim("GyroExciteTrickActive");
        }
      }
      return true;
    }

    bool ModeTitle::Process() {
      // 入力処理
      Input(_appMain.GetOperation());
      // スタジオ更新
      _studio->Process();
      // ゲーム開始された
      if (_start) {
        // ジャイロのアニメーションが終わったら
        if (_studio->IsGyroAnimEnd()) {
          // モード切り替え
          ChangeMode();
        }
      }
      return true;
    }

    bool ModeTitle::Draw() const {
      // スタジオ描画
      _studio->Draw();
      // タイトル描画
      DrawRotaGraph(720, 400, 0.75, 0, _titleHandle, true);
      return true;
    }

    void ModeTitle::LoadResource() {
      // タイトル読み込み
      _titleHandle = LoadGraph("res/Title/GYROtitle.png");
      // 各種モデルハンドルの読み込み
      using ModelServer = AppFrame::Model::ModelServer;
      const ModelServer::ModelDatas mv1Models{
        {"studio", "res/Stage/Studio_GEO.mv1"},          // スタジオ
        {"player", "res/Player/Gyro Multimotion8.mv1"},  // 自機(ジャイロ)
        {"sky", "res/SkySphere/skysphere.mv1"},          // スカイスフィア
      };
      // モデルサーバで読み取りを行う
      _appMain.GetModelServer().AddMV1Model(mv1Models);
      // サウンド情報の読み込み
      using SoundServer = AppFrame::Sound::SoundServer;
      const SoundServer::SoundMap soundMap{
        {"title", "res/Sound/Title.mp3"}  // タイトル
      };
      // サウンドサーバに登録
      _appMain.GetSoundServer().AddSounds(soundMap);
    }

    void ModeTitle::ChangeMode() {
      // モードタイトルの削除
      _appMain.GetModeServer().PopBuck();
      // モードゲームの登録
      _appMain.GetModeServer().AddMode("Game", std::make_shared<Mode::ModeGame>(_appMain));
      _appMain.GetModeServer().TransionToMode("Game");
      // BGMの再生を停止する
      _appMain.GetSoundComponent().StopSound("title");
    }
  }
}
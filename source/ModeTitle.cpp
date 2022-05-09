/*****************************************************************//**
 * @file    ModeTitle.cpp
 * @brief   モードタイトルクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeCredit.h"
#include "ModeLoading.h"

namespace {
  constexpr int BGMVolume = 50;  //!< BGMの再生ボリューム
  // 場面切り替え定数
  constexpr int PressAnyButtonNum = 0;  //!< プレスボタン
  constexpr int GameStartNum = 1;       //!< ゲーム開始
  constexpr int CreditNum = 2;          //!< クレジット
  constexpr int QuitGameNum = 3;        //!< ゲーム終了
}

namespace Gyro {
  namespace Mode {
    ModeTitle::ModeTitle(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeTitle::~ModeTitle() {

    }

    bool ModeTitle::Init() {
      // スタジオ生成
      _studio = std::make_unique<Studio::Studio>(_appMain);
      return true;
    }

    bool ModeTitle::Enter() {
      // リソース読み込み
      LoadResource();
      // 場面番号初期化
      _sceneNum = 0;
      // スタジオ初期化
      _studio->Init();
      // タイトルBGMの再生開始
      PlayBgm("title", BGMVolume);
      return true;
    }

    bool ModeTitle::Exit() {
      // 変数解放
      _gameStartExRate = 1.0f;
      _creditExRate = 1.0f;
      _quitGameExRate = 1.0f;
      _isStick = false;
      _decision = false;
      // スタジオ解放
      _studio->Release();
      return true;
    }

    bool ModeTitle::Input(AppFrame::Application::InputOperation& input) {
      // 入力状態の取得
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // 場面番号がプレスボタン
      if (_sceneNum == PressAnyButtonNum) {
        // 何らかのボタンが押されたら画面切り替え
        if (device.InputAnyButton()) {
          _sceneNum = GameStartNum;
        }
        return true;
      }
      // 選択未決定
      if (!_decision) {
        auto [leftX, leftY] = device.GetStick(false);
        // 左スティック上下入力
        LeftStickYInput(leftY);
        // Aボタンが押された場合、選択決定
        if (device.GetButton(XINPUT_BUTTON_A, App::InputTrigger)) {
          // 場面番号がゲーム終了
          if (_sceneNum == QuitGameNum) {
            // アプリケーションの終了処理を呼び出し
            _appMain.RequestTerminate();
            // 選択決定
            _decision = true;
            return true;
          }
          // 選択決定
          _decision = true;
          // スタートSE再生
          _app.GetSoundComponent().PlayBackGround("bell", 75);
          // ジャイロアニメ変更
          _studio->GyroChangeAnim("Gyro_Title_Start");
        }
      }
      return true;
    }

    bool ModeTitle::Process() {
      // モード削除予約判定
      PopBack();
      // 入力処理
      Input(_appMain.GetOperation());
      // 拡大率設定
      SetExRate();
      // スタジオ更新
      _studio->Process();
      // 選択決定された
      if (_decision) {
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
      DrawRotaGraph(700, 400, 0.75, 0, _titleHandle, true);
      // 場面による切り替え
      if (_sceneNum == PressAnyButtonNum) {
        DrawRotaGraph(650, 800, 1.0, 0, _pressButtonHandle, true);
      }
      else {
        DrawRotaGraph(650, 750, _gameStartExRate, 0, _gameStartHandle, true);
        DrawRotaGraph(650, 850, _creditExRate, 0, _creditHandle, true);
        DrawRotaGraph(650, 950, _quitGameExRate, 0, _quitGameHandle, true);
      }
      return true;
    }

    void ModeTitle::LoadResource() {
      // リソースの読み込みは行われているか
      if (_isLoad) {
        return; // 読み込み済み
      }
      // 別名定義
      using ResourceServer = AppFrame::Resource::ResourceServer;
      // 画像情報の設定
      const ResourceServer::DivGraphTable divGraphMap{
        {"title", {"res/Title/GYROtitle.png", 1, 1, 1, 1920, 1080}},  // タイトル
        {"press", {"res/Title/pressbutton.png", 1, 1, 1, 721, 86}},   // プレスボタン
        {"start", {"res/Title/gamestart.png", 1, 1, 1, 379, 73}},     // ゲーム開始
        {"credit", {"res/Title/credit.png", 1, 1, 1, 219, 73}},       // クレジット
        {"quitgame", {"res/Title/quitgame.png", 1, 1, 1, 336, 85}}    // ゲーム終了
      };
      // リソースサーバに登録
      _appMain.GetResourceServer().LoadDivGraph(divGraphMap);
      // 別名定義
      using ModelServer = AppFrame::Model::ModelServer;
      // 各種モデルハンドルの読み込み
      const ModelServer::ModelDatas mv1Models{
        {"studio", "res/Stage/Studio_GEO.mv1"},           // スタジオ
        {"player", "res/Player/Gyro Multimotion10.mv1"},  // 自機(ジャイロ)
        {"sky", "res/SkySphere/skysphere.mv1"},           // スカイスフィア
      };
      // モデルサーバで読み取りを行う
      _appMain.GetModelServer().AddMV1Model(mv1Models);
      // 別名定義
      using SoundServer = AppFrame::Sound::SoundServer;
      // サウンド情報の読み込み
      const SoundServer::SoundMap soundMap{
        {"title", "res/Sound/BGM/Title.mp3"},  // タイトルBGM
        {"cursor", "res/Sound/SE/System/Cursor1.wav"},  // カーソルSE
        {"bell", "res/Sound/SE/System/TitleStart.wav"}  // 鐘の音SE
      };
      // サウンドサーバに登録
      _appMain.GetSoundServer().AddSounds(soundMap);
      // 画像読み込み
      _titleHandle = _appMain.GetResourceServer().GetHandle("title");
      _pressButtonHandle = _appMain.GetResourceServer().GetHandle("press");
      _gameStartHandle = _appMain.GetResourceServer().GetHandle("start");
      _creditHandle = _appMain.GetResourceServer().GetHandle("credit");
      _quitGameHandle = _appMain.GetResourceServer().GetHandle("quitgame");
      // 読み込み完了
      _isLoad = true;
    }

    void ModeTitle::LeftStickYInput(const int leftY) {
      if (leftY == 0) {
        // スティック入力なし
        _isStick = false;
        return;
      }
      // スティック入力されたままの場合中断
      if (_isStick) {
        return;
      }
      // 入力値の正負判定
      bool flag = 0 <= leftY;
      if (flag) {
        // 下限判定
        if (GameStartNum < _sceneNum) {
          // 場面番号を1減らす
          _sceneNum--;
        }
      } else {
        // 上限判定
        if (_sceneNum < QuitGameNum) {
          // 場面番号を1増やす
          _sceneNum++;
        }
      }
      // スティック入力あり
      _isStick = true;
      // カーソルSEの再生
      _app.GetSoundComponent().PlayBackGround("cursor", 75);
    }

    void ModeTitle::SetExRate() {
      // 拡大率初期化
      _gameStartExRate = 1.0f;
      _creditExRate = 1.0f;
      _quitGameExRate = 1.0f;
      // 場面番号の判定
      bool num1 = _sceneNum == GameStartNum;
      bool num2 = _sceneNum == CreditNum;
      bool num3 = _sceneNum == QuitGameNum;
      // 場面番号判定による拡大
      _gameStartExRate = num1 ? 1.25f : 1.0f;
      _creditExRate = num2 ? 1.25f : 1.0f;
      _quitGameExRate = num3 ? 1.25f : 1.0f;
    }

    void ModeTitle::ChangeMode() {
      if (_sceneNum == GameStartNum) {
        // インゲーム遷移
        InGame();
      }
      if (_sceneNum == CreditNum) {
        // クレジット遷移
        Credit();
      }
      // BGMの再生を停止する
      _appMain.GetSoundComponent().StopSound("title");
    }

    void ModeTitle::InGame() {
      // キーが登録されているか
      bool key = _app.GetModeServer().Contains("Game");
      if (!key) {
        if (GetASyncLoadNum() > 0) {
          // モードローディングの登録
          _appMain.GetModeServer().AddMode("Loading", std::make_shared<Mode::ModeLoading>(_appMain));
        }
        else {
          // 非同期処理フラグfalse
          SetUseASyncLoadFlag(false);
          // モードゲームの登録
          _appMain.GetModeServer().AddMode("Game", std::make_shared<Mode::ModeGame>(_appMain));
        }
      }
      // モードゲーム遷移
      _appMain.GetModeServer().TransionToMode("Game");
      // 消去予約
      _popBack = true;
    }

    void ModeTitle::Credit() {
      // キーが登録されているか
      bool key = _app.GetModeServer().Contains("Credit");
      if (!key) {
        // モードクレジットの登録
        _appMain.GetModeServer().AddMode("Credit", std::make_shared<Mode::ModeCredit>(_appMain));
      }
      // モードクレジット遷移
      _appMain.GetModeServer().TransionToMode("Credit");
      // 消去予約
      _popBack = true;
    }
  } // namespace Mode
} // namespace Gyro
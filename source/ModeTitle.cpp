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
#include "ModeCredit.h"
#include "ModeLoading.h"

namespace {
  constexpr int BgmVolume = 50;      //!< BGMの再生ボリューム
  // 場面切り替え定数
  constexpr int PressAnyButtonNum = 0;  //!< プレスボタン
  constexpr int GameStartNum = 1;       //!< ゲーム開始
  //constexpr int CreditNum = 2;          //!< クレジット
  constexpr int QuitGameNum = 2;        //!< ゲーム終了
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
      // 変数初期化
      _sceneNum = PressAnyButtonNum;
      _isStick = false;
      _decision = false;
      // スタジオ初期化
      _studio->Init();
      // BGMの再生開始
      _appMain.GetSoundComponent().PlayLoop("title");
      // 再生音量の設定
      _appMain.GetSoundComponent().SetVolume("title", BgmVolume);
      return true;
    }

    bool ModeTitle::Exit() {
      // スタジオ解放
      _studio->Release();
      return true;
    }

    bool ModeTitle::Input(AppFrame::Application::InputOperation& input) {
      // 入力状態の取得
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // 場面判定
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
          if (_sceneNum == QuitGameNum) {
            // 場面番号がゲーム終了
            // アプリケーションの終了処理を呼び出し
            _appMain.RequestTerminate();
            return true;
          }
          // 選択決定
          _decision = true;
          // スタートSE再生
          _app.GetSoundComponent().PlayBackGround("start", 50);
          // ジャイロアニメ変更
          _studio->GyroChangeAnim("Gyro_Title_Start");
        }
      }
      return true;
    }

    bool ModeTitle::Process() {
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
        //DrawRotaGraph(650, 850, _creditExRate, 0, _creditHandle, true);
        DrawRotaGraph(650, 950, _quitGameExRate, 0, _quitGameHandle, true);
      }
      return true;
    }

    void ModeTitle::LoadResource() {
      // リソースの読み込みは行われているか
      if (_isLoad) {
        return; // 読み込み済み
      }
      // 画像読み込み
      _titleHandle = LoadGraph("res/Title/GYROtitle.png");
      _pressButtonHandle = LoadGraph("res/Title/pressbutton.png");
      _gameStartHandle = LoadGraph("res/Title/gamestart.png");
      _creditHandle = LoadGraph("res/Title/credit.png");
      _quitGameHandle = LoadGraph("res/Title/quitgame.png");
      // 各種モデルハンドルの読み込み
      using ModelServer = AppFrame::Model::ModelServer;
      const ModelServer::ModelDatas mv1Models{
        {"studio", "res/Stage/Studio_GEO.mv1"},           // スタジオ
        {"player", "res/Player/Gyro Multimotion10.mv1"},  // 自機(ジャイロ)
        {"sky", "res/SkySphere/skysphere.mv1"},           // スカイスフィア
      };
      // モデルサーバで読み取りを行う
      _appMain.GetModelServer().AddMV1Model(mv1Models);
      // サウンド情報の読み込み
      using SoundServer = AppFrame::Sound::SoundServer;
      const SoundServer::SoundMap soundMap{
        {"title", "res/Sound/BGM/Title.mp3"},  // タイトルBGM
        {"cursor", "res/Sound/SE/System/Cursor1.wav"},   // カーソルSE
        {"start", "res/Sound/SE/System/TitleStart.wav"}  // スタートSE
      };
      // サウンドサーバに登録
      _appMain.GetSoundServer().AddSounds(soundMap);
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
      if (0 < leftY) {
        // スティック上入力あり
        _isStick = true;
        // カーソルSE再生
        _app.GetSoundComponent().PlayBackGround("cursor", 50);
        // 場面番号を1減らす
        _sceneNum--;
        if (_sceneNum < GameStartNum) {
          // 下限調整
          _sceneNum = GameStartNum;
        }
      }
      else if (leftY < 0) {
        // スティック下入力あり
        _isStick = true;
        // カーソルSE再生
        _app.GetSoundComponent().PlayBackGround("cursor", 50);
        // 場面番号を1増やす
        _sceneNum++;
        if (QuitGameNum < _sceneNum) {
          // 上限調整
          _sceneNum = QuitGameNum;
        }
      }
    }

    void ModeTitle::SetExRate() {
      // 拡大率初期化
      _gameStartExRate = 1.0f;
      _creditExRate = 1.0f;
      _quitGameExRate = 1.0f;
      // 場面による切り替え
      switch (_sceneNum) {
      case GameStartNum:
        // ゲーム開始拡大
        _gameStartExRate = 1.25f;
        break;
      //case CreditNum:
      //  // クレジット拡大
      //  _creditExRate = 1.25f;
      //  break;
      case QuitGameNum:
        // ゲーム終了拡大
        _quitGameExRate = 1.25f;
        break;
      default:
        break;
      }
    }

    void ModeTitle::ChangeMode() {
      // モードタイトルの削除
      _appMain.GetModeServer().PopBuck();
      if (_sceneNum == GameStartNum) {
        // インゲーム遷移
        InGame();
      }
      //else if (_sceneNum == CreditNum) {
      //  // クレジット遷移
      //  Credit();
      //}
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
    }
  } // namespace Mode
} // namespace Gyro
/*****************************************************************//**
 * @file   ApplicationBase.cpp
 * @brief  アプリケーションのスーパークラスの定義
 * 
 * @author 鈴木希海
 * @date   December 2021
 *********************************************************************/
#include "ApplicationBase.h"
#include <string>
#include <algorithm>
#ifdef _DEBUG
#include <stdexcept>
#endif
#include <unordered_map>
#include "InputOperation.h"
#include "../FileServer/FileServer.h"
#include "../FileServer/FileBase.h"
#include "../Mode/ModeBase.h"
#include "../Mode/ModeFadeIn.h"
#include "../Resource/ResourceServer.h"
#include "../Model/ModelServer.h"

namespace {
  constexpr auto InitError = -1;   // 初期化失敗
} // namespace

namespace AppFrame {
  namespace Application {

    /**
     * @brief ウィンドウ情報をキーとして、画面サイズ情報をpair型で保持する連想配列
     */
    const std::unordered_map<ApplicationBase::WindowType, std::pair<int, int>> WindowMap{
      // デフォルトの画面サイズ情報
      {ApplicationBase::WindowType::Default, {1920, 1080}}
    };

    ApplicationBase::ApplicationBase() {
      _particleMax = 4000;
#ifndef _DEBUG
      _windowMode = false;
#else
      _windowMode = true;
#endif
    }

    ApplicationBase::~ApplicationBase() {
    }

    bool ApplicationBase::SetInstance() {
      // 実体が登録されているかの判定
      if (!_setInstance) {
        if (_instance == nullptr) {
          _setInstance = true;
          return true; // 登録を行う
        }
      }
      return false; // 登録済み
    }

    bool ApplicationBase::Init() {
      // ログファイルの出力を行うかの設定
      SetOutApplicationLogValidFlag(_windowMode);
      // 画面モードの設定
      SetWindowSize(_windowType);
      // ウィンドウモードの設定
      ChangeWindowMode(_windowMode);
      // DXライブラリの初期化
      if (DxLib::DxLib_Init() == InitError) {
#ifdef _DEBUG
        throw std::logic_error("ApplicationBase:DXライブラリの初期化に失敗しました\n");
#endif
        return false; // 初期化失敗
      }
      // 背景色の設定
      SetBackgroundColor(0, 0, 255);
      SetDrawScreen(DX_SCREEN_BACK);
      // Zバッファの設定
      SetZBuffer();
      // ファイルサーバの生成
      _fileServer = std::make_unique<FileServer::FileServer>(*this);
      // インプットオペレーションの生成
      _input = std::make_unique<InputOperation>(*this);
      // モードサーバの生成
      _modeServer = std::make_unique<Mode::ModeServer>(*this);
      // リソースサーバの生成
      _resourceServer = std::make_unique<Resource::ResourceServer>();
      // サウンドサーバの生成
      _soundServer = std::make_unique<Sound::SoundServer>();
      // サウンドコンポーネントの生成
      _soundComponent = std::make_unique<Sound::SoundComponent>(*this);
      // モデルサーバの生成
      _modelServer = std::make_unique<Model::ModelServer>();
#ifndef _DEBUG
      if (!_fileServer->Init()) {
        return false; // 初期化失敗
      }
#else
      try {
        // ファイルサーバの初期化
        // 初期化に失敗した場合は対応したエラーを発射
        _fileServer->Init();
      }
      catch (std::logic_error error) {
        OutputDebugString(error.what());
        return false; // 初期化失敗
      }
#endif
      // モデルサーバ初期化
      _modelServer->Init();
      return true; // 初期化成功
    }

    void ApplicationBase::Release() {
      DxLib_End();
    }

    void ApplicationBase::Run() {
      // メインループ
      while (_state != State::Quit) {
#ifndef _DEBUG
        Input();   // 入力
        Process(); // 更新
        Draw();    // 描画
#else
        try {
          Input();   // 入力
          Process(); // 更新
          Draw();    // 描画
        } catch (std::logic_error error) {
          // 例外発生時、出力を行う
          OutputDebugString(error.what());
        }
#endif
      }
    }

    bool ApplicationBase::Input() {
      IsQuit();          // 終了判定
      _input->Process(); // 入力状態の更新
      return true;
    }

    bool ApplicationBase::Process() {
      // モードサーバの更新処理を実行
      _modeServer->Process();
      return true;
    }

    bool ApplicationBase::Draw() {
      ClearDrawScreen();   // 画面をクリア
      _modeServer->Draw(); // モードサーバの描画処理実行
      ScreenFlip();        // 裏画面の内容を表画面に反映
      return true;
    }

    void ApplicationBase::Terminate() {
      // DXライブラリの終了
      DxLib_End();
    }

    void ApplicationBase::RequestTerminate() {
      // アプリケーションが終了状態ではない場合
      if (_state != State::Quit) {
        _state = State::Quit;
      }
    }

    void ApplicationBase::SetWindowSize(const WindowType& window, bool bit) {
      // 画面サイズの取得
      auto [width, height] = WindowSize();
      // 取得したサイズ情報を登録する
      _width = width;
      _height = height;
      // カラービット数の設定
      _colorBit = ColorBit(bit);
      // 画面モードの変更
      SetGraphMode(_width, _height, _colorBit);
    }

    int ApplicationBase::ColorBit(const bool bit) const {
      // bitフラグに応じた値を返す
      if (bit) {
        return BitColor32;
      }
      return BitColor16;
    }

    std::pair<int, int> ApplicationBase::WindowSize() const {
      // 現在のウィンドウタイプに対応する画面サイズを返す
      return WindowMap.at(_windowType);
    }

    void ApplicationBase::SetZBuffer(bool flag) {
      // Zバッファを使用するかの設定
      SetUseZBuffer3D(flag);
      SetWriteZBuffer3D(flag);
    }

    void ApplicationBase::IsQuit() {
      // メッセージループに失敗した場合は終了
      if (ProcessMessage() == Error) {
        _state = State::Quit; // 終了状態に遷移
      }
    }

    Resource::ResourceServer& ApplicationBase::GetResourceServer() {
      return *_resourceServer;
    }

    Sound::SoundComponent& ApplicationBase::GetSoundComponent() {
      return *_soundComponent;
    }

    Model::ModelServer& ApplicationBase::GetModelServer() const {
      return *_modelServer;
    }
  } // namespace Application
} // namespace AppFrame
/*****************************************************************//**
 * @file   ApplicationMain.cpp
 * @brief  アプリケーションベースのサブクラスの定義
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ApplicationMain.h"
#include "appframe.h"
#include <DxLib.h>
#include "ObjectServer.h"
#include "ModeAMG.h"
#include "ModeGame.h"
#include "SpawnServer.h"
#include "StageTransition.h"
#include "StageComponent.h"

namespace Gyro {
  namespace Application {
      // アプリケーションの実体
      ApplicationMain application;

      ApplicationMain::ApplicationMain() : ApplicationBase() {
        // 実体の登録を行うか
        if (SetInstance()) {
          // 実体作成
          _instance = std::make_shared<ApplicationMain>();
        }
      }

      bool ApplicationMain::Init() {
        if (!ApplicationBase::Init()) {
          return false; // 初期化失敗
        }
        // Effekseerの設定
        if (!Effekseer()) {
          return false; // 設定失敗
        }
        // オブジェクトサーバの生成
        _objectServer = std::make_unique<Object::ObjectServer>();
        _objectServer->Init();
        // スポーンサーバの生成
        _spawnServer = std::make_unique<Object::SpawnServer>(*this);
        _spawnServer->Init();
        // カメラの生成
        _camera = std::make_unique<Camera::Camera>();
        _camera->Init();
        // エフェクト読み込みサーバの生成
        _effectLoadServer = std::make_unique<Effect::EffectLoadServer>();
        // エフェクトサーバの生成
        _effectServer = std::make_unique<Effect::EffectServer>(*this);
        // ステージコンポーネントの生成
        _stage = std::make_unique<Stage::StageComponent>(*this);
        // ステージ遷移マネージャーの生成
        _stageTransition = std::make_unique<Stage::StageTransition>(*this);
        _stageTransition->Init();
        // モードゲームの登録
        _modeServer->AddMode("AMG", std::make_shared<Mode::ModeAMG>(*this));
        _modeServer->PushBack("AMG");
        return true;
      }

      bool ApplicationMain::Input() {
        auto flag = ApplicationBase::Input();
        return flag;
      }

      void ApplicationMain::Terminate() {
        // Effekseerを終了する。
        Effkseer_End();
      }

      bool ApplicationMain::Process() {
        return ApplicationBase::Process();
      }

      bool ApplicationMain::IsGameOver() const {
        // モードゲームの取得
        auto game = _modeServer->GetMode("Game");
        // 取得に失敗
        if (game == nullptr) {
          return false; // 取得失敗
        }
        // ゲームオーバー状態かの判定を行う
        return std::dynamic_pointer_cast<Mode::ModeGame>(game)->IsGameOver();
      }

      void ApplicationMain::GameOver() {
        // モードゲームの取得
        auto game = _modeServer->GetMode("Game");
        // 取得に失敗
        if (game == nullptr) {
          return; // 取得失敗
        }
        // ゲームオーバー状態に遷移する
        std::dynamic_pointer_cast<Mode::ModeGame>(game)->ToGameOver();
      }

      bool ApplicationMain::Effekseer() {
        //DirectX11を使用
        SetUseDirect3DVersion(DX_DIRECT3D_11);
        //Effekseerの初期化
        //引数には画面に表示する最大パーティクル数を設定
        if (Effekseer_Init(8000) == -1) {
            return false;
        }
        //フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ
        SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
        //DXライブラリのデバイスロストした時のコールバックを設定
        Effekseer_SetGraphicsDeviceLostCallbackFunctions();
        return true;
      }

      void ApplicationMain::IsQuit() {
        // 通常の終了判定
        ApplicationBase::IsQuit();
        // キーボードでの終了判定を行う
        auto keyboard = _input->GetKeyboardState();
        auto isEnd = keyboard.GetEscapeKey(false);
        // ゲームを終了するかの判定
        if (isEnd) {
          // 終了する
          _state = State::Quit;
        }
      }
  } // namespace Application
} // namespace Gyro
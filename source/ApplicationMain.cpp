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
#include "SpawnServer.h"
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
            // モードゲームの登録
            _modeServer->AddMode("AMG", std::make_shared<Mode::ModeAMG>(*this));
            _modeServer->TransionToMode("AMG");
            return true;
        }

        bool ApplicationMain::Input() {
            auto flag = ApplicationBase::Input();
            // 入力状態の取得
            //auto state = _input->GetJoypadState();
            //// ゲームを終了するかの判定
            //if (state.GetKey() & PAD_INPUT_1) {
            //  _state = State::Quit;
            //  return true;
            //}
            return flag;
        }

        void ApplicationMain::Terminate() {
            // Effekseerを終了する。
            Effkseer_End();
        }

        bool ApplicationMain::Process() {
            return ApplicationBase::Process();
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
    } // namespace Application
} // namespace Gyro
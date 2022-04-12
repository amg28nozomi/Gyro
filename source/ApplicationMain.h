/*****************************************************************//**
 * @file   ApplicationMain.h
 * @brief  アプリケーションベースのサブクラス
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include <EffekseerForDXLib.h>
#include "Camera.h"
#include "EffectLoadServer.h"
#include "EffectServer.h"

 /**
  * @brief ゲームスペース
  */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    // 前方宣言
    class ObjectServer; //!< オブジェクトサーバ
    class SpawnServer;  //!< スポーンサーバ
  } // namespace Object
  /**
   * @brief ステージベース
   */
  namespace Stage {
    class StageComponent;
    class StageTransition;
  } // namespace Stage
  /**
   * @brief エフェクトベース
   */
  namespace Effect {
    // 前方宣言
    class EffectLoadServer;  //!< エフェクトサーバ
    class EffectServer;   //!< エフェクト
  } // namespace Effect
  /**
   * @brief アプリケーション
   */
  namespace Application {
    /**
     * @class ApplicationMain
     * @brief アプリケーションメイン
     */
    class ApplicationMain : public AppFrame::Application::ApplicationBase {
    public:
      /**
       * @brief  コンストラクタ
       */
      ApplicationMain();
      /**
       * @brief  初期化
       * @return true:初期化成功 false:初期化失敗
       */
      bool Init() override;
      /**
       * @brief  入力処理
       * @return
       */
      bool Input() override;
      /**
       * @brief  終了処理
       */
      void Terminate() override;
      /**
       * @brief  ゲームオーバーフラグセット
       * @param  flag フラグ
       */
      void SetGameOver(const bool flag) {
        _gameOver = flag;
      }
      /**
       * @brief  ゲームクリアフラグセット
       * @param  flag フラグ
       */
      void SetGameClear(const bool flag) {
        _gameClear = flag;
      }
      /**
       * @brief  ゲームポーズフラグセット
       * @param  flag フラグ
       */
      void SetGamePause(const bool flag) {
        _gamePause = flag;
      }
      /**
       * @brief  フレームカウンタの取得
       * @return フレームカウンタ
       */
      const int GetFrameCount() const override {
        return 0;
      }
      /**
       * @brief  ゲームオーバー状態かの判定
       * @return true:ゲームオーバー false:ゲームオーバーではない
       */
      bool IsGameOver() const;
      /**
       * @brief  ゲームオーバーの呼び出し
       */
      void GameOver();
      /**
       * @brief  ゲームオーバーフラグの取得
       * @return ゲームオーバーフラグ
       */
      //bool GetGameOver() {
      //  return _gameOver;
      //}
      /**
       * @brief  ゲームクリアフラグの取得
       * @return ゲームクリアフラグ
       */
      bool GetGameClear() {
        return _gameClear;
      }
      /**
       * @brief  ゲームポーズフラグの取得
       * @return ゲームポーズフラグ
       */
      bool GetGamePause() {
        return _gamePause;
      }
      /**
       * @brief  オブジェクトサーバの取得
       * @return オブジェクトサーバの参照
       */
      Object::ObjectServer& GetObjectServer() {
        return *_objectServer;
      }
      /**
       * @brief  スポーンサーバの取得
       * @return スポーンサーバの参照
       */
      Object::SpawnServer& GetSpawnServer() {
        return *_spawnServer;
      }
      /**
       * @brief  カメラの取得
       * @return カメラの参照
       */
      Camera::Camera& GetCamera() {
        return *_camera;
      }
      /**
       * @brief  エフェクト読み込みサーバの取得
       * @return エフェクト読み込みサーバの参照
       */
      Effect::EffectLoadServer& GetEffectLoadServer() {
        return *_effectLoadServer;
      }
      /**
       * @brief  エフェクトサーバの取得
       * @return エフェクトサーバの参照
       */
      Effect::EffectServer& GetEffectServer() {
        return *_effectServer;
      }
      /**
       * @brief  ステージコンポーネントの取得
       * @return ステージコンポーネントの参照
       */
      Stage::StageComponent& GetStageComponent() const {
        return *_stage;
      }
      /**
       * @brief  ステージ遷移マネージャーの取得
       * @return ステージ遷移マネージャーの参照
       */
      Stage::StageTransition& GetStageTransition() const {
        return *_stageTransition;
      }
    private:
      bool _gameOver{ false };      //!< ゲームオーバーフラグ
      bool _gameClear{ false };     //!< ゲームクリアフラグ
      bool _gamePause{ false };     //!< ゲームポーズフラグ
      //!< オブジェクトサーバ
      std::unique_ptr<Object::ObjectServer> _objectServer{ nullptr };
      //!< スポーンサーバ
      std::unique_ptr<Object::SpawnServer> _spawnServer{ nullptr };
      //!< カメラ
      std::unique_ptr<Camera::Camera> _camera{ nullptr };
      //!< エフェクト読み込みサーバ
      std::unique_ptr<Effect::EffectLoadServer> _effectLoadServer{ nullptr };
      //!< エフェクトサーバ
      std::unique_ptr<Effect::EffectServer> _effectServer{ nullptr };
      //!< ステージコンポーネント
      std::unique_ptr<Stage::StageComponent> _stage{ nullptr };
      //!< ステージ遷移用のマネージャー
      std::unique_ptr<Stage::StageTransition> _stageTransition{nullptr};
      /**
       * @brief  更新処理
       * @return
       */
      bool Process() override;
      /**
       * @brief  Effekseer設定
       * @return true 設定成功
       *         false 設定失敗
       */
      bool Effekseer();
      /**
       * @brief  終了判定
       */
      void IsQuit() override;
    };
  } // namespace Application
} // namespace Gyro
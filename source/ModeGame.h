/*****************************************************************//**
 * @file   ModeGame.h
 * @brief  インゲーム処理を行うモード
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "Player.h"
#include "PrimitiveBase.h"
#include "PrimitivePlane.h"
#include "SpawnServer.h"
#include "Light.h"
#include "Shadow.h"
/**
 * @brief ゲームベース
 */
namespace Gyro {
  // 前方宣言
  namespace Application {
    class ApplicationMain;
  }
  /**
   * @brief モードベース
   */
  namespace Mode {
    /**
     * @class ModeGame
     * @brief ゲーム処理を行うモード
     */
    class ModeGame : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      ModeGame(Application::ApplicationMain& app);
      /**
       * @brief デストラクタ
       */
      ~ModeGame() override;
      /**
       * @brief  初期化処理
       * @return true:初期化成功 false:初期化失敗
       */
      bool Init() override;
      /**
       * @brief  入口処理
       * @return true
       */
      bool Enter() override;
      /**
       * @brief  終了処理
       * @return true
       */
      bool Exit() override;
      /**
       * @brief  入力処理
       * @param  input インプットオペレーションの参照
       * @return true:正常終了 false:問題発生
       */
      bool Input(AppFrame::Application::InputOperation& input) override;
      /**
       * @brief  更新処理
       * @return true:正常終了 false:問題発生
       */
      bool Process() override;
      /**
       * @brief  描画処理
       * @return 
       */
      bool Draw() const override;
      /**
       * @brief  ステージの設定
       * @return true:正常終了 false:問題発生
       */
      bool StageChange(std::string_view key);
      /**
       * @brief  アプリケーションメインの取得
       * @return アプリケーションメインの参照を返す
       */
      Application::ApplicationMain& GetAppMain();
    private:
      bool _isEffectLoad{ false };  //!< エフェクト読み込みフラグ
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
      //!< 床
      Primitive::Plane _plane;
      //!< ライト
      std::unique_ptr<Light::Light> _light;
      //!< シャドウ
      std::unique_ptr<Shadow::Shadow> _shadow;
      //!< 現在のステージキー
      std::string _key;
      //!< waveフラグ
      bool _wave1{ true };
      bool _wave2{ true };
      bool _wave3{ true };
      bool _wave4{ true };
      bool _bossStage{ true };
      int _waveNum{ 0 };

      /**
       * @brief リソースの読み取り
       */
      void LoadResource();
      /**
       * @brief エフェクトリソースの読み取り
       */
      void LoadEffectResource();
      /**
       * @brief スポーン情報の設定
       */
      void SetSpawn();
      /**
       * @brief スポーンさせるタイミング
       */
      void SpawnTiming();
      /**
       * @brief ゲームオーバー切り替え
       */
      void GameOver();
    };
  } // namespace Mode
} // namespace Gyro
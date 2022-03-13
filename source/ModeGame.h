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
#include "StageTransition.h"
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
   * @brief エネミーベース
   */
  namespace Enemy {
    class EnemyDroneBoss; //!< 前方宣言
    class EnemyWheelBoss; //!< 前方宣言
  } // namespace Enemy
  /**
   * @brief モードベース
   */
  namespace Mode {
    /**
     * @class ModeGame
     * @brief ゲーム処理を行うモード
     */
    class ModeGame : public AppFrame::Mode::ModeBase {
    private:
      friend class Application::ApplicationMain;
      friend class Enemy::EnemyDroneBoss;
      friend class Enemy::EnemyWheelBoss;
    public:
      /**
       * @brief ゲームの状態を表す列挙型クラス
       */
      enum class GameState {
        Play,    // プレイ中
        Pouse,   // ポーズ
        GameOver // ゲームオーバー
      };
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
      bool StageChange(const Stage::StageTransition::StageType& key);
      /**
       * @brief  アプリケーションメインの取得
       * @return アプリケーションメインの参照を返す
       */
      Application::ApplicationMain& GetAppMain();
      /**
       * @brief  ゲームオーバー状態かの判定
       * @return true:ゲームオーバー false:ゲームオーバーではない
       */
      bool IsGameOver() const {
        return _gameState == GameState::GameOver;
      }
      /**
       * @brief  ボスカウントの取得
       * @return ボスカウント
       */
      inline int GetBossCount() {
        return _bossCount;
      }
    private:
      bool _isEffectLoad{ false };  //!< エフェクト読み込みフラグ
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
      //!< ゲーム状態
      GameState _gameState{GameState::Pouse};
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
      //!< ボス討伐カウント
      int _bossCount{0};
      //!< ボス数
      int _bossNum{0};
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
       * @brief  ゲームオーバー処理
       * @return true:ゲームオーバー処理を実行 false:ゲームオーバーではない
       */
      bool GameOver();
      /**
       * @brief  ゲームオーバー状態への切り替え
       * @brief スポーンさせるタイミング
       */
      void SpawnTiming();
      /**
       * @brief ゲームオーバー切り替え
       */
      // void GameOver();
      /**
       * @brief リザルト切り替え
       */
      void Result();
      /**
       * @brief ポーズ切り替え
       */
      void Pause();
      /**
       * @brief ローディング切り替え
       */
      void Loading();
      void ToGameOver();
      /**
       * @brief オブジェクト番号を初期化する
       */
      void ResetObjectNumber();
      /**
       * @brief ボス討伐カウントの初期化
       */
      inline void BossCountReset() {
        _bossCount = 0;
      }
      /**
       * @brief  ゲームクリアに遷移するかの判定
       * @return true:遷移する false:遷移しない
       */
      bool ToGameClear();
      /**
       * @brief  ゲームクリア判定
       * @return true:クリア false:クリアではない
       */
      inline bool IsGameClear() const {
        return _bossCount == _bossNum;
      }
    };
  } // namespace Mode
} // namespace Gyro
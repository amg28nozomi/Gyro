/*****************************************************************//**
 * @file    ModeTitle.h
 * @brief   モードタイトルクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"
#include "Studio.h"

 /**
  * @brief ゲームベース
  */
namespace Gyro {
  /**
   * @brief モードベース
   */
  namespace Mode {
    namespace AppMath = AppFrame::Math;
    /**
     * @class ModeTitle
     * @brief モードタイトルクラス
     */
    class ModeTitle : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      ModeTitle(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~ModeTitle() override;
      /**
       * @brief  初期化処理
       * @return true
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
       * @return true
       */
      bool Input(AppFrame::Application::InputOperation& input) override;
      /**
       * @brief  更新処理
       * @return true
       */
      bool Process() override;
      /**
       * @brief  描画処理
       * @return true
       */
      bool Draw() const override;

    private:
      /**
       * @brief  変数解放
       */
      void Release();
      /**
       * @brief  リソース読み込み
       */
      void LoadResource();
      /**
       * @brief  左スティック上下入力
       * @param  leftY 左スティック上下入力値
       */
      void LeftStickYInput(const int leftY);
      /**
       * @brief  拡大率設定
       */
      void SetExRate();
      /**
       * @brief  モード切り替え
       */
      void ChangeMode();
      /**
       * @brief  インゲーム遷移
       */
      void InGame();
      /**
       * @brief  クレジット遷移
       */
      void Credit();

      int _titleHandle{ -1 };          //!< タイトル画像
      int _pressButtonHandle{ -1 };    //!< プレスボタン画像
      int _gameStartHandle{ -1 };      //!< ゲーム開始画像
      int _creditHandle{ -1 };         //!< クレジット画像
      int _quitGameHandle{ -1 };       //!< ゲーム終了画像
      int _sceneNum{ 0 };              //!< 場面番号
      float _gameStartExRate{ 1.0f };  //!< ゲーム開始拡大率
      float _creditExRate{ 1.0f };     //!< クレジット拡大率
      float _quitGameExRate{ 1.0f };   //!< ゲーム終了拡大率
      bool _isStick{ false };          //!< 左スティック上下入力判定
      bool _decision{ false };         //!< 選択決定
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
      //!< スタジオ
      std::unique_ptr<Studio::Studio> _studio{ nullptr };
    };
  }
}
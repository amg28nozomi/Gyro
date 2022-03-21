/*****************************************************************//**
 * @file    ModeGameOver.h
 * @brief   モードゲームオーバークラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"

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
     * @class ModeGameOver
     * @brief モードゲームオーバークラス
     */
    class ModeGameOver : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      ModeGameOver(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~ModeGameOver() override;
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
       * @brief  リソース読み込み
       */
      void LoadResource();
      /**
       * @brief  左スティック上下入力
       * @param  leftY 左スティック上下入力値
       */
      void LeftStickYInput(const int leftY);
      /**
       * @brief  モード切り替え
       */
      void ChangeMode();

      int _gameOverHandle{ -1 };          //!< ゲームオーバー画像
      int _retryHandle[2]{ -1, -1 };      //!< リトライ画像
      int _backTitleHandle[2]{ -1, -1 };  //!< タイトルバック画像
      int _retry{ 0 };                    //!< リトライ番号
      int _backTitle{ 0 };                //!< タイトルバック番号
      bool _isStick{ false };             //!< 左スティック上下入力有無
      bool _decision{ false };            //!< 選択決定
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
    };
  }
}
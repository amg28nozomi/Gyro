/*****************************************************************//**
 * @file    ModePause.h
 * @brief   モードポーズクラス
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
     * @class ModePause
     * @brief モードポーズクラス
     */
    class ModePause : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      ModePause(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~ModePause() override;
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

      int _pauseHandle{ -1 };            //!< ポーズ画像
      int _continueHandle[2]{ -1, -1 };  //!< コンティニュー画像
      int _quitGameHandle[2]{ -1, -1 };  //!< ゲーム終了画像
      int _continue{ 0 };                //!< コンテニュー番号
      int _quitGame{ 0 };                //!< ゲーム終了番号
      bool _isStick{ false };            //!< 左スティック上下入力有無
      bool _decision{ false };           //!< 選択決定
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
    };
  }
}
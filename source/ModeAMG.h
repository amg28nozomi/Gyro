/*****************************************************************//**
 * @file    ModeAMG.h
 * @brief   モードAMGクラス
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
  namespace Application {
    class ApplicationMain; //!< 前方宣言
  } // namespace Application
  /**
   * @brief モードベース
   */
  namespace Mode {
    namespace AppMath = AppFrame::Math;
    /**
     * @class ModeAMG
     * @brief モードAMGクラス
     */
    class ModeAMG : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      ModeAMG(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~ModeAMG() override;
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
       * @brief  モード切り替え
       */
      void ChangeMode();

      int _amgHandle{ -1 };  //!< AMG画像
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
    };
  }
}
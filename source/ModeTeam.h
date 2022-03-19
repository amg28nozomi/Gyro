/*****************************************************************//**
 * @file    ModeTeam.h
 * @brief   モードチームクラス
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
     * @class ModeTeamLogo
     * @brief モードチームロゴクラス
     */
    class ModeTeam : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      ModeTeam(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~ModeTeam() override;
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

      int _teamHandle{ -1 };  //!< チーム画像
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
    };
  }
}
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
       * @brief  リソース読み込み
       */
      void LoadResource();
      /**
       * @brief  モード切り替え
       */
      void ChangeMode();

      int _titleHandle{ -1 };  //!< タイトル画像
      bool _start{ false };    //!< ゲーム開始
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
      //!< スタジオ
      std::unique_ptr<Studio::Studio> _studio{ nullptr };
    };
  }
}
/*****************************************************************//**
 * @file   ModeLoading.h
 * @brief  モードローディングクラス
 * 
 * @author 土橋峡介
 * @date   March 2022
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
    /**
     * @class ModeLoading
     * @brief モードローディングクラス
     */
    class ModeLoading : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      ModeLoading(Application::ApplicationMain& app);
      /**
       * @brief デストラクタ
       */
      ~ModeLoading() override;
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
       * @brief  リソース読み込み
       */
      void LoadResource();
      /**
       * @brief  モード切り替え
       */
      void ChangeMode();

      int _loadHandle[ 4 ]{ -1 };  //!< AMG画像
      int _cnt{ 0 };               //!< カウント
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;
    };
  } // namespace Mode
} // namespace Gyro
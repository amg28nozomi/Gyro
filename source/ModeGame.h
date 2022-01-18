/*****************************************************************//**
 * @file   ModeGame.h
 * @brief  インゲーム処理を行うモード
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
/**
 * @brief ゲームベース
 */
namespace Gyro {
  // 前方宣言
  class ApplicationMain;
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
      ModeGame(AppFrame::Application::ApplicationBase& app);
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
       * @brief  グラビティベースの取得
       * @return グラビティベースの参照
       */
      inline AppFrame::Math::GravityBase& GetGravity() {
        return *_gravity;
      }
    private:
      //!< グラビティベース
      std::shared_ptr<AppFrame::Math::GravityBase> _gravity{nullptr};
    };
  } // namespace Mode
} // namespace Gyro
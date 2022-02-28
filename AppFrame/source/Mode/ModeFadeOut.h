/*****************************************************************//**
 * @file   ModeFadeOut.h
 * @brief  モードフェードのサブクラス
 *         フェードアウト処理を行う
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "ModeFade.h"
/**
 * @brief アプリケーションフレーム
 */
namespace AppFrame {
  /**
   * @brief モードベース
   */
  namespace Mode {
    /**
     * @class ModeFadeOut
     * @brief フェードアウト処理を行うモード
     */
    class ModeFadeOut : public ModeFade {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      ModeFadeOut(Application::ApplicationBase& app, const Data::Color color = Data::Color());
      /**
       * @brief  入口処理
       * @return true
       */
      bool Enter() override;
      /**
       * @brief  更新処理
       * @return true
       */
      bool Process() override;
    private:
      /**
       * @brief  フェード処理の終了判定
       * @return true:終了 false:処理継続
       */
      bool IsFinish() override;
    };
  } // namespace Mode
} // namespace AppFrame
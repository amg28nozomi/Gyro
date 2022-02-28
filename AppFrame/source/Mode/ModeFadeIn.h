/*****************************************************************//**
 * @file   ModeFadeIn.h
 * @brief  モードフェードのサブクラス
 *         フェードイン処理を行う
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
     * @class ModeFadeIn
     * @brief フェードイン処理を行うモード
     */
    class ModeFadeIn : public ModeFade {
    public:
      /**
       * @brief コンストラクタ
       * @param app   アプリケーションの参照
       * @param color フェード処理で使用するRGB値
       */
      ModeFadeIn(Application::ApplicationBase& app, const Data::Color color = Data::Color());
      /**
       * @brief  入口処理
       * @return treu
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
       * @return true:処理完了 false:処理継続
       */
      bool IsFinish() override;
    };
  } // namespace Mode
} // namespace AppFrame
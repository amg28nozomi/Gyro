/*****************************************************************//**
 * @file   Shadow.h
 * @brief  モードゲーム時のシャドウクラス
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
  /**
   * @brief シャドウ
   */
  namespace Shadow {
    /**
     * @class Shadow
     * @brief モードゲーム用シャドウクラス
     */
    class Shadow {
    public:
      /**
       * @brief コンストラクタ
       * 
       */
      Shadow(Application::ApplicationMain& app);
      /**
       * @brief デストラクタ
       */
      ~Shadow();
      /**
       * @brief 初期化処理
       */
      void Init();
      /**
       * @brief 更新処理
       */
      void Process();
      /**
       * @brief 描画処理
       */
      void Draw() const;
    private:
      //!< アプリケーションメインの参照
      Application::ApplicationMain& _appMain;

      int _shadowHandle; //!< シャドウマップハンドル
    };
  } // namespace Shadow
} // namespace Gyro
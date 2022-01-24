/*****************************************************************//**
 * @file   ApplicationMain.h
 * @brief  アプリケーションベースのサブクラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
/**
 * @brief ゲームスペース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class ObjectServer;
  } // namespace 
  /**
   * @brief アプリケーション
   */
  namespace Application {
    /**
     * @class ApplicationMain
     * @brief アプリケーションメイン
     */
    class ApplicationMain : public AppFrame::Application::ApplicationBase {
    public:
      /**
       * @brief  コンストラクタ
       */
      ApplicationMain();
      /**
       * @brief  初期化
       * @return true:初期化成功 false:初期化失敗
       */
      bool Init() override;
      /**
       * @brief  入力処理
       * @return 
       */
      bool Input() override;
      /**
       * @brief  フレームカウンタの取得
       * @return フレームカウンタ
       */
      const int GetFrameCount() const override {
        return 0;
      }
      /**
       * @brief  オブジェクトサーバの取得
       * @return オブジェクトサーバの参照
       */
      Object::ObjectServer& GetObjectServer() {
        return *_objectServer;
      }
    private:
      //!< オブジェクトサーバ
      std::unique_ptr<Object::ObjectServer> _objectServer{nullptr};
      /**
       * @brief  更新処理
       * @return
       */
      bool Process() override;
    };
  } // namespace Application
} // namespace Gyro
/*****************************************************************//**
 * @file   ApplicationMain.h
 * @brief  アプリケーションベースのサブクラス
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include <EffekseerForDXLib.h>
#include "Camera.h"
#include "Effect/EffectServer.h"
#include "Effect/EffectComponent.h"

 /**
  * @brief ゲームスペース
  */
namespace Gyro {
    /**
     * @brief オブジェクトベース
     */
    namespace Object {
        // 前方宣言
        class ObjectServer; //!< オブジェクトサーバ
        class SpawnServer;  //!< スポーンサーバ
    } // namespace Object
    /**
     * @brief エフェクトベース
     */
    namespace Effect {
        // 前方宣言
        class EffectServer;     //!< エフェクトサーバ
        class EffectComponent;  //!< エフェクト
    } // namespace Effect
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
             * @brief  終了処理
             */
            void Terminate() override;
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
            /**
             * @brief  スポーンサーバの取得
             * @return スポーンサーバの参照
             */
            Object::SpawnServer& GetSpawnServer() {
                return *_spawnServer;
            }
            /**
             * @brief  カメラの取得
             * @return カメラの参照
             */
            Camera::Camera& GetCamera() {
                return *_camera;
            }
            /**
             * @brief  エフェクトサーバの取得
             * @return エフェクトサーバの参照
             */
            Effect::EffectServer& GetEffectServer() {
                return *_effectServer;
            }
            /**
             * @brief  エフェクトの取得
             * @return エフェクトの参照
             */
            Effect::EffectComponent& GetEffect() {
                return *_effect;
            }
        private:
            //!< オブジェクトサーバ
            std::unique_ptr<Object::ObjectServer> _objectServer{ nullptr };
            //!< スポーンサーバ
            std::unique_ptr<Object::SpawnServer> _spawnServer{ nullptr };
            //!< カメラ
            std::unique_ptr<Camera::Camera> _camera{ nullptr };
            //!< エフェクトサーバ
            std::unique_ptr<Effect::EffectServer> _effectServer{ nullptr };
            //! エフェクト
            std::unique_ptr<Effect::EffectComponent> _effect{ nullptr };
            /**
             * @brief  更新処理
             * @return
             */
            bool Process() override;
            /**
             * @brief  Effekseer設定
             * @return true 設定成功
             *         false 設定失敗
             */
            bool Effekseer();
        };
    } // namespace Application
} // namespace Gyro
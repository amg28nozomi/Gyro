#pragma once
#include "ObjectBase.h"
//#include "camera.h"

/**
 * @brief ゲームベース
 */
namespace Gyro {
    namespace Camera {
        class Camera {
        public:
            VECTOR _pos;
            VECTOR _target;
            float _clipNear, _clipFar;
        };
    }
    /**
     * @brief プレイヤー
     */
    namespace Player {
        /**
         * @class Player
         * @brief オブジェクトベースのサブクラス
         */
        class Player : public Object::ObjectBase {
            public:
            /**
             * @enum class
             */
            enum class STATE {
                IDLE,
                WALK,
                RUN,
                ATTACK,
                JUMP,
            };
            /**
             * @brief コンストラクタ
             */
            Player(Application::ApplicationMain& app);
            //Player();
            /**
             * @brief  初期化処理
             * @return true
             */
            bool Init() override;
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
        protected:
            int _handleMap;
            int _frameMapCollision;
            int _handleModel;       //!< モデルハンドル
            int _handleSkySphere;   //!< スカイスフィアハンドル
            int _attachIndex;       //!< アニメーションのアタッチ
            float _totalTime;       //!< 総再生時間
            float _playTime;        //!< 
            VECTOR _position;       //!< 座標
            VECTOR _dir;            //!< 向き

            STATE _state;           //!< 状態

            Camera::Camera _cam;
        };
    } // namespace Player
} // namespace Gyro


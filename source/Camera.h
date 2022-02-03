/*****************************************************************//**
 * @file   Camera.h
 * @brief  オブジェクトクラスのサブクラス
 *         カメラの処理を行う
 *
 * @author 土橋峡介
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "ObjectBase.h"

namespace AppFrame::Math {}

/**
 * @brief ゲームベース
 */
namespace Gyro {
    /**
     * @brief カメラ
     */
    namespace Camera {
        /**
         * @class Camera
         * @brief カメラクラス
         */
        class Camera {
        public:
            /**
             * @brief カメラの状態を表す列挙型クラス
             */
            enum class CameraState {
                Normal,         //!< 通常
                SpecialMove,    //!< 必殺技
            };
            /**
             * @brief コンストラクタ
             */
            Camera();
            /**
             * @brief デストラクタ
             */
             //~Camera();
             /**
              * @brief 初期化
              */
            bool Init();
            /**
             * @brief 更新
             * @param stick     右スティックの大きさ
             * @param target    プレイヤーの位置
             * @param move      プレイヤーの移動量
             */
            bool Process(const AppFrame::Math::Vector4 stick, const AppFrame::Math::Vector4 target, const AppFrame::Math::Vector4 move);
#ifdef _DEBUG
            /**
             * @brief 描画
             * @param position  プレイヤーの位置
             * @param move      プレイヤーの移動量
             */
            bool Draw(const AppFrame::Math::Vector4 positoin, const AppFrame::Math::Vector4 move) const;
#endif // DEBUG
            float CamPosGetX() {
                return _position.GetX();
            }
            float CamPosGetZ() {
                return _position.GetZ();
            }
            float CamTarGetX() {
                return _target.GetX();
            }
            float CamTarGetZ() {
                return _target.GetZ();
            }
        private:
            AppFrame::Math::Vector4 _position{};    //!< カメラの座標
            AppFrame::Math::Vector4 _target{};  //!< カメラの注視点(見ている座標)
            CameraState _cameraState{ CameraState::Normal }; //!< カメラ状態

            /**
             * @brief 状態の設定
             */
            void SetState();
        };
    }// namespace Camera
}// namespace Gyro

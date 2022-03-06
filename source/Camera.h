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
      ~Camera();
      /**
       * @brief 初期化
       */
      bool Init();
      /**
       * @brief  更新
       * @param  stick     右スティックの大きさ
       * @param  target    プレイヤーの位置
       * @param  move      プレイヤーの移動量
       * @return true
       */
      bool Process(const AppFrame::Math::Vector4 stick, const AppFrame::Math::Vector4 target, const AppFrame::Math::Vector4 move);
#ifdef _DEBUG
      /**
       * @brief  描画
       * @param  position  プレイヤーの位置
       * @param  move      プレイヤーの移動量
       * @return true
       */
      bool Draw(const AppFrame::Math::Vector4 positoin, const AppFrame::Math::Vector4 move) const;
#endif
      /**
       * @brief  カメラのXを取得
       * @return カメラのX座標
       */
      float CamPosGetX() {
          return _position.GetX();
      }
      /**
       * @brief  カメラのZ座標を取得
       * @return カメラのZ座標
       */
      float CamPosGetZ() {
          return _position.GetZ();
      }
      /**
       * @brief  注視点のX座標を取得
       * @return 注視点のX座標
       */
      float CamTarGetX() {
          return _target.GetX();
      }
      /**
       * @brief  注視点のZ座標を取得
       * @return 注視点のZ座標
       */
      float CamTarGetZ() {
          return _target.GetZ();
      }
      /**
       * @brief  カメラの座標に足す
       * @param  vector
       * @return 0.0f
       */
      float CamAddPos(const AppFrame::Math::Vector4 vector) {
          _position.Add(vector);
          return 0.0f;
      }
      /**
       * @brief  カメラ座標の取得
       * @return カメラ座標
       */
      AppFrame::Math::Vector4 GetPosition() const {
        return _position;
      }
      /**
       * @brief  注視点の取得
       * @return 注視点
       */
      AppFrame::Math::Vector4 GetTarget() const {
        return _target;
      }
      /**
       * @brief  カメラの状態を取得
       * @return カメラの状態
       */
      CameraState GetCamState() {
        return _cameraState;
      }
      /**
       * @brief  カメラの状態をスペシャルに移行
       * @return 
       */
      CameraState GoSpecial() {
        _cameraState = CameraState::SpecialMove;
        _cnt = 20;
        return _cameraState;
      }
    private:
      AppFrame::Math::Vector4 _position{};    //!< カメラの座標
      AppFrame::Math::Vector4 _target{};      //!< カメラの注視点(見ている座標)
      CameraState _cameraState{ CameraState::Normal }; //!< カメラ状態
      int _cnt;                               //!< カウント
      /**
       * @brief  Normal状態の処理
       * @param  stick   右スティックの大きさ
       * @param  target  プレイヤーの位置
       * @param  move    プレイヤーの移動量
       */
      void Normal(const AppFrame::Math::Vector4 stick, const AppFrame::Math::Vector4 target, const AppFrame::Math::Vector4 move);
      /**
       * @brief  Special状態の処理
       * @param  target  プレイヤーの位置
       * @param  move    プレイヤーの移動量
       */
      void Special(const AppFrame::Math::Vector4 stick, const AppFrame::Math::Vector4 target, const AppFrame::Math::Vector4 move);
      /**
       * @brief 状態の設定
       */
      void SetState();
    };
  }// namespace Camera
}// namespace Gyro

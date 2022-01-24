/*****************************************************************//**
 * @file   CameraBase.h
 * @brief  カメラベースクラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

namespace Gyro {

  namespace Object {
    class ObjectBase;
  } // namespace Object
  /**
   * @brief アプリケーションベース
   */
  namespace Application {

    namespace AppMath = AppFrame::Math;
    /**
     * @class CameraBase
     * @brief カメラの基底クラス
     */
    class CameraBase {
    public:
      /**
       * @brief コンストラクタ
       */
      CameraBase(Object::ObjectBase& owner);
      /**
       * @brief 初期化
       */
      virtual void Init();
      /**
       * @brief 更新処理
       */
      virtual void Process();
    protected:
      Object::ObjectBase& _owner; //!< カメラの保有者
      AppMath::Vector4 _position; //!< カメラ座標
      AppMath::Vector4 _rotation; //!< 注視点
      AppMath::Matrix44 _lookAt;  //!< 注視行列

    };
  } // namespace Application
} // namespace Gyro
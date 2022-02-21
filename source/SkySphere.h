/*****************************************************************//**
 * @file   SkySphere.h
 * @brief  スカイスフィアクラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectBase.h"
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    /**
     * @class  SkySphere
     * @brief  スカイスフィアクラス
     */
    class SkySphere : public ObjectBase {
    public:
      /**
       * @brief コンストラクタ
       */
      SkySphere(Application::ApplicationMain& app, ObjectBase& owner);


    protected:
      ObjectBase& _owner; //!< 所有者
    };
  } // namespace Object
} // namespace Gyro
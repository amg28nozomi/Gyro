/*****************************************************************//**
 * @file   ObjectBase.h
 * @brief  オブジェクトのスーパークラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once

namespace AppFrame {
  namespace Math {
    /**
     * @brief 前方宣言
     */
    class Vector4;
  }
}

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    class ApplicationMain; //!< 前方宣言
  } // namespace Application
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    /**
     * @class ObjectBase
     * @brief オブジェクトのスーパークラス
     */
    class ObjectBase {
    public:
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      ObjectBase(Application::ApplicationMain& app);
      /**
       * @brief  初期化処理
       * @return true
       */
      virtual bool Init();
      /**
       * @brief  更新処理
       * @return true
       */
      virtual bool Process();
      /**
       * @brief  描画処理
       * @return true
       */
      virtual bool Draw() const;
    protected:
      Application::ApplicationMain& _app; //!< アプリケーションの参照
      AppFrame::Math::Vector4 _position;  //!< 座標行列
      AppFrame::Math::Vector4 _rotation;  //!< 回転行列
      bool _gravity; //!< 重力処理を行うか(true:重力処理を行う false:重力処理を行わない)
      float _mass;   //!< 質量
      float _gravityScale; //!< 重力スケール
      /**
       * @brief オブジェクトに対する重力処理
       */
      virtual void Gravity();
    };
  } // namespace Object
} // namespace Gyro
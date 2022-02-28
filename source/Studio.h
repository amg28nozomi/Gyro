/*****************************************************************//**
 * @file    Studio.h
 * @brief   モード用スタジオクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"
#include "ModelAnimComponent.h"

 /**
  * @brief ゲームベース
  */
namespace Gyro {
  /**
   * @brief スタジオベース
   */
  namespace Studio {
    namespace AppMath = AppFrame::Math;
    /**
     * @class Studio
     * @brief モード用スタジオクラス
     */
    class Studio {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      Studio(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~Studio();
      /**
       * @brief  初期化
       */
      void Init();
      /**
       * @brief  解放
       */
      void Release();
      /**
       * @brief  更新
       */
      void Process();
      /**
       * @brief  描画
       */
      void Draw() const;
      /**
       * @brief  ジャイロアニメ切り替え
       * @param  key アニメキー
       */
      void GyroChangeAnim(const std::string_view key);
      /**
       * @brief  ジャイロアニメ終了判定
       * @return true:ジャイロアニメ終了
       *         false:ジャイロアニメ再生中
       */
      bool IsGyroAnimEnd() {
        return _modelAnim.GetMainAnimEnd();
      }

    private:
      /**
       * @brief  リソース読み込み
       */
      void LoadResource();
      /**
       * @brief  モデル配置
       */
      void LayOut();

      int _studioHandle{ -1 };  //!< スタジオモデル
      int _gyroHandle{ -1 };    //!< ジャイロモデル
      int _skyHandle{ -1 };     //!< スカイモデル
      AppMath::Vector4 _skyRot{ 0.0f, 0.0f, 0.0f };  //!< スカイ向き
      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
      //!< モデルアニメ
      ModelAnim::ModelAnimComponent _modelAnim;
    };
  }
}
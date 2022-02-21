/*****************************************************************//**
 * @file   StageBase.h
 * @brief  ステージのスーパークラス
 * 
 * @author 土橋 峡介
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
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
   * @brief ステージベース
   */
  namespace Object {
    namespace AppMath = AppFrame::Math;
    class SpawnBase; //!< スポーン情報
    /**
     * @class StageBase
     * @brief ステージのスーパークラス
     */
    class StageBase {
    public:
      /**
       * @brief コンストラクタ
       * @param アプリケーションの参照
       */
      StageBase(Application::ApplicationMain& app);
      /**
       * 
       */
      ~StageBase();
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
      /**
       * @brief  モデルハンドル格納コンテナの取得
       * @return モデルハンドル格納コンテナ
       */
      std::vector<int> GetStageModel() const {
          return _model;
      }
    protected:
      Application::ApplicationMain& _app;        //!< アプリケーションの参照
      std::vector<int> _model{ -1 }; //!< モデルハンドル格納用コンテナ
    };
  } // namespace Stage
} // namespace Gyro

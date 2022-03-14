/*****************************************************************//**
 * @file   StageComponent.h
 * @brief  ステージを作成するクラス
 * 
 * @author 土橋 峡介
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "StageData.h"
#include <appframe.h>
#include <string>
#include <unordered_map>
#include "appframe.h"
#include "SkySphere.h"
#include "SpawnServer.h"
#include "ObjectBase.h"
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

  namespace Object {
    class SkySphere;
  } // namespace Object
  /**
   * @brief ステージ
   */
  namespace Stage {
    namespace AppMath = AppFrame::Math;
    /**
     * @class StageComponent
     * @brief ステージコンポーネントクラス
     */
    class StageComponent{
    public:
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      StageComponent(Application::ApplicationMain& app);
      /**
       * @brief デストラクタ
       */
      ~StageComponent();
      /**
       * @brief  初期化
       * @param  jsonName jsonのファイル名
       * @return true
       */
      bool Init(std::filesystem::path jsonName);
      /**
       * @brief ステージ情報を読み込む
       * @param key _stageModelMapに登録するキー
       * @param stageData ステージ情報
       */
      void LoadStage(std::string_view key, StageData& stageData);
      /**
       * @brief  ステージ情報をもとにオブジェクトをおいていく
       * @param  key _stageModelMapに登録するキー
       * @return true
       */
      bool CreateStage(std::string key);
      /**
       * @brief  更新
       * @return true
       */
      bool Process();
      /**
       * @brief 描画
       */
      bool Draw() const;
      /**
       * @brief  ステージ情報の解放
       * @return true
       */
      bool ReleaseStageInfo();
      /**
       * @brief  ステージモデルだけ解放
       * @return true
       */
      bool ReleaseModel();
      void AddSky(std::shared_ptr<Object::SkySphere> sky);
      /**
       * @brief  ステージ情報の取得
       * @param  key 各ステージに関連づけた任意の文字列
       * @return ハンドルとステージ情報
       */
      std::vector<std::pair<int, StageData>> GetStageModels(std::string key);
      /**
       * @brief  モデルハンドル格納コンテナの取得
       * @return モデルハンドル格納コンテナ
       */
      std::vector<int> GetStageModel() const {
          return _model;
      }
      /**
       * @brief  スカイスフィアの取得
       * @return スカイスフィア
       */
      std::shared_ptr<Object::SkySphere> GetSkySphere() {
        return _skySphere;
      }
      /**
       * @brief  ステージネームの取得
       * @return ステージネーム
       */
      std::filesystem::path GetStageName() {
        return _stageName;
      }
    private:
      /**
       * @brief 文字列をキーとしてステージ情報を管理する連想配列
       */
      std::unordered_map<std::string, std::vector<std::pair<int, StageData>>> _stageModelMap;
      std::vector<int> _model{ -1 }; //!< モデルハンドル格納用コンテナ
      std::shared_ptr<Object::SkySphere> _skySphere{ nullptr };
      std::filesystem::path _stageName;
    };
  } //namespace Stage
} // namespace Gyro
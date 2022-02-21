/*****************************************************************//**
 * @file   StageComponent.h
 * @brief  ステージを作成するクラス
 * 
 * @author 土橋 峡介
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "StageData.h"
#include "StageBase.h"
#include "appframe.h"
#include <string>
#include <unordered_map>
#include "appframe.h"
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief ステージ
   */
  namespace Stage {
    namespace AppMath = AppFrame::Math;
    /**
     * @class StageComponent
     * @brief ステージコンポーネントクラス
     */
    class StageComponent : public Object::StageBase {
    public:
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      StageComponent(Application::ApplicationMain& app);
      /**
       * 初期化
       */
      bool Init() override;
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
       * @brief 描画
       */
      bool Draw() const override;
      /**
       * @brief  ステージ情報の取得
       * @param  key 各ステージに関連づけた任意の文字列
       * @return ハンドルとステージ情報
       */
      std::vector<std::pair<int, StageData>> GetStageModels(std::string key);

    private:
      /**
       * @brief 文字列をキーとしてステージ情報を管理する連想配列
       */
      std::unordered_map<std::string, std::vector<std::pair<int, StageData>>> _stageModelMap;
    };
  } //namespace Stage
} // namespace Gyro

/*****************************************************************//**
 * @file   StageTransition.h
 * @brief  ステージ遷移を管理するマネージャークラス
 * 
 * @author 鈴木希海
 * @date   March 2022
 *********************************************************************/
#pragma once
#include <appframe.h>
#include <unordered_map>

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    class ApplicationMain;
  } // namespace Applicaiton
  /**
   * @brief ステージベース
   */
  namespace Stage {
    /**
     * @class StageTransition
     * @brief ステージ遷移を管理するマネージャー
     */
    class StageTransition {
    public:
      /**
       * @brief ステージの種類をあらわす列挙型クラス
       */
      enum class StageType {
        Null,   // 該当なし
        Normal, // 通常ステージ
        Boss    // ボスステージ
      };
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      StageTransition(Application::ApplicationMain& app);
      /**
       * @brief  ステージキーの登録処理
       * @param  stage ステージタイプ
       * @param  key   ステージキー
       * @return true:登録成功 false:登録失敗
       */
      bool Register(const StageType& stage, std::string_view key);
      /**
       * @brief  ステージキーの取得
       * @return キーが登録されている場合はステージキーを返す
       *         ステージタイプがNullの場合は空のキーを返す
       */
      std::string StageKey() const;
      /**
       * @brief  現在のステージタイプの取得
       * @return ステージタイプ
       */
      StageType GetStageType() const {
        return _stageType;
      }
    protected:
      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
      //!< ステージタイプ
      StageType _stageType{StageType::Null};
      //!< ステージキーを管理する連想配列
      std::unordered_map<StageType, std::string> _registry;
      /**
       * @brief  ステージの遷移処理
       * @return true:遷移終了 false:遷移継続
       */
      bool Transition();
    };
  } // namespace Stage
} // namespace Gyro
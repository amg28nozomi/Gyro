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
   * @brief モードベース
   */
  namespace Mode {
    class ModeGame;
  } // namespace Mode
  /**
   * @brief ステージベース
   */
  namespace Stage {
    /**
     * @class StageTransition
     * @brief ステージ遷移を管理するマネージャー
     */
    class StageTransition {
    private:
      /**
       * @brief モードゲームをフレンドクラス指定
       */
      friend class Mode::ModeGame;
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
       * @brief  初期化処理
       * @param  haveData データベースを保持するか(true:保持 false:保持しない(デフォルト))
       * @return true
       */
      void Init(const bool haveData = false);
      /**
       * @brief  ステージキーの登録(複数)
       * @param  stageMap ステージキーが格納された連想配列
       */
      bool Register(const std::unordered_map<StageType, std::string_view> stageMap);
      /**
       * @brief  ステージキーの登録処理
       * @param  stage ステージタイプ
       * @param  key   ステージキー
       * @return true:登録成功 false:登録失敗
       */
      bool Register(const StageType& stage, std::string_view key);
      /**
       * @brief  ステージの遷移予約
       * @param  stage 遷移先のステージタイプ
       * @return true:予約成功 false:予約失敗
       */
      bool ChangeReserve(const StageType& stage);
      /**
       * @brief  ステージを直接切り替える
       * @param  stage 遷移先のステージタイプ
       * @return true:遷移成功 false:遷移失敗
       */
      bool ChangeStage(const StageType& stage);
      /**
       * @brief  ステージ遷移を行うか
       * @return true:遷移実行 false:遷移を行っていない
       */
      bool IsTransition();
      /**
       * @brief  ステージキーの取得
       * @return キーが登録されている場合はステージキーを返す
       *         ステージタイプがNullの場合は空のキーを返す
       */
      std::string GetStageKey() const;
      /**
       * @brief  現在のステージタイプの取得
       * @return ステージタイプ
       */
      StageType GetStageType() const {
        return _stageType;
      }
      /**
       * @brief  ステージタイプが一致していないかの判定
       * @param  stage 対象となるステージタイプ
       * @return true:一致していない false:一致している
       */
      bool StageDifferent(const StageType& stage) const {
        return stage != _stageType;
      }
    protected:
      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
      //!< ステージタイプ
      StageType _stageType{StageType::Null};
      //!< ステージタイプの予約
      StageType _reserveType{StageType::Null};
      //!< ステージキーを管理する連想配列
      std::unordered_map<StageType, std::string> _registry;
      //!< ステージ遷移フラグ
      bool _transition{false};
      /**
       * @brief  ステージの遷移処理
       * @return true:遷移終了 false:遷移継続
       */
      bool Transition();
      /**
       * @brief  ステージタイプがNullかの判定
       * @param  stage 判定するステージタイプ
       * @return true:タイプがNULL false:タイプがNULLではない
       */
      bool StageNull(const StageType& stage) const {
        return stage == StageType::Null;
      }
      /**
       * @brief  ステージキーの取得
       * @param  stage ステージタイプ
       * @return ステージタイプに対応したステージキー
       *         取得に失敗した場合は空の文字列を返す
       */
      std::string StageKey(const StageType& stage) const;
      /**
       * @brief ステージタイプを直接設定する
       * @param stage ステージタイプ
       */
      void SetStageKey(const StageType& stage) {
        _stageType = stage;
      }
    };
  } // namespace Stage
} // namespace Gyro
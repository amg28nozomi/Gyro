/*****************************************************************//**
 * @file   StageTransition.cpp
 * @brief  ステージ遷移を管理するマネージャークラスの定義
 *
 * @author 鈴木希海
 * @date   March 2022
 *********************************************************************/
#include "StageTransition.h"
#include "ApplicationMain.h"

namespace Gyro {
  /**
   * @brief
   */
  namespace Stage {

    StageTransition::StageTransition(Application::ApplicationMain& app) : _app(app) {
      // ステージ遷移情報の設定
      _stageType = StageType::Null;
      // データベースの削除
      _registry.clear();
    }

    bool StageTransition::Register(const StageType& stage, std::string_view key) {
      // データベースに登録されているか
      if (_registry.contains(stage)) {
        return false; // キーは登録済み
      }
      // 未登録の場合はステージキーをセットする
      _registry.emplace(stage, key.data());
      return true; // 登録成功
    }

    std::string StageTransition::StageKey() const {
      // ステージキーは登録されているか
      if (!_registry.contains(_stageType)) {
        return "";
      }
      // 対応するステージキーを返す
      return _registry.at(_stageType);
    }

    bool StageTransition::Transition() {
      return true;
    }
  } // namespace Stage
} // namespace Gyro
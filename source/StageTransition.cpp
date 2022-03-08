/*****************************************************************//**
 * @file   StageTransition.cpp
 * @brief  ステージ遷移を管理するマネージャークラスの定義
 *
 * @author 鈴木希海
 * @date   March 2022
 *********************************************************************/
#include "StageTransition.h"
#include <appframe.h>
#include "ApplicationMain.h"
#include "StageComponent.h"

namespace Gyro {
  /**
   * @brief
   */
  namespace Stage {

    StageTransition::StageTransition(Application::ApplicationMain& app) : _app(app) {
      Init();
    }

    void StageTransition::Init(const bool haveData) {
      // 各種データの初期化
      _stageType = StageType::Null;
      _reserveType = StageType::Null;
      _transition = false;
      // データを保持する場合は処理を行わない
      if (haveData) {
        return;
      }
      // データベースを解放する
      _registry.clear();
    }

    bool StageTransition::Register(const std::unordered_map<StageType, std::string_view> stageMap) {
      // データは登録されているか
      if (stageMap.empty()) {
        return false; // 未登録
      }
      // 登録失敗回数計測用
      auto count = 0;
      // データベース上に登録する
      for (auto [stageType, stageKey] : stageMap) {
#ifndef _DEBUG
        Register(stageType, stageKey);
#else
        // 登録が正常に終了した場合は次へ
        if (Register(stageType, stageKey)) {
          continue;
        }
        // 失敗した場合はカウントする
        ++count;
#endif
      }
#ifdef _DEBUG
      // 登録に失敗した場合はログに出力する
      if (count) {
        OutputDebugString(("StageTransition:" + std::to_string(count) + "回登録に失敗しました\n").data());
      }
#endif
      return true;
    }

    bool StageTransition::Register(const StageType& stage, std::string_view key) {
      // データベースに登録されているか
      if (_registry.contains(stage)) {
        return false; // キーは登録済み
      }
      // ステージタイプがNULLかの判定
      if (StageNull(stage)) {
        return false; // タイプがNULL
      }
      // 未登録の場合はステージキーをセットする
      _registry.emplace(stage, key.data());
      return true; // 登録成功
    }

    bool StageTransition::ChangeReserve(const StageType& stage) {
      // 既に遷移予約が行われている場合は中断
      if (!StageNull(_reserveType)) {
        return false;
      }
      // キーを取得
      const auto key = StageKey(stage);
      // キーは登録されているか
      if (key.empty()) {
        return false; // キーが未登録
      }
      // ステージタイプが空かの判定
      if (StageNull(stage)) {
        return false;
      }
      // 現在のステージと同じかの判定
      if (!StageDifferent(stage)) {
        return false; // キーが重複している
      }
      // 遷移予約を行う
      _transition = true;
      _reserveType = stage;
      return true;
    }

    bool StageTransition::ChangeStage(const StageType& stage) {
      // キーを取得
      const auto key = StageKey(stage);
      // キーは登録されているか
      if (key.empty()) {
        return false; // キーが未登録
      }
      // ステージタイプが空かの判定
      if (StageNull(stage)) {
        return false;
      }
      // ステージ情報の削除
      _app.GetStageComponent().ReleaseStageInfo();
      // ステージの読み込み
      _app.GetStageComponent().Init(key);
      // ステージキーの切り替え
      _stageType = stage;
      return true;
    }

    bool StageTransition::IsTransition() {
      // ステージ遷移フラグは立っているか
      if (!_transition) {
        return false; // フラグは立っていない
      }
      // フェードアウトが終了した場合
      if (!_app.GetModeServer().IsFadeOutEnd()) {
        return false; // 処理が終了していない
      }
      // ステージ遷移を行う
      return Transition();
    }

    std::string StageTransition::GetStageKey() const {
      // 現在のステージに対応したキーを返す
      return StageKey(_stageType);
    }

    bool StageTransition::Transition() {
      // 前ステージの情報を削除する
      _app.GetStageComponent().ReleaseStageInfo();
      // ステージコンポーネントの初期化を行う
      _app.GetStageComponent().Init(StageKey(_reserveType));
      // 現在のキーを更新
      _stageType = _reserveType;
      _reserveType = StageType::Null;
      // 遷移フラグをオフにする
      _transition = false;
      return true;
    }

    std::string StageTransition::StageKey(const StageType& stage) const {
      // ステージキーは登録されているか
      if (!_registry.contains(stage)) {
        return ""; // 未登録
      }
      // 対応するステージキーを返す
      return _registry.at(stage);
    }
  } // namespace Stage
} // namespace Gyro
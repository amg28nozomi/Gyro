/*****************************************************************//**
 * @file    ModeAMG.cpp
 * @brief   モードAMGクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "ModeAMG.h"
#include "ModeTitle.h"
#include "StageComponent.h"
#include "StageTransition.h"

namespace {
  // 各種定数
  constexpr int MaxCount = 30;  //!< モード最大カウント
}

namespace Gyro {
  namespace Mode {
    ModeAMG::ModeAMG(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeAMG::~ModeAMG() {

    }

    bool ModeAMG::Init() {
      // 別名定義
      using StageType = Stage::StageTransition::StageType;
      // ステージリストの生成
      const std::unordered_map<StageType, std::string_view> stageMap = {
        {StageType::Normal, "stage"},
        {StageType::Boss, "boss"},
      };
      // 生成したリストを登録する
      _appMain.GetStageTransition().Register(stageMap);
      return true;
    }

    bool ModeAMG::Enter() {
      // リソース読み込み
      _appMain.GetStageTransition().ChangeReserve(Stage::StageTransition::StageType::Normal);
      LoadResource();
      return true;
    }

    bool ModeAMG::Exit() {
      // 変数解放
      Release();
      return true;
    }

    bool ModeAMG::Process() {
      _count++;  // カウントを増やす
      // モード最大カウントを過ぎたら
      if (MaxCount < _count) {
        // モード切り替え
        ChangeMode();
      }
      return true;
    }

    bool ModeAMG::Draw() const {
      // AMG描画
      DrawGraph(0, 0, _amgHandle, false);
      return true;
    }

    void ModeAMG::Release() {
      // 変数解放
      _amgHandle = -1;
    }

    void ModeAMG::LoadResource() {
      // AMG読み込み
      _amgHandle = LoadGraph("res/Logo/amglogo.png");
      // リソースの読み込みは行われているか
      if (_isLoad) {
        return; // 読み込み済み
      }
      // 非同期処理フラグtrue
      SetUseASyncLoadFlag(true);
      // 通常ステージの読み込み開始
      _appMain.GetStageTransition().IsTransition();
      // 読み込み完了
      _isLoad = true;
    }

    void ModeAMG::ChangeMode() {
      // モードAMGの削除
      _appMain.GetModeServer().PopBuck();
      // 未登録のためモードチームの登録
      _appMain.GetModeServer().AddMode("Title", std::make_shared<Mode::ModeTitle>(_appMain));
      // モードチーム遷移
      _appMain.GetModeServer().TransionToMode("Title");
    }
  } // namespace Mode
} // namespace Gyro
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
      return true;
    }

    bool ModeAMG::Enter() {
      // リソース読み込み
      LoadResource();
      return true;
    }

    bool ModeAMG::Exit() {
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

    void ModeAMG::LoadResource() {
      // リソースの読み込みは行われているか
      if (_isLoad) {
        return; // 読み込み済み
      }
      // AMG読み込み
      _amgHandle = LoadGraph("res/Logo/amglogo.png");
      // 読み込み完了
      _isLoad = true;
      // 非同期処理フラグtrue
      SetUseASyncLoadFlag(true);
      // 通常ステージの読み込み開始
      //_appMain.GetStageComponent().Init("stage");

    }

    void ModeAMG::ChangeMode() {
      // モードAMGの削除
      _appMain.GetModeServer().PopBuck();
      // 未登録のためモードチームの登録
      _appMain.GetModeServer().AddMode("Title", std::make_shared<Mode::ModeTitle>(_appMain));
      // モードチーム遷移
      _appMain.GetModeServer().TransionToMode("Title");
    }
  }
}
/*****************************************************************//**
 * @file    ModeAMG.cpp
 * @brief   モードAMGクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "ModeAMG.h"
#include "ModeTeam.h"

namespace {
  // 各種定数
  constexpr int MaxCount = 60;  //!< モード最大カウント
}

namespace Gyro {
  namespace Mode {
    ModeAMG::ModeAMG(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeAMG::~ModeAMG() {

    }

    bool ModeAMG::Init() {
      // リソース読み込み
      LoadResource();
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
      // AMG読み込み
      _amgHandle = LoadGraph("res/Logo/amglogo.png");
    }

    void ModeAMG::ChangeMode() {
      // モードAMGの削除
      _appMain.GetModeServer().PopBuck();
      // モードチームの登録
      _appMain.GetModeServer().AddMode("Team", std::make_shared<Mode::ModeTeam>(_appMain));
      _appMain.GetModeServer().TransionToMode("Team");
    }
  }
}
/*****************************************************************//**
 * @file    ModeTeam.cpp
 * @brief   モードチームクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "ModeTeam.h"
#include "ModeTitle.h"

namespace {
  // 各種定数
  constexpr int MaxCount = 60;  //!< モード最大カウント
}

namespace Gyro {
  namespace Mode {
    ModeTeam::ModeTeam(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeTeam::~ModeTeam() {

    }

    bool ModeTeam::Init() {
      return true;
    }

    bool ModeTeam::Enter() {
      // リソース読み込み
      LoadResource();
      return true;
    }

    bool ModeTeam::Exit() {
      return true;
    }

    bool ModeTeam::Process() {
      _count++;  // カウントを増やす
      // モード最大カウントを過ぎたら
      if (MaxCount < _count) {
        // モード切り替え
        ChangeMode();
      }
      return true;
    }

    bool ModeTeam::Draw() const {
      // チーム描画
      DrawGraph(0, 0, _teamHandle, false);
      return true;
    }

    void ModeTeam::LoadResource() {
      // リソースの読み込みは行われているか
      if (_isLoad) {
        return; // 読み込み済み
      }
      // 
      const AppFrame::Data::DivGraph divGraph("res/Logo/amglogo.png", 1, 1, 1, 1920, 1080);
      // AMG読み込み
      _app.GetResourceServer().LoadDivGraph("teamlogo", divGraph);
      // ハンドルの設定
      _teamHandle = _app.GetResourceServer().GetHandle("teamlogo");
      // 読み込み完了
      _isLoad = true;
    }

    void ModeTeam::ChangeMode() {
      // モードチームの削除
      _appMain.GetModeServer().PopBuck();
      // モードタイトルの登録
      _appMain.GetModeServer().AddMode("Title", std::make_shared<Mode::ModeTitle>(_appMain));
      // モードタイトル遷移
      _appMain.GetModeServer().TransionToMode("Title");
    }
  } // namespace Mode
} // namespace Gyro
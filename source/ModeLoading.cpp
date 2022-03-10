/*****************************************************************//**
 * @file   ModeLoading.cpp
 * @brief  モードローディングクラス
 * 
 * @author 土橋峡介
 * @date   March 2022
 *********************************************************************/
#include "ModeLoading.h"
#include "ModeGame.h"
#include "ModeTitle.h"

namespace Gyro {
  namespace Mode {
    ModeLoading::ModeLoading(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {

    }

    ModeLoading::~ModeLoading() {

    }

    bool ModeLoading::Init() {
      return true;
    }

    bool ModeLoading::Enter() {
      // リソース読み込み
      LoadResource();
      return true;
    }

    bool ModeLoading::Exit() {
      // 非同期処理フラグfalse
      SetUseASyncLoadFlag(false);
      return true;
    }

    bool ModeLoading::Process() {
      _cnt++;
      // 非同期の数が0ならGameへ移行
      if (GetASyncLoadNum() == 0) {
        ChangeMode();
      }
      return true;
    }

    bool ModeLoading::Draw() const {
      // 黒色の設定
      auto black = GetColor(0, 0, 0);
      // 背景を黒に
      DrawBox(0, 0, 1920, 1080, black, true);
      // ローディング画像の描画
      DrawGraph(1400, 950, _loadHandle[_cnt / 10 % 4], true);
      return true;
    }

    void ModeLoading::LoadResource() {
      // リソースは読み込まれているか
      if (_isLoad) {
        return; // 読み込み済み
      }
      // ロード画像読み込み
      LoadDivGraph("res/Loading/Loading2.png", 4, 2, 2, 500, 100, _loadHandle);
      _isLoad = true;
    }

    void ModeLoading::ChangeMode() {
      // モードローディングの削除
      _appMain.GetModeServer().PopBuck();
      // キーが登録されているか
      bool key = _app.GetModeServer().Contains("Game");
      if (!key) {
        // モードゲームの登録
        _appMain.GetModeServer().AddMode("Game", std::make_shared<Mode::ModeGame>(_appMain));
      }
      // モードゲーム遷移
      _appMain.GetModeServer().TransionToMode("Game");
    }
  } // namespace Mode
} // namespace Gyro
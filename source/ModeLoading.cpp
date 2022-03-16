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
#include "ObjectServer.h"
#include "EnemyWheel.h"
#include "EnemyWheelBoss.h"
#include "EnemyDrone.h"
#include "EnemyDroneBoss.h"

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
      // 自機以外を削除する
      _appMain.GetObjectServer().ObjectClear(true);
      // モデルカウントをリセット
      Enemy::EnemyDrone::ModelNumberReset();
      Enemy::EnemyDroneBoss::ModelNumberReset();
      Enemy::EnemyWheel::ModelNumberReset();
      Enemy::EnemyWheelBoss::ModelNumberReset();
      // オブジェクトサーバから複製品を削除する
      _appMain.GetModelServer().DeleteDuplicateModels("enemyWheel", false);
      _appMain.GetModelServer().DeleteDuplicateModels("enemyWheelBoss", false);
      _appMain.GetModelServer().DeleteDuplicateModels("enemyDrone", false);
      _appMain.GetModelServer().DeleteDuplicateModels("enemyDroneBoss", false);
      // 非同期処理フラグtrue
      SetUseASyncLoadFlag(true);
      // ボスステージ情報読み込み
      _appMain.GetStageComponent().ReleaseModel();
      _appMain.GetStageComponent().Init("boss");
      _appMain.GetStageComponent().CreateStage("boss");
      return true;
    }

    bool ModeLoading::Exit() {
      // 非同期処理フラグfalse
      SetUseASyncLoadFlag(false);
      // 画像の破棄
      DeleteGraph(_loadHandle[ 3 ]);
      return true;
    }

    bool ModeLoading::Process() {
      _cnt++;
      auto maxCnt = 180;
      if (maxCnt < _cnt) {
        // 非同期の数が0ならGameへ移行
        if (GetASyncLoadNum() == 0) {
          ChangeMode();
        }else {
          _cnt = 0;
        }
      }
      return true;
    }

    bool ModeLoading::Draw() const {
      // 黒色の設定
      auto black = GetColor(0, 0, 0);
      // 背景を黒に
      DrawBox(0, 0, 1920, 1080, black, true);
      // ローディング画像の描画
      DrawGraph(1400, 950, _loadHandle[_cnt / 20 % 4], true);
      return true;
    }

    void ModeLoading::LoadResource() {
      // リソースは読み込まれているか
      if (_isLoad) {
        return; // 読み込み済み
      }
      // ロード画像読み込み
      LoadDivGraph("res/Loading/Loading2.png", 4, 2, 2, 500, 100, _loadHandle);
      // 読み込み完了
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
    }
  } // namespace Mode
} // namespace Gyro
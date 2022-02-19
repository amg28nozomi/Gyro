/*****************************************************************//**
 * @file   ModeGame.cpp
 * @brief  インゲーム処理を行うモード
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ModeGame.h"
#include <memory>
#include "ApplicationMain.h"
#include "Player.h"
#include "EnemyWheel.h"
#include "PrimitiveBase.h"
#include "PrimitivePlane.h"
#include "ObjectServer.h"
#include "StageComponent.h"

namespace {
    constexpr auto TEXTURE = _T("res/water.png");
}

namespace Gyro {
  namespace Mode {

    ModeGame::ModeGame(Application::ApplicationMain& app) : ModeBase(*app.GetInstance()), _appMain(app) {
    }

    ModeGame::~ModeGame() {
    }

    bool ModeGame::Enter() {
      // オブジェクトを生成
      SetSpawn();
      return true;
    }

    bool ModeGame::Exit() {
      // 生成したオブジェクトを取り除く
      _appMain.GetObjectServer().Release();
      return true;
    }

    bool ModeGame::Init() {
      LoadResource(); // 各種リソースの読み取りを行う
      // 使用するデータの読み込みを記述する
      _plane.Initialize(35000.0, 150);
      _plane.Load(TEXTURE);
      _plane.Create();
      _appMain.GetStageComponent().Init();
      // 重力加速度をセットする
      AppMath::GravityBase::SetScale(-9.8f);
      return true;
    }

    bool ModeGame::Input(AppFrame::Application::InputOperation& input) {
      // 入力状態の取得
      auto device = input.GetXBoxState();
      namespace App = AppFrame::Application;
      // STARTボタンが押された場合、アプリケーションを終了する
      if (device.GetButton(XINPUT_BUTTON_START, App::InputTrigger)) {
        _appMain.RequestTerminate();
      }
#ifdef _DEBUG
      // デバッグ時限定:左スティックが押された場合、デバッグフラグを切り替える
      if (device.GetButton(XINPUT_BUTTON_RIGHT_THUMB, App::InputTrigger)) {
        _app.ChengeDebugFlag(); // デバッグフラグの切り替え
        if (_app.GetDebugFlag()) {
          _app.GetSoundComponent().PlayLoop("bgm");
          _app.GetSoundComponent().SetVolume("bgm", 50);
        } else {
          _app.GetSoundComponent().StopSound("bgm");
        }
      }
#endif
      return true;
    }

    bool ModeGame::Process() {
      // 入力処理
      Input(_app.GetOperation());
      // オブジェクトサーバの更新処理実行
      _appMain.GetObjectServer().Process();
      _appMain.GetEffect().Process();
      _plane.Process();

      return true;
    }

    bool ModeGame::Draw() const {
      // 描画処理呼び出し
      _appMain.GetObjectServer().Draw();
      _appMain.GetEffect().Draw();
      _appMain.GetStageComponent().Draw();
      _plane.Draw();

      return true;
    }

    Application::ApplicationMain& ModeGame::GetAppMain() {
      return _appMain;
    }

    void ModeGame::LoadResource() const {
      using ModelServer = AppFrame::Model::ModelServer;
      // 各種モデルハンドルの読み込み
      const ModelServer::ModelDatas mv1Models{
        {"player", "res/Player/Gyro Multimotion8.mv1"},     // 自機
        {"enemy", "res/Enemy/Wheel/Enemy_multimotion.mv1"}, // 敵
        {"sky", "res/SkySphere/skysphere.mv1"},             // スカイスフィア
        {"stage", "res/Stage/houseGEO_1.mv1"}               // ステージ
      };
      // モデルサーバで読み取りを行う
      _app.GetModelServer().AddMV1Model(mv1Models);
      // サウンド情報の読み取り
      using SoundServer = AppFrame::Sound::SoundServer;
      const SoundServer::SoundMap soundMap{
        {"bgm", "res/Sound/Stage.mp3"}
      };
      // サウンドサーバに登録
      _app.GetSoundServer().AddSounds(soundMap);
      // エフェクトリソースの読み取り
      LoadEffectResource();
    }

    void ModeGame::SetSpawn() {
      // スポーン情報の設定
      const Object::SpawnTable normal {
        // 自機の生成情報
        // 引数1:オブジェクトタイプ(0:自機　1:敵)
        // 引数2:ローカル座標
        // 引数3:向き
        // 引数4:スケール
        { Object::TypePlayer, {0.0f, 1500.0f, 0.0f,}, {0.0f, 0.0f, 0.0f,}, {1.0f, 1.0f, 1.0f}}
      };
      // エネミーテーブル
      const Object::EnemyTable enemy {
        // 陸上型エネミーの配置情報
        { Object::EnemyWheel, { 100.0f, 1500.0f, 100.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { -200.0f, 1500.0f, 200.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { 300.0f, 1500.0f, 200.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
        { Object::EnemyWheel, { -400.0f, 1500.0f, 200.0f}, {0.0f, 0.0f, 0.0f }, {2.0f, 2.0f, 2.0f}},
      };
      // 各種テーブルを基にスポーンテーブルを作成
      Object::SpawnData table{
        {0, std::make_tuple(normal, enemy)}
      };
      // スポーンテーブルの登録
      _appMain.GetSpawnServer().AddSpawnTable("test", table);
#ifndef _DEBUG
      _appMain.GetSpawnServer().SetStage("test");
#else
      try {
        _appMain.GetSpawnServer().SetStage("test");
      } catch (std::logic_error error) {
        OutputDebugString(error.what());
      }
#endif
      _appMain.GetSpawnServer().Spawn(0);
    }

    void ModeGame::LoadEffectResource() const {
      using EffectServer = Effect::EffectServer;
      // エフェクトハンドルの読み込み
      const EffectServer::EffectMap effectMap{
        {Effect::pWeakAttack1, "res/Effect/Player/WeakAttack1/player_weakattack1_1.efkefc"},
        {Effect::pWeakAttack2, "res/Effect/Player/WeakAttack2/player_weakattack2_2.efkefc"},
        {Effect::pWeakAttack3, "res/Effect/Player/WeakAttack3/player_weakattack3.efkefc"},
        {Effect::pWeakAttackEX, "res/Effect/Player/WeakAttackEX/player_weakattackEX.efkefc"},
        {Effect::pHeavyAttack1, "res/Effect/Player/HeavyAttack1/HeavyAttack1.efkefc"},
        {Effect::pHeavyAttack3, "res/Effect/Player/HeavyAttack3/HeavyAttack3.efkefc"},
        {Effect::pAirWeakAttack1, "res/Effect/Player/AirWeakAttack1/Player_attack_air_normal_01.efkefc"},
        {Effect::pAirWeakAttack2, "res/Effect/Player/AirWeakAttack2/Player_attack_air_normal_02.efkefc"},
        {Effect::pAirWeakAttack3, "res/Effect/Player/AirWeakAttack3/Player_attack_air_normal_03.efkefc"},
        {Effect::pAirHeavyAttack1, "res/Effect/Player/AirHeavyAttack1/Player_attack_air_heavy_01.efkefc"},
        {Effect::pAirHeavyAttack2, "res/Effect/Player/AirHeavyAttack2/Player_attack_air_heavy_02.efkefc"},
        {Effect::pUltActivate, "res/Effect/Player/Ult_Activate/Player_ult_activate.efkefc"},
        {Effect::pUltSlash, "res/Effect/Player/Ult_Slash/Player_ult_slash.efkefc"},
        {Effect::pHit, "res/Effect/Player/Hit/Hit.efkefc"},
        {Effect::eEyeLight, "res/Effect/Enemy/EyeLight/Enemy_EyeLight.efkefc"},
        {Effect::eGroundAttack, "res/Effect/Enemy/GroundAttack/Enemy_ground_attack.efkefc"},
        {Effect::eHit, "res/Effect/Enemy/Hit/Enemy_Hit.efkefc"},
        {Effect::eExprosion, "res/Effect/Enemy/Exprosion/Enemy_Exprosion.efkefc"},
        {Effect::stageBarrier, "res/Effect/stage_barrier/stage_barrier.efkefc"}
      };
      // エフェクト拡大率の登録
      const EffectServer::EffectMagniMap effectMagniMap{
        {Effect::pWeakAttack1, 5.0f},
        {Effect::pWeakAttack2, 5.0f},
        {Effect::pWeakAttack3, 5.0f},
        {Effect::pWeakAttackEX, 2.0f},
        {Effect::pHeavyAttack1, 20.0f},
        {Effect::pHeavyAttack3, 20.0f},
        {Effect::pAirWeakAttack1, 10.0f},
        {Effect::pAirWeakAttack2, 10.0f},
        {Effect::pAirWeakAttack3, 10.0f},
        {Effect::pAirHeavyAttack1, 10.0f},
        {Effect::pAirHeavyAttack2, 10.0f},
        {Effect::pUltActivate, 10.0f},
        {Effect::pUltSlash, 10.0f},
        {Effect::pHit, 20.0f},
        {Effect::eEyeLight, 20.0f},
        {Effect::eGroundAttack, 10.0f},
        {Effect::eHit, 20.0f},
        {Effect::eExprosion, 10.0f},
        {Effect::stageBarrier, 20.0f}
      };
      // エフェクトサーバに登録
      _appMain.GetEffectServer().AddEffects(effectMap, effectMagniMap);
    }
  } // namespace Mode
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectServer.cpp
 * @brief   エフェクトを管理するサーバクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "EffectServer.h"
#include "EffectBase.h"
#include "EffectPlayerJump.h"
#include "EffectPlayerHit.h"
#include "EffectPlayerWeakAttack1.h"
#include "EffectPlayerWeakAttack2.h"
#include "EffectPlayerWeakAttack3.h"
#include "EffectPlayerWeakAttackEX.h"
#include "EffectPlayerHeavyAttack1.h"
#include "EffectPlayerHeavyAttack2.h"
#include "EffectPlayerHeavyAttack3.h"
#include "EffectPlayerAirWeakAttack1.h"
#include "EffectPlayerAirWeakAttack2.h"
#include "EffectPlayerAirWeakAttack3.h"
#include "EffectPlayerAirHeavyAttack1.h"
#include "EffectPlayerAirHeavyAttack2.h"
#include "EffectPlayerUltActivate.h"
#include "EffectPlayerUltSlash.h"
#include "EffectEnemyEyeLight.h"
#include "EffectEnemyGroundAttack.h"
#include "EffectEnemyHit.h"
#include "EffectEnemyExprosion.h"
#include "EffectStageBarrier.h"
#include "EffectStageBoxDestroy.h"

namespace Gyro {
  namespace Effect {
    EffectServer::EffectServer(Application::ApplicationMain& app) : AppServer::ServerTemplateVector<std::shared_ptr<EffectBase>>(), _app(app) {
#ifdef _DEBUG
      SetServerName("EffectServer");
#endif
      // 各種コンテナを解放する
      ServerTemplateVector<std::shared_ptr<EffectBase>>::_registry.clear();
    }

    EffectServer::~EffectServer() {
      // エフェクトを解放する
      Release();
    }

    bool EffectServer::Release() {
      // コンテナの中身を解放する
      for (auto effect : _registry) {
        // エフェクト消去を呼び出す
        effect->DeadEffect();
      }
      // コンテナの中身を解放する
      _registry.clear();
      return true;
    }

    bool EffectServer::Process() {
      for (auto effect : _registry) {
        // 死亡状態か判定
        if (!effect->IsDead()) {
          effect->Process(); // 更新処理呼び出し
        }
      }
      // DXライブラリのカメラとEffekseerのカメラを同期する
      Effekseer_Sync3DSetting();
      // Effekseerにより再生中のエフェクトを更新する
      UpdateEffekseer3D();
      // 不要になったエフェクトを削除する
      std::erase_if(_registry, [](auto&& effect) {return effect->IsDead(); });
      return true;
    }

    bool EffectServer::Draw() {
      // Effekseerにより再生中のエフェクトを描画する
      DrawEffekseer3D();
      return true;
    }

    void EffectServer::MakeEffect(const int num, const AppMath::Vector4 position, const float radian) {
      // エフェクト識別生成
      switch (num) {
      case EffectNum::PlayerJump:
        // プレイヤージャンプ
        AddEffect(PlayerJump(position, radian));
        break;
      case EffectNum::PlayerHit:
        // プレイヤー被ダメ
        AddEffect(PlayerHit(position, radian));
        break;
      case EffectNum::PlayerWeakAttack1:
        // プレイヤー弱攻撃1
        AddEffect(PlayerWeakAttack1(position, radian));
        break;
      case EffectNum::PlayerWeakAttack2:
        // プレイヤー弱攻撃2
        AddEffect(PlayerWeakAttack2(position, radian));
        break;
      case EffectNum::PlayerWeakAttack3:
        // プレイヤー弱攻撃3
        AddEffect(PlayerWeakAttack3(position, radian));
        break;
      case EffectNum::PlayerHeavyAttack1:
        // プレイヤー強攻撃1
        AddEffect(PlayerHeavyAttack1(position, radian));
        break;
      case EffectNum::PlayerHeavyAttack2:
        // プレイヤー強攻撃2
        AddEffect(PlayerHeavyAttack2(position, radian));
        break;
      case EffectNum::PlayerHeavyAttack3:
        // プレイヤー強攻撃3
        AddEffect(PlayerHeavyAttack3(position, radian));
        break;
      case EffectNum::PlayerWeakAttackEX:
        // プレイヤー弱攻撃EX
        AddEffect(PlayerWeakAttackEX(position, radian));
        break;
      case EffectNum::PlayerAirWeakAttack1:
        // プレイヤー空中弱攻撃1
        AddEffect(PlayerAirWeakAttack1(position, radian));
        break;
      case EffectNum::PlayerAirWeakAttack2:
        // プレイヤー空中弱攻撃2
        AddEffect(PlayerAirWeakAttack2(position, radian));
        break;
      case EffectNum::PlayerAirWeakAttack3:
        // プレイヤー空中弱攻撃3
        AddEffect(PlayerAirWeakAttack3(position, radian));
        break;
      case EffectNum::PlayerAirHeavyAttack1:
        // プレイヤー空中強攻撃1
        AddEffect(PlayerAirHeavyAttack1(position, radian));
        break;
      case EffectNum::PlayerAirHeavyAttack2:
        // プレイヤー空中強攻撃2
        AddEffect(PlayerAirHeavyAttack2(position, radian));
        break;
      case EffectNum::EnemyEyeLight:
        // 敵眼光
        AddEffect(EnemyEyeLight(position, radian));
        break;
      case EffectNum::EnemyGroundAttack:
        // 敵地上攻撃
        AddEffect(EnemyGroundAttack(position, radian));
        break;
      case EffectNum::EnemyHit:
        // 敵被ダメ
        AddEffect(EnemyHit(position, radian));
        break;
      case EffectNum::EnemyExprosion:
        // 敵爆発
        AddEffect(EnemyExprosion(position, radian));
        break;
      case EffectNum::StageBarrier:
        // ステージバリア
        AddEffect(StageBarrier(position, radian));
        break;
      case EffectNum::StageBoxDestroy:
        // ステージ箱破壊
        AddEffect(StageBoxDestroy(position, radian));
        break;
      default:
#ifdef _DEBUG
        throw ("エフェクト識別番号がありません");
#endif
        break;
      }
    }

    void EffectServer::AddEffect(std::shared_ptr<EffectBase> effect) {
      // エフェクトがnullの場合エラー
      if (effect == nullptr) {
#ifdef _DEBUG
        throw ("エフェクトはnullptrです");
#endif
        return;
      }
      // 登録
      _registry.emplace_back(std::move(effect));
    }

    std::shared_ptr<EffectPlayerJump> EffectServer::PlayerJump(const AppMath::Vector4 position, const float radian) const {
      // プレイヤージャンプの生成
      auto playerJump = std::make_shared<EffectPlayerJump>(_app);
      // 位置・向き設定
      playerJump->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerJump);
    }

    std::shared_ptr<EffectPlayerHit> EffectServer::PlayerHit(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー被ダメの生成
      auto playerHit = std::make_shared<EffectPlayerHit>(_app);
      // 位置・向き設定
      playerHit->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerHit);
    }

    std::shared_ptr<EffectPlayerWeakAttack1> EffectServer::PlayerWeakAttack1(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー弱攻撃1の生成
      auto playerWeakAttack1 = std::make_shared<EffectPlayerWeakAttack1>(_app);
      // 位置・向き設定
      playerWeakAttack1->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerWeakAttack1);
    }

    std::shared_ptr<EffectPlayerWeakAttack2> EffectServer::PlayerWeakAttack2(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー弱攻撃2の生成
      auto playerWeakAttack2 = std::make_shared<EffectPlayerWeakAttack2>(_app);
      // 位置・向き設定
      playerWeakAttack2->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerWeakAttack2);
    }

    std::shared_ptr<EffectPlayerWeakAttack3> EffectServer::PlayerWeakAttack3(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー弱攻撃3の生成
      auto playerWeakAttack3 = std::make_shared<EffectPlayerWeakAttack3>(_app);
      // 位置・向き設定
      playerWeakAttack3->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerWeakAttack3);
    }

    std::shared_ptr<EffectPlayerWeakAttackEX> EffectServer::PlayerWeakAttackEX(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー弱攻撃EXの生成
      auto playerWeakAttackEX = std::make_shared<EffectPlayerWeakAttackEX>(_app);
      // 位置・向き設定
      playerWeakAttackEX->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerWeakAttackEX);
    }

    std::shared_ptr<EffectPlayerHeavyAttack1> EffectServer::PlayerHeavyAttack1(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー強攻撃1の生成
      auto playerHeavyAttack1 = std::make_shared<EffectPlayerHeavyAttack1>(_app);
      // 位置・向き設定
      playerHeavyAttack1->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerHeavyAttack1);
    }

    std::shared_ptr<EffectPlayerHeavyAttack2> EffectServer::PlayerHeavyAttack2(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー強攻撃2の生成
      auto playerHeavyAttack2 = std::make_shared<EffectPlayerHeavyAttack2>(_app);
      // 位置・向き設定
      playerHeavyAttack2->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerHeavyAttack2);
    }

    std::shared_ptr<EffectPlayerHeavyAttack3> EffectServer::PlayerHeavyAttack3(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー強攻撃3の生成
      auto playerHeavyAttack3 = std::make_shared<EffectPlayerHeavyAttack3>(_app);
      // 位置・向き設定
      playerHeavyAttack3->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerHeavyAttack3);
    }

    std::shared_ptr<EffectPlayerAirWeakAttack1> EffectServer::PlayerAirWeakAttack1(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー空中弱攻撃1の生成
      auto playerAirWeakAttack1 = std::make_shared<EffectPlayerAirWeakAttack1>(_app);
      // 位置・向き設定
      playerAirWeakAttack1->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerAirWeakAttack1);
    }

    std::shared_ptr<EffectPlayerAirWeakAttack2> EffectServer::PlayerAirWeakAttack2(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー空中弱攻撃2の生成
      auto playerAirWeakAttack2 = std::make_shared<EffectPlayerAirWeakAttack2>(_app);
      // 位置・向き設定
      playerAirWeakAttack2->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerAirWeakAttack2);
    }

    std::shared_ptr<EffectPlayerAirWeakAttack3> EffectServer::PlayerAirWeakAttack3(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー空中弱攻撃3の生成
      auto playerAirWeakAttack3 = std::make_shared<EffectPlayerAirWeakAttack3>(_app);
      // 位置・向き設定
      playerAirWeakAttack3->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerAirWeakAttack3);
    }

    std::shared_ptr<EffectPlayerAirHeavyAttack1> EffectServer::PlayerAirHeavyAttack1(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー空中強攻撃1の生成
      auto playerAirHeavyAttack1 = std::make_shared<EffectPlayerAirHeavyAttack1>(_app);
      // 位置・向き設定
      playerAirHeavyAttack1->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerAirHeavyAttack1);
    }

    std::shared_ptr<EffectPlayerAirHeavyAttack2> EffectServer::PlayerAirHeavyAttack2(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー空中強攻撃2の生成
      auto playerAirHeavyAttack2 = std::make_shared<EffectPlayerAirHeavyAttack2>(_app);
      // 位置・向き設定
      playerAirHeavyAttack2->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerAirHeavyAttack2);
    }

    std::shared_ptr<EffectPlayerUltActivate> EffectServer::PlayerUltActivate(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー必殺発動の生成
      auto playerUltActivate = std::make_shared<EffectPlayerUltActivate>(_app);
      // 位置・向き設定
      playerUltActivate->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerUltActivate);
    }

    std::shared_ptr<EffectPlayerUltSlash> EffectServer::PlayerUltSlash(const AppMath::Vector4 position, const float radian) const {
      // プレイヤー必殺攻撃の生成
      auto playerUltSlash = std::make_shared<EffectPlayerUltSlash>(_app);
      // 位置・向き設定
      playerUltSlash->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(playerUltSlash);
    }

    std::shared_ptr<EffectEnemyEyeLight> EffectServer::EnemyEyeLight(const AppMath::Vector4 position, const float radian) const {
      // 敵眼光の生成
      auto enemyEyeLight = std::make_shared<EffectEnemyEyeLight>(_app);
      // 位置・向き設定
      enemyEyeLight->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(enemyEyeLight);
    }

    std::shared_ptr<EffectEnemyGroundAttack> EffectServer::EnemyGroundAttack(const AppMath::Vector4 position, const float radian) const {
      // 敵地上攻撃の生成
      auto enemyGroundAttack = std::make_shared<EffectEnemyGroundAttack>(_app);
      // 位置・向き設定
      enemyGroundAttack->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(enemyGroundAttack);
    }

    std::shared_ptr<EffectEnemyHit> EffectServer::EnemyHit(const AppMath::Vector4 position, const float radian) const {
      // 敵被ダメの生成
      auto enemyHit = std::make_shared<EffectEnemyHit>(_app);
      // 位置・向き設定
      enemyHit->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(enemyHit);
    }

    std::shared_ptr<EffectEnemyExprosion> EffectServer::EnemyExprosion(const AppMath::Vector4 position, const float radian) const {
      // 敵爆発の生成
      auto enemyExprosion = std::make_shared<EffectEnemyExprosion>(_app);
      // 位置・向き設定
      enemyExprosion->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(enemyExprosion);
    }

    std::shared_ptr<EffectStageBarrier> EffectServer::StageBarrier(const AppMath::Vector4 position, const float radian) const {
      // ステージバリアの生成
      auto stageBarrier = std::make_shared<EffectStageBarrier>(_app);
      // 位置・向き設定
      stageBarrier->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(stageBarrier);
    }

    std::shared_ptr<EffectStageBoxDestroy> EffectServer::StageBoxDestroy(const AppMath::Vector4 position, const float radian) const {
      // ステージ箱破壊の生成
      auto stageBoxDestroy = std::make_shared<EffectStageBoxDestroy>(_app);
      // 位置・向き設定
      stageBoxDestroy->SetEffectParameter(position, radian);
      // 生成したシェアードポインタを返す
      return std::move(stageBoxDestroy);
    }
  } // namespace Effect
} // namespace Gyro
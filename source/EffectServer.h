/*****************************************************************//**
 * @file    EffectServer.h
 * @brief   エフェクトを管理するサーバクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"

 /**
  * @brief ゲームベース
  */
namespace Gyro {
  /**
   * @brief エフェクトベース
   */
  namespace Effect {
    namespace AppServer = AppFrame::Server;
    namespace AppMath = AppFrame::Math;
    class EffectBase;
    class EffectPlayerJump;
    class EffectPlayerHit;
    class EffectPlayerWeakAttack1;
    class EffectPlayerWeakAttack2;
    class EffectPlayerWeakAttack3;
    class EffectPlayerWeakAttackEX;
    class EffectPlayerHeavyAttack1;
    class EffectPlayerHeavyAttack2;
    class EffectPlayerHeavyAttack3;
    class EffectPlayerAirWeakAttack1;
    class EffectPlayerAirWeakAttack2;
    class EffectPlayerAirWeakAttack3;
    class EffectPlayerAirHeavyAttack1;
    class EffectPlayerAirHeavyAttack2;
    class EffectPlayerUltActivate;
    class EffectPlayerUltSlash;
    class EffectEnemyEyeLight;
    class EffectEnemyGroundAttack;
    class EffectEnemyHit;
    class EffectEnemyExprosion;
    class EffectStageBarrier;
    class EffectStageBoxDestroy;
    /**
     * @class EffectServer
     * @brief エフェクトを管理するサーバクラス
     */
    class EffectServer : AppServer::ServerTemplateVector<std::shared_ptr<EffectBase>> {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションメインの参照
       */
      EffectServer(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectServer();
      /**
       * @brief  解放
       * @return true
       */
      bool Release() override;
      /**
       * @brief  更新
       * @return true
       */
      bool Process();
      /**
       * @brief  描画
       * @return true
       */
      bool Draw();
      /**
       * @brief  エフェクト生成
       * @param  num エフェクト識別番号
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       */
      void MakeEffect(const int num, const AppMath::Vector4 position, const float radian);

    private:
      /**
       * @brief  エフェクトの登録
       * @param  エフェクトのシェアードポインタ
       */
      void AddEffect(std::shared_ptr<EffectBase> effect);
      /**
       * @brief  プレイヤージャンプの生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤージャンプのシェアードポインタ
       */
      std::shared_ptr<EffectPlayerJump> PlayerJump(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー被ダメの生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー被ダメのシェアードポインタ
       */
      std::shared_ptr<EffectPlayerHit> PlayerHit(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー弱攻撃1の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー弱攻撃1のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerWeakAttack1> PlayerWeakAttack1(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー弱攻撃2の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー弱攻撃2のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerWeakAttack2> PlayerWeakAttack2(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー弱攻撃3の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー弱攻撃3のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerWeakAttack3> PlayerWeakAttack3(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー弱攻撃EXの生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー弱攻撃EXのシェアードポインタ
       */
      std::shared_ptr<EffectPlayerWeakAttackEX> PlayerWeakAttackEX(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー強攻撃1の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー強攻撃1のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerHeavyAttack1> PlayerHeavyAttack1(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー強攻撃2の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー強攻撃2のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerHeavyAttack2> PlayerHeavyAttack2(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー強攻撃3の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー強攻撃3のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerHeavyAttack3> PlayerHeavyAttack3(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー空中弱攻撃1の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー空中弱攻撃1のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerAirWeakAttack1> PlayerAirWeakAttack1(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー空中弱攻撃2の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー空中弱攻撃2のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerAirWeakAttack2> PlayerAirWeakAttack2(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー空中弱攻撃3の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー空中弱攻撃3のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerAirWeakAttack3> PlayerAirWeakAttack3(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー空中強攻撃1の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー空中強攻撃1のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerAirHeavyAttack1> PlayerAirHeavyAttack1(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー空中強攻撃2の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー空中強攻撃2のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerAirHeavyAttack2> PlayerAirHeavyAttack2(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー必殺発動の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー必殺発動のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerUltActivate> PlayerUltActivate(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー必殺攻撃の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー必殺攻撃のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerUltSlash> PlayerUltSlash(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  敵眼光の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return 敵眼光のシェアードポインタ
       */
      std::shared_ptr<EffectEnemyEyeLight> EnemyEyeLight(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  敵地上攻撃の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return 敵地上攻撃のシェアードポインタ
       */
      std::shared_ptr<EffectEnemyGroundAttack> EnemyGroundAttack(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  敵被ダメの生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return 敵被ダメのシェアードポインタ
       */
      std::shared_ptr<EffectEnemyHit> EnemyHit(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  敵爆発の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return 敵爆発のシェアードポインタ
       */
      std::shared_ptr<EffectEnemyExprosion> EnemyExprosion(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  ステージバリアの生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return ステージバリアのシェアードポインタ
       */
      std::shared_ptr<EffectStageBarrier> StageBarrier(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  ステージ箱破壊の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return ステージ箱破壊のシェアードポインタ
       */
      std::shared_ptr<EffectStageBoxDestroy> StageBoxDestroy(const AppMath::Vector4 position, const float radian) const;

      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
    };
  } // namespace Effect

  // エフェクト識別番号定数
  namespace EffectNum {
    // 1**:プレイヤー
      // 10*:汎用
    constexpr int PlayerJump = 100;             //!< プレイヤージャンプ
    constexpr int PlayerHit = 101;              //!< プレイヤー被ダメ
    // 11*:弱攻撃
    constexpr int PlayerWeakAttack1 = 111;      //!< プレイヤー弱攻撃1
    constexpr int PlayerWeakAttack2 = 112;      //!< プレイヤー弱攻撃2
    constexpr int PlayerWeakAttack3 = 113;      //!< プレイヤー弱攻撃3
    constexpr int PlayerWeakAttackEX = 114;     //!< プレイヤー弱攻撃EX
    // 12*:強攻撃
    constexpr int PlayerHeavyAttack1 = 121;     //!< プレイヤー強攻撃1
    constexpr int PlayerHeavyAttack2 = 122;     //!< プレイヤー強攻撃2
    constexpr int PlayerHeavyAttack3 = 123;     //!< プレイヤー強攻撃3
    // 13*:空中弱攻撃
    constexpr int PlayerAirWeakAttack1 = 131;   //!< プレイヤー空中弱攻撃1
    constexpr int PlayerAirWeakAttack2 = 132;   //!< プレイヤー空中弱攻撃2
    constexpr int PlayerAirWeakAttack3 = 133;   //!< プレイヤー空中弱攻撃3
    // 14*:空中強攻撃
    constexpr int PlayerAirHeavyAttack1 = 141;  //!< プレイヤー空中強攻撃1
    constexpr int PlayerAirHeavyAttack2 = 142;  //!< プレイヤー空中強攻撃2
    // 15*:必殺技
    constexpr int PlayerUltActivate = 150;      //!< プレイヤー必殺発動
    constexpr int PlayerUltSlash = 151;         //!< プレイヤー必殺攻撃
  // 2**:敵
    constexpr int EnemyEyeLight = 200;      //!< 敵眼光
    constexpr int EnemyGroundAttack = 201;  //!< 敵地上攻撃
    constexpr int EnemyHit = 202;           //!< 敵被ダメ
    constexpr int EnemyExprosion = 203;     //!< 敵爆発
  // 3**:ステージ
    constexpr int StageBarrier = 300;     //!< ステージバリア
    constexpr int StageBoxDestroy = 301;  //!< ステージ箱破壊
  } // namespace EffectNum
} // namespace Gyro
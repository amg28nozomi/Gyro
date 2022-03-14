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
    class EffectPlayerDash;
    class EffectPlayerJump;
    class EffectPlayerLanding;
    class EffectPlayerHit;
    class EffectPlayerAvoidance;
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
    class EffectEnemyGroundAttack1;
    class EffectEnemyGroundAttack2;
    class EffectEnemyAirAttack;
    class EffectEnemyHit;
    class EffectEnemyExprosion;
    class EffectEnemyBossEyeLight;
    class EffectEnemyBossGroundAttack1;
    class EffectEnemyBossGroundAttack2;
    class EffectEnemyBossAirAttack;
    class EffectEnemyBossHit;
    class EffectEnemyBossExprosion;
    class EffectStageBarrier;
    class EffectStageBoxDestroy;
    class EffectStageHeal;
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
       * @brief  エフェクト生成(サーバに登録)
       * @param  num エフェクト識別番号
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       */
      void MakeEffect(const int num, const AppMath::Vector4 position, const float radian);
      /**
       * @brief  必殺攻撃エフェクト終了判定の設定
       * @param  flag 終了フラグ
       */
      void SetUltSlashEnd(const bool flag) {
        _ultSlashEnd = flag;
      }
      /**
       * @brief  必殺攻撃エフェクト終了判定の取得
       * @return true:終了
       *         false:再生中(未再生)
       */
      bool GetUltSlashEnd() {
        return _ultSlashEnd;
      }

    private:
      /**
       * @brief  エフェクトの登録
       * @param  エフェクトのシェアードポインタ
       */
      void AddEffect(std::shared_ptr<EffectBase> effect);
      /**
       * @brief  プレイヤーダッシュの生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤーダッシュのシェアードポインタ
       */
      std::shared_ptr<EffectPlayerDash> PlayerDash(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤージャンプの生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤージャンプのシェアードポインタ
       */
      std::shared_ptr<EffectPlayerJump> PlayerJump(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー着地の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー着地のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerLanding> PlayerLanding(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー被ダメの生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー被ダメのシェアードポインタ
       */
      std::shared_ptr<EffectPlayerHit> PlayerHit(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  プレイヤー回避の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return プレイヤー回避のシェアードポインタ
       */
      std::shared_ptr<EffectPlayerAvoidance> PlayerAvoidance(const AppMath::Vector4 position, const float radian) const;
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
       * @brief  敵地上攻撃1の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return 敵地上攻撃1のシェアードポインタ
       */
      std::shared_ptr<EffectEnemyGroundAttack1> EnemyGroundAttack1(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  敵地上攻撃2の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return 敵地上攻撃2のシェアードポインタ
       */
      std::shared_ptr<EffectEnemyGroundAttack2> EnemyGroundAttack2(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  敵空中攻撃の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return 敵空中攻撃のシェアードポインタ
       */
      std::shared_ptr<EffectEnemyAirAttack> EnemyAirAttack(const AppMath::Vector4 position, const float radian) const;
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
       * @brief  敵ボス眼光の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return 敵ボス眼光のシェアードポインタ
       */
      std::shared_ptr<EffectEnemyBossEyeLight> EnemyBossEyeLight(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  敵ボス地上攻撃1の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return 敵ボス地上攻撃1のシェアードポインタ
       */
      std::shared_ptr<EffectEnemyBossGroundAttack1> EnemyBossGroundAttack1(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  敵ボス地上攻撃2の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return 敵ボス地上攻撃2のシェアードポインタ
       */
      std::shared_ptr<EffectEnemyBossGroundAttack2> EnemyBossGroundAttack2(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  敵ボス空中攻撃の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return 敵ボス空中攻撃のシェアードポインタ
       */
      std::shared_ptr<EffectEnemyBossAirAttack> EnemyBossAirAttack(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  敵ボス被ダメの生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return 敵ボス被ダメのシェアードポインタ
       */
      std::shared_ptr<EffectEnemyBossHit> EnemyBossHit(const AppMath::Vector4 position, const float radian) const;
      /**
       * @brief  敵ボス爆発の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return 敵ボス爆発のシェアードポインタ
       */
      std::shared_ptr<EffectEnemyBossExprosion> EnemyBossExprosion(const AppMath::Vector4 position, const float radian) const;
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
      /**
       * @brief  ステージ回復の生成
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       * @return ステージ回復のシェアードポインタ
       */
      std::shared_ptr<EffectStageHeal> StageHeal(const AppMath::Vector4 position, const float radian) const;

      bool _ultSlashEnd{ false };  //!< 必殺攻撃エフェクト終了判定
      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
    };
  } // namespace Effect

  // エフェクト識別番号定数
  namespace EffectNum {
  // 1**:プレイヤー
    // 10*:汎用
    constexpr int PlayerDash = 100;       //!< プレイヤーダッシュ
    constexpr int PlayerJump = 101;       //!< プレイヤージャンプ
    constexpr int PlayerLanding = 102;    //!< プレイヤー着地
    constexpr int PlayerHit = 103;        //!< プレイヤー被ダメ
    constexpr int PlayerAvoidance = 104;  //!< プレイヤー回避
    // 11*:弱攻撃
    constexpr int PlayerWeakAttack1 = 111;   //!< プレイヤー弱攻撃1
    constexpr int PlayerWeakAttack2 = 112;   //!< プレイヤー弱攻撃2
    constexpr int PlayerWeakAttack3 = 113;   //!< プレイヤー弱攻撃3
    constexpr int PlayerWeakAttackEX = 114;  //!< プレイヤー弱攻撃EX
    // 12*:強攻撃
    constexpr int PlayerHeavyAttack1 = 121;  //!< プレイヤー強攻撃1
    constexpr int PlayerHeavyAttack2 = 122;  //!< プレイヤー強攻撃2
    constexpr int PlayerHeavyAttack3 = 123;  //!< プレイヤー強攻撃3
    // 13*:空中弱攻撃
    constexpr int PlayerAirWeakAttack1 = 131;  //!< プレイヤー空中弱攻撃1
    constexpr int PlayerAirWeakAttack2 = 132;  //!< プレイヤー空中弱攻撃2
    constexpr int PlayerAirWeakAttack3 = 133;  //!< プレイヤー空中弱攻撃3
    // 14*:空中強攻撃
    constexpr int PlayerAirHeavyAttack1 = 141;  //!< プレイヤー空中強攻撃1
    constexpr int PlayerAirHeavyAttack2 = 142;  //!< プレイヤー空中強攻撃2
    // 15*:必殺技
    constexpr int PlayerUltActivate = 150;  //!< プレイヤー必殺発動
    constexpr int PlayerUltSlash = 151;     //!< プレイヤー必殺攻撃
  // 2**:敵
    // 20*:通常
    constexpr int EnemyEyeLight = 200;       //!< 敵眼光
    constexpr int EnemyGroundAttack1 = 201;  //!< 敵地上攻撃1
    constexpr int EnemyGroundAttack2 = 202;  //!< 敵地上攻撃2
    constexpr int EnemyAirAttack = 203;      //!< 敵空中攻撃
    constexpr int EnemyHit = 204;            //!< 敵被ダメ
    constexpr int EnemyExprosion = 205;      //!< 敵爆発
    // 21*:ボス
    constexpr int EnemyBossEyeLight = 210;       //!< 敵ボス眼光
    constexpr int EnemyBossGroundAttack1 = 211;  //!< 敵ボス地上攻撃1
    constexpr int EnemyBossGroundAttack2 = 212;  //!< 敵ボス地上攻撃2
    constexpr int EnemyBossAirAttack = 213;      //!< 敵ボス空中攻撃
    constexpr int EnemyBossHit = 214;            //!< 敵ボス被ダメ
    constexpr int EnemyBossExprosion = 215;      //!< 敵ボス爆発
  // 3**:ステージ
    constexpr int StageBarrier = 300;     //!< ステージバリア
    constexpr int StageBoxDestroy = 301;  //!< ステージ箱破壊
    constexpr int StageHeal = 302;        //!< ステージ回復
  } // namespace EffectNum
} // namespace Gyro
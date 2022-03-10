/*****************************************************************//**
 * @file    EffectLoadServer.h
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
    /**
     * @class EffectLoadServer
     * @brief エフェクトを管理するサーバクラス
     */
    class EffectLoadServer : AppServer::ServerTemplateUnordered<std::string, int> {
    public:
      /**
       * @brief  エフェクト情報を格納する動的配列
       * @param  エフェクトファイルに紐づける文字列
       * @param  エフェクトファイルのパス
       * @param  エフェクト拡大率
       */
      using EffectMap = std::vector<std::tuple<std::string_view, std::string_view, float>>;
      /**
       * @brief  コンストラクタ
       */
      EffectLoadServer();
      /**
       * @brief  解放処理
       * @return true
       */
      bool Release() override;
      /**
       * @brief  コンテナを使用したエフェクトファイルの読み取り
       * @param  effectMap エフェクト情報が格納されたコンテナ
       */
      void AddEffects(const EffectMap& effectMap);
      /**
       * @brief  指定したエフェクトハンドルの取得
       * @param  key 対象のエフェクトハンドルに紐づけられた文字列
       * @return エフェクトハンドル
       *         キーが有効ではない場合は-1を返す
       */
      int GetEffectHandle(std::string_view key) const;

    private:
      /**
       * @brief  エフェクトファイルの読み取り
       * @param  key エフェクトハンドルに紐づける文字列
       * @param  effectFile エフェクトファイルのパス
       * @param  magni エフェクト拡大率
       * @return true:正常終了
       *         false:読み取り失敗
       */
      bool AddEffect(std::string_view key, const std::filesystem::path effectFile, const float magni);
    };
  } // namespace Effect

  // エフェクトキー定数
  namespace EffectKey {
  // プレイヤー
    constexpr std::string_view PlayerJump = "PlayerJump";                        //!< プレイヤージャンプ
    constexpr std::string_view PlayerHit = "PlayerHit";                          //!< プレイヤー被ダメ
    constexpr std::string_view PlayerWeakAttack1 = "PlayerWeakAttack1";          //!< プレイヤー弱攻撃1
    constexpr std::string_view PlayerWeakAttack2 = "PlayerWeakAttack2";          //!< プレイヤー弱攻撃2
    constexpr std::string_view PlayerWeakAttack3 = "PlayerWeakAttack3";          //!< プレイヤー弱攻撃3
    constexpr std::string_view PlayerWeakAttackEX = "PlayerWeakAttackEX";        //!< プレイヤー弱攻撃EX
    constexpr std::string_view PlayerHeavyAttack1 = "PlayerHeavyAttack1";        //!< プレイヤー強攻撃1
    constexpr std::string_view PlayerHeavyAttack2 = "PlayerHeavyAttack2";        //!< プレイヤー強攻撃2
    constexpr std::string_view PlayerHeavyAttack3 = "PlayerHeavyAttack3";        //!< プレイヤー強攻撃3
    constexpr std::string_view PlayerAirWeakAttack1 = "PlayerAirWeakAttack1";    //!< プレイヤー空中弱攻撃1
    constexpr std::string_view PlayerAirWeakAttack2 = "PlayerAirWeakAttack2";    //!< プレイヤー空中弱攻撃2
    constexpr std::string_view PlayerAirWeakAttack3 = "PlayerAirWeakAttack3";    //!< プレイヤー空中弱攻撃3
    constexpr std::string_view PlayerAirHeavyAttack1 = "PlayerAirHeavyAttack1";  //!< プレイヤー空中強攻撃1
    constexpr std::string_view PlayerAirHeavyAttack2 = "PlayerAirHeavyAttack2";  //!< プレイヤー空中強攻撃2
    constexpr std::string_view PlayerUltActivate = "PlayerUltActivate";          //!< プレイヤー必殺発動
    constexpr std::string_view PlayerUltSlash = "PlayerUltSlash";                //!< プレイヤー必殺攻撃
  // 敵
    constexpr std::string_view EnemyEyeLight = "EnemyEyeLight";            //!< 敵眼光
    constexpr std::string_view EnemyGroundAttack1 = "EnemyGroundAttack1";  //!< 敵地上攻撃1
    constexpr std::string_view EnemyGroundAttack2 = "EnemyGroundAttack2";  //!< 敵地上攻撃2
    constexpr std::string_view EnemyAirAttack = "EnemyAirAttack";          //!< 敵空中攻撃
    constexpr std::string_view EnemyHit = "EnemyHit";                      //!< 敵被ダメ
    constexpr std::string_view EnemyExprosion = "EnemyExprosion";          //!< 敵爆発
    //ボス
    constexpr std::string_view EnemyBossEyeLight = "EnemyBossEyeLight";            //!< 敵ボス眼光
    constexpr std::string_view EnemyBossGroundAttack1 = "EnemyBossGroundAttack1";  //!< 敵ボス地上攻撃1
    constexpr std::string_view EnemyBossGroundAttack2 = "EnemyBossGroundAttack2";  //!< 敵ボス地上攻撃2
    constexpr std::string_view EnemyBossAirAttack = "EnemyBossAirAttack";          //!< 敵ボス空中攻撃
    constexpr std::string_view EnemyBossHit = "EnemyBossHit";                      //!< 敵ボス被ダメ
    constexpr std::string_view EnemyBossExprosion = "EnemyBossExprosion";          //!< 敵ボス爆発
  // ステージ
    constexpr std::string_view StageBarrier = "StageBarrier";        //!< ステージバリア
    constexpr std::string_view StageBoxDestroy = "StageBoxDestroy";  //!< ステージ箱破壊
  } // namespace EffectKey
} // namespace Gyro
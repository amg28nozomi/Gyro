/*****************************************************************//**
 * @file    EffectComponent.h
 * @brief   エフェクトクラス
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
    namespace AppMath = AppFrame::Math;
    /**
     * @class EffecComponent
     * @brief エフェクトクラス
     */
    class EffectComponent {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectComponent(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectComponent();
      /**
       * @brief  更新
       */
      void Process();
      /**
       * @brief  描画
       */
      void Draw() const;
      /**
       * @brief  エフェクト再生
       * @param  key エフェクトキー
       * @param  position エフェクト位置
       * @param  radian エフェクト向き
       */
      void PlayEffect(const std::string_view key, const AppMath::Vector4 position, const float radian);

    private:
      /**
       * @brief  エフェクトハンドルの取得
       * @param  key エフェクトキー
       */
      int GetEffectHandle(const std::string_view key);

      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
    };

    // エフェクトキー定数化
    // プレイヤー
    constexpr std::string_view PlayerWeakAttack1 = "P_WeakAttack1";          //!< プレイヤー弱攻撃1
    constexpr std::string_view PlayerWeakAttack2 = "P_WeakAttack2";          //!< プレイヤー弱攻撃2
    constexpr std::string_view PlayerWeakAttack3 = "P_WeakAttack3";          //!< プレイヤー弱攻撃3
    constexpr std::string_view PlayerWeakAttackEX = "P_WeakAttackEX";        //!< プレイヤー弱攻撃EX
    constexpr std::string_view PlayerHeavyAttack1 = "P_HeavyAttack1";        //!< プレイヤー強攻撃1
    constexpr std::string_view PlayerHeavyAttack3 = "P_HeavyAttack3";        //!< プレイヤー強攻撃3
    constexpr std::string_view PlayerAirWeakAttack1 = "P_AirWeakAttack1";    //!< プレイヤー空中弱攻撃1
    constexpr std::string_view PlayerAirWeakAttack2 = "P_AirWeakAttack2";    //!< プレイヤー空中弱攻撃1
    constexpr std::string_view PlayerAirWeakAttack3 = "P_AirWeakAttack3";    //!< プレイヤー空中弱攻撃1
    constexpr std::string_view PlayerAirHeavyAttack1 = "P_AirHeavyAttack1";  //!< プレイヤー空中弱攻撃1
    constexpr std::string_view PlayerAirHeavyAttack2 = "P_AirHeavyAttack2";  //!< プレイヤー空中弱攻撃1
    constexpr std::string_view PlayerUltActivate = "P_Ult_Activate";         //!< プレイヤー必殺
    constexpr std::string_view PlayerUltSlash = "P_Ult_Slash";               //!< プレイヤー必殺
    constexpr std::string_view PlayerJump = "P_Jump";                        //!< プレイヤージャンプ
    constexpr std::string_view PlayerHit = "P_Hit";                          //!< プレイヤー被ダメ
    // 敵
    constexpr std::string_view EnemyEyeLight = "E_EyeLight";          //!< 敵発見
    constexpr std::string_view EnemyGroundAttack = "E_GroundAttack";  //!< 敵回転攻撃
    constexpr std::string_view EnemyHit = "E_Hit";                    //!< 敵被ダメ
    constexpr std::string_view EnemyExprosion = "E_Exprosion";        //!< 敵爆発
    // ステージ
    constexpr std::string_view StageBarrier = "Stage_Barrier";  //!< ステージバリア
    constexpr std::string_view BoxDestroy = "Box_Destroy";      //!< 箱破壊
  } // namespace Effect
} // namespace Gyro
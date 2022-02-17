/*****************************************************************//**
 * @file    EffectComponent.h
 * @brief   エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "../ApplicationMain.h"

 /** 作品用名前空間 */
namespace Gyro {
  /** エフェクト用名前空間 */
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
       * @param  rotation エフェクト向き
       */
      void PlayEffect(const std::string_view key, const AppMath::Vector4 position, const float radian);

    private:
      /**
       * @brief  エフェクトハンドルの取得
       * @param  key エフェクトキー
       */
      int GetEffectHandle(const std::string_view key);

      Application::ApplicationMain& _app; //!< アプリケーションの参照
    };

    // エフェクトキー定数化
    constexpr std::string_view eEyeLight = "E_EyeLight";              //!< 敵発見
    constexpr std::string_view eGroundAttack = "E_GroundAttack";      //!< 敵回転攻撃
    constexpr std::string_view eHit = "E_Hit";                        //!< 敵被ダメ
    constexpr std::string_view eExprosion = "E_Exprosion";            //!< 敵爆発
    constexpr std::string_view pWeakAttack1 = "P_WeakAttack1";        //!< プレイヤー弱攻撃1
    constexpr std::string_view pWeakAttack2 = "P_WeakAttack2";        //!< プレイヤー弱攻撃2
    constexpr std::string_view pWeakAttack3 = "P_WeakAttack3";        //!< プレイヤー弱攻撃3
    constexpr std::string_view pWeakAttackEX = "P_WeakAttackEX";      //!< プレイヤー弱攻撃EX
    constexpr std::string_view pHeavyAttack1 = "P_HeavyAttack1";      //!< プレイヤー強攻撃1
    constexpr std::string_view pHeavyAttack3 = "P_HeavyAttack3";      //!< プレイヤー強攻撃3
    constexpr std::string_view pAirWeakAttack1 = "P_AirWeakAttack1";  //!< プレイヤー空中弱攻撃1
    constexpr std::string_view pUltActivate = "P_Ult_Activate";       //!< プレイヤー必殺
    constexpr std::string_view pUltSlash = "P_Ult_Slash";             //!< プレイヤー必殺
    constexpr std::string_view pHit = "P_Hit";                        //!< プレイヤー被ダメ
    constexpr std::string_view stageBarrier = "Stage_Barrier";        //!< ステージバリア
  } // namespace Effect
} // namespace Gyro
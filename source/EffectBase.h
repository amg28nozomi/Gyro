/*****************************************************************//**
 * @file    EffectBase.h
 * @brief   エフェクトの基底クラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"
#include "Player.h"

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
     * @class EffectBase
     * @brief エフェクトの基底クラス
     */
    class EffectBase {
    public:
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションの参照
       */
      EffectBase(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EffectBase();
      /**
       * @brief  初期化
       */
      virtual void Init();
      /**
       * @brief  更新
       */
      virtual void Process();
      /**
       * @brief  エフェクト再生
       */
      virtual void PlayEffect();
      /**
       * @brief  エフェクト消去
       */
      virtual void DeadEffect();
      /**
       * @brief  エフェクト位置・向き設定
       * @param  position 位置
       * @param  radian 向き(y回転, ラジアン)
       */
      virtual void SetEffectParameter(const AppMath::Vector4 position, const float radian) {
        _ePos = position, _eRadY = radian;
      }
      /**
       * @brief  死亡状態かの判定
       * @return true:死亡状態
       *         false:死んでいない
       */
      virtual bool IsDead() const {
        return _effectState == EffectState::Dead;
      }

    protected:
      /**
       * @brief  エフェクトの状態を表す列挙型クラス
       */
      enum class EffectState {
        Active,  //!< 活動状態
        Paused,  //!< 停止状態
        Dead     //!< 死亡状態
      };
      /**
       * @brief  プレイヤー状態の確認
       */
      virtual void CheckPlayerState();
      /**
       * @brief  エフェクト読み込みハンドルの取得
       * @param  key エフェクトキー
       * @return 指定したエフェクトの読み込みハンドル
       *         キーが有効でない場合-1を返す
       */
      virtual int GetEffectHandle(const std::string_view key) {
        return _app.GetEffectLoadServer().GetEffectHandle(key);
      }

      int _effectHandle{ -1 };  //!< エフェクト読み込みハンドル
      int _playHandle{ -1 };    //!< エフェクト再生ハンドル
      AppMath::Vector4 _ePos;   //!< エフェクト位置
      float _eRadY{ 0.0f };     //!< エフェクトy向き(ラジアン)
      int _playLag{ 0 };        //!< 生成から再生までのラグ
      int _lagCount{ 0 };       //!< ラグカウント
      bool _isPlay{ false };    //!< 再生判定
      bool _isCheck{ false };   //!< プレイヤー状態確認の有無

      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
      //! エフェクトの状態保持変数
      EffectState _effectState{ EffectState::Paused };
      //!< プレイヤー状態を比較する変数
      Player::Player::PlayerState _checkState{ Player::Player::PlayerState::Idle };
    };
  } // namespace Effect
} // namespace Gyro
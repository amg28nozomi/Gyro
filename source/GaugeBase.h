/*****************************************************************//**
 * @file   GaugeBase.cpp
 * @brief  ゲームゲージの基底クラス
 *
 * @author 土橋峡介
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief ゲージベース
   */
  namespace Gauge {
    /**
     * @class GaugeBase
     * @brief ゲージベース
     */
    class GaugeBase {
    public:
      /**
       * @brief ゲージ識別番号の列挙型クラス
       */
      enum class GaugeId {
        Gauge,  //!< ゲージ
        Player, //!< プレイヤー
        Enemy   //!< エネミー
      };
      /**
       * @brief ゲージの状態を表す列挙型クラス
       */
      enum class GaugeState {
        Active, //!< 活動状態
        Paused, //!< 停止状態
        Dead    //!< 死亡状態
      };
      /**
       * @brief コンストラクタ
       */
      GaugeBase(Application::ApplicationMain& app);
      /**
       * @brief コンストラクタ
       * @param gauge ゲージポイント
       */
      GaugeBase(int gauge);
      /**
       * @brief コンストラクタ
       * @param gauge ゲージポイント
       */
      GaugeBase(float gauge);
      /**
       * @brief デストラクタ
       */
      ~GaugeBase() = default;
      /**
       * @brief  初期化処理
       * @return true
       */
      virtual bool Init();
      /**
       * @brief  更新処理
       * @return true
       */
      virtual bool Process();
      /**
       * @brief  描画処理
       * @return true
       */
      virtual bool Draw() const;
      /**
       * @brief  識別番号の取得
       * @return 識別番号
       */
      GaugeId GetId() const {
          return _id;
      }
      /**
       * @brief  状態の取得
       * @return 状態
       */
      GaugeState GetState() const {
          return _state;
      }
      /**
       * @brief  死亡状態かの判定
       * @return true:死亡状態 false:死んでいない
       */
      virtual bool IsDead() const {
          return _state == GaugeState::Dead;
      }
      /**
       * @brief ゲージの増加
       * @param value 値
       */
      void Add(float value);
      /**
       * @brief  対象ゲージとの比較
       * @param  gauge 比較対象
       * @return true:対象以上 false:対象未満
       */
      inline bool IsBig(const GaugeBase gauge) const {
          return gauge._point <= _point;
      }
      /**
       * @brief  ゲージポイントの取得(整数値)
       * @return 整数値にキャストしたゲージポイント
       */
      inline int GetInteger() const {
          return static_cast<int>(_point);
      }
      /**
       * @brief  ゲージポイントの取得(単精度浮動小数点数)
       * @return 生のゲージポイント
       */
      inline float GetFloat() const {
          return _point;
      }
    protected:
      Application::ApplicationMain& _app; //!< アプリケーションの参照
      float _point{ 0 };       //!< ゲージポイント
      float _hitPoint{ 0 };    //!< ゲージポイント(HP用)
      float _maxW{ 0 };        //!< ゲージの横幅(描画する際の横幅)
      float _maxGauge{ 0 };    //!< ゲージの横幅(変動)
      float _value{ 0 };       //!< 値
      GaugeId _id{ GaugeId::Gauge }; //!< ゲージの識別番号
      GaugeState _state{ GaugeState::Active }; //!< 状態
    };
  }// namespace Gauge
}// namespace Gyro


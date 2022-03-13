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
       * @brief コンストラクタ
       */
      GaugeBase(Application::ApplicationMain& app);
      /**
       * @brief デストラクタ
       */
      ~GaugeBase() = default;
      /**
       * @brief  初期化処理
       * @param  value ゲージの最大値
       * @return true
       */
      virtual bool Init(float value);
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
       * @brief ゲージの増加
       * @param value 値
       */
      void Add(float value);
      /**
       * @brief ゲージの減少
       * @param value 値
       */
      void Sub(float value);
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
      inline int GetIntPoint() const {
          return static_cast<int>(_point);
      }
      /**
       * @brief  ゲージポイントの取得(単精度浮動小数点数)
       * @return 生のゲージポイント
       */
      inline float GetFloatPoint() const {
          return _point;
      }
      /**
       * @brief  ゲージの値の取得
       * @return ゲージの値
       */
      float Getvalue() const {
        return _value;
      }
      /**
       * @brief  上限値の取得
       * @return 上限値
       */
      inline float GetMaxGauge() const {
        return _maxGauge;
      }
    protected:
      Application::ApplicationMain& _app; //!< アプリケーションの参照
      float _point{ 0 };       //!< ゲージポイント
      float _hitPoint{ 0 };    //!< ゲージポイント(HP用)
      float _maxW{ 0 };        //!< ゲージの横幅(描画する際の横幅)
      float _maxGauge{ 0 };    //!< ゲージの横幅(変動)
      float _value{ 0 };       //!< 値
    };
  }// namespace Gauge
}// namespace Gyro


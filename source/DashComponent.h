/*****************************************************************//**
 * @file   DashComponent.h
 * @brief  ダッシュコンポーネントクラス
 * 
 * @author 鈴木希海
 * @date   March 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"
#include <appframe.h>

namespace Gyro {
  namespace Object {
    namespace AppMath = AppFrame::Math;
    class ObjectBase;
    /**
     * @class DashComponent
     * @brief ダッシュコンポーネントクラス
     */
    class DashComponent : public ObjectComponent {
    public:
      /**
       * @brief ダッシュ状態を表す列挙型クラス
       */
      enum class DashState {
        Active,   //!< 活動状態
        NoActive, //!< 非活動
        Interval  //!< 待機状態
      };
      /**
       * @brief コンストラクタ
       */
      DashComponent();
      /**
       * @brief 初期化
       */
      void Init() override;
      /**
       * @brief 開始処理
       */
      void Start() override;
      /**
       * @brief 終了処理
       */
      void Finish() override;
      /**
       * @brief  更新処理
       * @param  move 移動量を格納するためのベクトル4クラスの参照
       * @return true
       */
      bool Process(AppMath::Vector4& move);
      /**
       * @brief ダッシュの設定
       * @param move 総移動量
       * @param time 総移動時間
       */
      void SetMove(const AppMath::Vector4& move, float time);
      /**
       * @brief インターバルの設定
       */
      void SetIniterval(const float interval);
      /**
       * @brief インターバル処理
       */
      void Interval();
      /**
       * @brief  ダッシュ状態の取得
       * @return ダッシュ状態
       */
      DashState GetDashState() const {
        return _dashState;
      }
      /**
       * @brief  インターバルがあるかの判定
       * @return true:インターバル中 false:インターバルではない
       */
      bool IsInterval() const {
        return _dashState == DashState::Interval;
      }
    private:
      //!< ダッシュ状態
      DashState _dashState{DashState::NoActive};
      //!< 総移動量
      AppMath::Vector4 _length{};
      //!< 移動量
      AppMath::Vector4 _move{};
      //!< インターバル時間
      float _time{0.0f};
    };
  } // namespace Object
} // namespace Gyro
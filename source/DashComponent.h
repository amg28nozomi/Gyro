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

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    namespace AppMath = AppFrame::Math;
    class ObjectBase; //!< 前方宣言
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
       * @param owner 所有者の参照
       */
      DashComponent(ObjectBase& onwer);
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
       * @param dashPower 総移動量
       * @param totalTime ダッシュ時間
       * @param playSpeed 再生速度
       */
      void SetDash(const float dashPower, float totalTime, float playSpeed);
      /**
       * @brief インターバルの設定
       */
      void SetIniterval(const float interval);
      /**
       * @brief インターバル処理
       */
      void Interval();
      /**
       * @brief  移動量の取得
       * @return 移動量
       */
      AppMath::Vector4 GetMovePower() const {
        return _move;
      }
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
      //!< 所有者の参照
      ObjectBase& _owner;
      //!< ダッシュ状態
      DashState _dashState{DashState::NoActive};
      //!< 移動力
      float _power{0.0f};
      //!< インターバル時間
      float _intervalTime{0.0f};
      //!< 処理回数
      int _count{0};
      //!< 移動量
      AppMath::Vector4 _move{};
    };
  } // namespace Object
} // namespace Gyro
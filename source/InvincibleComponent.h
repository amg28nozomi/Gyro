/*****************************************************************//**
 * @file   InvincibleComponent.h
 * @brief  無敵処理用のコンポーネントクラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"

/**
 * @brief ゲームベース
 */
namespace Gyro {

  namespace Application {
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    /**
     * @class InvincibleComponent
     * @brief 無敵処理用コンポーネント
     */
    class InvincibleComponent : public ObjectComponent {
    public:
      /**
       * @brief  無敵状態を表す列挙型クラス
       */
      enum class InvincibleState {
        Normal,    //!< 通常状態
        Invincible //!< 無敵状態
      };
      /**
       * @brief  コンストラクタ
       * @param  app アプリケーションメインの参照
       */
      InvincibleComponent(Application::ApplicationMain& app);
      /**
       * @brief  初期化
       */
      void Init() override;
      /**
       * @brief  無敵時間の設定
       * @param  limit 総無敵時間
       */
      inline void Set(const float limit) {
        _limit = limit;
      }
      /**
       * @brief  無敵処理の開始
       */
      void Start() override;
      /**
       * @brief  無敵処理の終了
       */
      void Finish() override;
      /**
       * @brief  更新処理
       * @param  speed 経過時間(デフォルトは1.0f)
       */
      void Process(const float speed = 1.0f);
    protected:
      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
      //!< 無敵状態
      InvincibleState _invincible{InvincibleState::Normal};
      //!< 総無敵時間
      float _limit;
      //!< 無敵時間
      float _time;
      /**
       * @brief  無敵時間を超過したかの判定
       * @param  speed 時間
       * @return true:終了 false:継続
       */
      bool TimeEnd(const float speed);
    };
  } // namespace Object
} // namespace Gyro
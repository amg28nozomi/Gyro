/*****************************************************************//**
 * @file   KnockBackComponent.h
 * @brief  ノックバック機能クラス
 * 
 * @author 土橋峡介
 * @date   March 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"
#include "appframe.h"

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief アプリケーションベース
   */
  namespace Application {
    class ApplicationMain; //!< 前方宣言
  } // namespace Application
  namespace AppMath = AppFrame::Math;
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class EnemyBase;  //!< エネミーベース
    class ObjectBase; //!< オブジェクトベース
    /**
     * @class KnockBackComponent
     * @brief ノックバック用コンポーネント
     */
    class KnockBackComponent : public ObjectComponent {
    public:
      /**
       * @brief ノックバック状態を表す列挙型クラス
       */
      enum class KnockBackState {
        NonActive,  // ノーアクション
        Active,     // 活動状態
      };
      /**
       * @brief コンストラクタ
       */
      KnockBackComponent(ObjectBase& owner, Application::ApplicationMain& app);
      /**
       * @brief ノックバック処理の開始
       */
      void Start() override;
      /**
       * @brief ノックバックの終了
       */
      void Finish() override;
      /**
       * @brief  ノックバックの更新
       * @return true:正常終了 false:ノックバック状態ではない
       */
      bool Process();
      /**
       * @brief  ノックバック状態かの判定
       * @return true:ノックバック中 false:ノックバック状態ではない
       */
      bool IsKnockBack() const {
        return _state == KnockBackState::Active;
      }
      /**
       * @brief  ノックバック状態の取得
       * @return ノックバック状態
       */
      const KnockBackState& GetState() {
        return _state;
      }
      /**
       * @brief  移動量(ベクトル)の取得
       * @return 移動量ベクトル
       */
      AppMath::Vector4 MoveVector() const {
        return _move;
      }
    protected:
      ObjectBase& _owner;                 //!< 所有者の参照
      //std::shared_ptr<EnemyBase> _enemy;  //!< エネミー
      Application::ApplicationMain& _app; //!< アプリケーションの参照
      KnockBackState _state;              //!< ノックバック状態
      AppMath::Vector4 _move{};           //!< ノックバックの移動量
      int _cnt{ 0 };                      //!< カウント
    };
  } // namespace Player
} // namespace Gyro
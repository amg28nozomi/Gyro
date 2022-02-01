/*****************************************************************//**
 * @file   ObjectBase.h
 * @brief  オブジェクトのスーパークラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
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
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    namespace AppMath = AppFrame::Math;
    /**
     * @class ObjectBase
     * @brief オブジェクトのスーパークラス
     */
    class ObjectBase {
    public:
      /**
       * @brief オブジェクト識別番号の列挙型クラス
       */
      enum class ObjectId {
        Object, //!< オブジェクト
        Player, //!< プレイヤー
        Enemy   //!< 敵
      };
      /**
       * @brief オブジェクトの状態を表す列挙型クラス
       */
      enum class ObjectState {
        Active, //!< 活動状態
        Paused, //!< 停止状態
        Dead    //!< 死亡状態
      };
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      ObjectBase(Application::ApplicationMain& app);
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
      ObjectId GetId() const {
        return _id;
      }
      /**
       * @brief  状態の取得
       * @return 状態
       */
      ObjectState GetState() const {
        return _state;
      }
      /**
       * @brief  死亡状態かの判定
       * @return true:死亡状態 false:死んでいない
       */
      virtual bool IsDead() const {
        return _state == ObjectState::Dead;
      }
      /**
       * @brief  ローカル座標の取得
       * @return ローカル座標
       */
      AppMath::Vector4 GetPosition() const {
        return _position;
      }
      /**
       * @brief  
       * @return 
       */
      AppMath::Vector4 GetRotation() const {
        return _rotation;
      }
      /**
       * @brief  拡大率の取得
       * @return 
       */
      AppMath::Vector4 GetScale() const {
        return _scale;
      }
    protected:
      Application::ApplicationMain& _app; //!< アプリケーションの参照
      ObjectId _id{ObjectId::Object}; //!< オブジェクトの識別番号
      ObjectState _state{ObjectState::Active}; //!< 状態
      AppFrame::Math::Matrix44 _world;         //!< ワールド座標
      AppFrame::Math::Vector4 _position;       //!< ローカル座標
      AppFrame::Math::Vector4 _rotation;       //!< 回転(Debug:デグリー Release:ラジアン)
      AppFrame::Math::Vector4 _scale{0, 0, 0}; //!< 拡大率
      bool _stand{false};   //!< 立ちフラグ(true:床に立っている false:床と接触していない)
      bool _gravity{false}; //!< 重力処理を行うか(true:重力処理を行う false:重力処理を行わない)
      float _mass{0.0f};    //!< 質量
      float _gravityScale{0.0f}; //!< 重力スケール
      /**
       * @brief オブジェクトに対する重力処理
       */
      virtual void Gravity();
      /**
       * @brief  重力スケールの更新
       */
      virtual void GravityScale();
      /**
       * @brief  床との衝突判定
       *         派生クラスで重力処理を行う場合は必ず再定義を行うこと
       * @return true:衝突している false:衝突していない
       */
      virtual bool IsStand();
      /**
       * @brief  重力処理のリセット
       */
      virtual void GravityReset();
      /**
       * @brief  ワールド座標の更新
       */
      void WorldMatrix();
#ifdef _DEBUG
      /**
       * @brief デバッグ専用の出力処理
       *        アプリケーションのデバッグフラグがtrueの場合のみ処理を行う
       */
      virtual bool DebugDraw() const;
#endif
    };
  } // namespace Object
} // namespace Gyro
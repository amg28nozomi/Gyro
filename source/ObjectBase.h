/*****************************************************************//**
 * @file   ObjectBase.h
 * @brief  オブジェクトのスーパークラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <appframe.h>
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
    class SpawnBase; //!< スポーン情報
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
        Object,    //!< オブジェクト
        Player,    //!< プレイヤー
        Enemy,     //!< 敵
        SkySphere, //!< スカイスフィア
        Item,      //!< アイテム
        Field      // Field
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
       * @brief  スポーン情報の読み取り
       * @param  spawn スポーン情報
       */
      virtual void Set(SpawnBase& spawn);
      /**
       * @brief  重力処理を行うかのフラグをセット
       * @param  flag true:重力処理を行う false:重力処理を無効
       */
      virtual inline void GravitySet(const bool flag) {
        _gravity = flag;
      }
      /**
       * @brief 向きベクトルの設定
       * @param forward 向きベクトル
       */
      inline void SetForward(AppMath::Vector4 forward) {
        _forward = forward;
      }
      /**
       * @brief  指定したフレームのワールド座標を取得
       * @param  frame フレーム番号
       * @return 空のベクトルを返す
       */
      virtual AppMath::Vector4 GetFramePosition(int frame) {
        return AppMath::Vector4();
      }
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
       * @brief  ワールド座標行列の取得
       * @return ワールド座標行列
       */
      AppMath::Matrix44 GetMatrix() const {
        return _world;
      }
      /**
       * @brief  ローカル座標の取得
       * @return ローカル座標
       */
      AppMath::Vector4 GetPosition() const {
        return _position;
      }
      /**
       * @brief  向きの取得
       * @return 向き
       */
      AppMath::Vector4 GetRotation() const {
        return _rotation;
      }
      /**
       * @brief  拡大率の取得
       * @return スケール
       */
      AppMath::Vector4 GetScale() const {
        return _scale;
      }
      /**
       * @brief  向きベクトルの取得
       * @return 向きベクトル
       */
      AppMath::Vector4 GetForward() const {
        return _forward;
      }
      /**
       * @brief  アプリケーションの取得
       * @return アプリケーションの参照
       */
      Application::ApplicationMain& GetApplicaton() const {
        return _app;
      }
      /**
       * @brief  モデルに紐づけられた文字列の取得
       * @return 文字列
       */
      virtual std::string_view ModelKey() const {
        return "";
      }
      /**
       * @brief 向きの設定
       * @param rotation 設定する向き
       */
      inline void SetRotation(const AppMath::Vector4& rotation) {
        _rotation = rotation;
      }
      /**
       * @brief  向きベクトルの取得
       * @return 向きベクトル
       */
      inline AppMath::Vector4 Forward() const {
        return _forward;
      }
      /**
       * @brief  ソート用の値を取得
       * @return ソート用の値
       */
      int GetSort() {
        return _sort;
      }
    protected:
      //!< アプリケーションの参照
      Application::ApplicationMain& _app;
      //!< オブジェクトの識別番号
      ObjectId _id{ObjectId::Object};
      //!< 状態
      ObjectState _state{ObjectState::Active};
      //!< ワールド座標
      AppMath::Matrix44 _world;
      //!< ローカル座標
      AppMath::Vector4 _position;
      //!< 回転(Debug:デグリー Release:ラジアン)
      AppMath::Vector4 _rotation;
      //!< 拡大率
      AppMath::Vector4 _scale{0, 0, 0};
      //!< 向きベクトル
      AppMath::Vector4 _forward{0, 0, 0};
      int _sort{ 0 };       //!< ソート用
      bool _stand{false};   //!< 立ちフラグ(true:床に立っている false:床と接触していない)
      bool _gravity{false}; //!< 重力処理を行うか(true:重力処理を行う false:重力処理を行わない)
      bool _isStand{false}; //!< 立ちフラグ
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
       * @brief  押し出し処理
       */
      virtual void Extrude(){}
      /**
       * @brief  ワールド座標の更新
       * @param  angle 角度フラグ(true:デグリー false:ラジアン)
       */
      void WorldMatrix(bool angle = AppMath::Degree);
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
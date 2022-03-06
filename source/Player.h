/*****************************************************************//**
 * @file   Player.h
 * @brief  オブジェクトベースのサブクラス
 *         自機の処理を行う
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "ObjectBase.h"
#include "Camera.h"
#include "ModelAnimComponent.h"
#include "CollisionSphere.h"
#include "CollisionCapsule.h"
#include "GaugeHP.h"
#include "GaugeTrick.h"
#include "JumpComponent.h"
#include "KnockBackComponent.h"
#include "MoveComponent.h"
#include "WireComponent.h"
#include "AttackComponent.h"
#include "InvincibleComponent.h"
#include "StateComponent.h"

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief エネミークラス
   */
  namespace Enemy {
    class EnemyBase;
  }
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class CollisionCapsule; //!< 前方宣言
  } // namespace Object
  /**
   * @brief プレイヤーベース
   */
  namespace Player {
    /**
     * @brief 名前空間の省略
     */
    namespace AppMath = AppFrame::Math;
    constexpr auto DefaultRadius = 30.0f; //!< デフォルトの半径
    class JumpComponent; //!< ジャンプコンポーネント
    /**
     * @class Player
     * @brief オブジェクトベースのサブクラス
     */
    class Player : public Object::ObjectBase {
    public:
      /**
       * @brief 自機の状態を表す列挙型クラス
       */
      enum class PlayerState {
        Idle,        //!< 待機
        Walk,        //!< 歩き
        Run,         //!< 移動
        Attack1,     //!< 攻撃1
        Attack2,     //!< 攻撃2
        Attack3,     //!< 攻撃3
        ExciteTrick, //!< エキサイトトリック
        Jump         //!< ジャンプ
      };
      /**
       * @brief コンストラクタ
       * @param app アプリケーションの参照
       */
      Player(Application::ApplicationMain& app);
      /**
       * @brief  初期化処理
       * @return true
       */
      bool Init() override;
      /**
       * @brief  更新処理
       * @return true
       */
      bool Process() override;
      /**
       * @brief  描画処理
       * @return true
       */
      bool Draw() const override;
      /**
       * @brief  スポーン情報の読み取り
       * @param  spawn スポーン情報
       */
      void Set(Object::SpawnBase& spawn) override;
      /**
       * @brief  ステージハンドルの取得
       * @return ステージハンドル
       */
      int StageHandle() const {
        return _handleMap;
      }
      /**
       * @brief  ゲームオーバーの取得
       * @return ゲームオーバー
       */
      bool GetGameOver() const {
        return _gameOver;
      }
      /**
       * @brief  指定したフレームのワールド座標を取得
       * @param  frame フレーム番号
       * @return 取得に成功した場合はワールド座標を返す
       *         失敗した場合は空のベクトルを返す
       */
      AppMath::Vector4 GetFramePosition(int frame) override;
      /**
       * @brief  アタックコンポーネントの取得
       * @return アタックコンポーネントの参照
       */
      Object::AttackComponent& AttackComponent() const {
        return *_attack;
      }
      /**
       * @brief  モデルキーの取得
       * @return モデルキー
       */
      std::string_view ModelKey() const override {
        return _modelKey;
      }
    private:
      //!< モデルハンドル
      int _model;
      //!< 歩き・ダッシュモーションの再生速度
      float _animSpeed;
      int _playerHP{ 0 };  //!< 自機体力
      //!< AnimComponent
      ModelAnim::ModelAnimComponent _modelAnim;
      //!< HPゲージ
      Gauge::GaugeHP _gaugeHp;
      //!< トリックゲージ
      Gauge::GaugeTrick _gaugeTrick;
      //!< 当たり判定コリジョン(球)
      std::unique_ptr<Object::CollisionSphere> _sphere;
      //!< 当たり判定コリジョン(カプセル)
      std::unique_ptr<Object::CollisionCapsule> _capsule;
      //!< 自機状態
      PlayerState _playerState{PlayerState::Idle};
      //!< 前フレーム状態
      PlayerState _oldState{ PlayerState::Idle };
      //!< 前方ベクトル
      AppMath::Vector4 _forward{};
      //!< 攻撃フラグ(true:強攻撃 false:弱攻撃)
      bool _attackFlag{false};
      //!< 平面
      std::unique_ptr<AppMath::Plane> _plane;
      int _handleMap;
      int _frameMapCollision;
      /**
       * @brief 入力処理
       */
      void Input();
      /**
       * @brief リソースの読み取り処理
       */
      void LoadResource();
      /**
       * @brief 状態の設定
       */
      void SetState();
      /**
       * @brief カメラの設定
       */
      void SetCamera();
      /**
       * @brief  移動量の算出
       * @param  leftX 左スティックの入力情報(x軸)
       * @param  leftY 左スティックの入力情報(y軸)
       */
      AppMath::Vector4 Move(const float leftX, const float leftY);
      /**
       * @brief カメラの更新
       * @param stick 
       */
      void CameraUpdate(const AppFrame::Math::Vector4 stick);
      /**
       * @brief 向きの設定
       * @param move 移動量
       */
      void SetRotation(const AppFrame::Math::Vector4 move);
      /**
       * @brief  
       * @param  state 
       * @return 
       */
      bool State(const PlayerState& state) const {
        return _playerState == state;
      }
      /**
       * @brief アニメーション処理
       * @param old 前フレームの状態
       */
      void Animation(PlayerState old);
      /**
       * @brief  状態の切り替え処理(βプレゼン専用)
       * @param  move XBOXコントローラの入力状態クラスの参照
       * @return true:チェンジ false:変更なし
       */
      bool StateChanege(const AppFrame::Application::XBoxState& input);
#ifdef _DEBUG
      /**
       * @brief  デバッグ専用の描画処理
       * @return true: false:
       */
      bool DebugDraw() const override;
      /**
       * @brief Debug専用描画
       */
      void DebugString() const;
#endif
      /**
       * @brief 重力処理
       */
      void GravityScale() override;
      /**
       * @brief  地形との衝突判定
       * @return true:衝突 false:衝突していない
       */
      bool IsStand() override;
      /**
       * @brief  押し出し処理
       */
      void Extrude() override;
      /**
       * @brief 衝突判定処理
       */
      void Hit();
      /**
       * @brief ジャンプ処理
       */
      void Jump();
      /**
       * @brief ワイヤーアクション
       */
      void Wire(AppMath::Vector4& move);
      /**
       * @brief  状態遷移
       * @param  state 遷移先の状態
       * @param  animName アニメーション名
       */
      void ChangeState(const PlayerState& state, std::string_view animName);
      /**
       * @brief  攻撃処理
       */
      void Attack();
      /**
       * @brief  攻撃状態かの判定
       * @return true:攻撃状態 false:攻撃状態ではない
       */
      bool IsAttackState() const;
      /**
       * @brief ダメージ処理
       */
      void IsDamage();
      /**
       * @brief  キーの設定
       * @return 現在の状態に対応するジョイパッドキーを返す
       *         最終コンボの場合は-1を返す
       *         それ以外の場合は-2を返す
       */
      int NextKey() const;
      /**
       * @brief  状態の変更
       * @return true: false:
       */
      bool SetStateParam(PlayerState pState);
      /**
       * @brief  走り状態に遷移するかの判定
       * @param  move 移動量
       * @return true:遷移する false:遷移しない
       */
      bool IsRun(const AppMath::Vector4& move);
      /**
       * @brief  プレイヤー状態を数値に変換する
       * @return プレイヤー状態に対応した
       */
      int PlayerStateToNumber() const;
      /**
       * @brief  コリジョンを生成する
       * @param  num    生成する数
       * @param  radius 半径
       * @return コリジョン情報が格納された動的配列
       */
      std::vector<std::shared_ptr<Object::CollisionBase>> AddSpheres(const int num, float daius = DefaultRadius);
    private:
      //!< モデルサーバに紐づけられた文字列
      static inline std::string _modelKey{"player"};
      //!< ジャンプコンポーネント
      std::unique_ptr<JumpComponent> _jump;
      //!< ノックバックコンポーネント
      std::unique_ptr<Object::KnockBackComponent> _knockBack;
      //!< ムーブコンポーネント
      std::unique_ptr<Object::MoveComponent> _move;
      //!< ワイヤーコンポーネント
      std::unique_ptr<WireComponent> _wire;
      //!< アタックコンポーネント
      std::unique_ptr<Object::AttackComponent> _attack;
      //!< インビジブルコンポーネント
      std::unique_ptr<Object::InvincibleComponent> _invincible;
      //!< ステートコンポーネント
      std::unique_ptr<Object::StateComponent> _stateComponent;
      //!< アニメーション名を保持する文字列
      std::string _animationKey;
      //!< 重力リセット処理
      bool _gravityReset{false};
      //!< ゲームオーバー
      bool _gameOver{ false };
    };
  } // namespace Player
} // namespace Gyro
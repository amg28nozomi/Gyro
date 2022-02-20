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
#include "MoveComponent.h"
#include "WireComponent.h"
#include "AttackComponent.h"
#include "InvincibleComponent.h"
#include "StateComponent.h"

namespace AppFrame::Math{}
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief オブジェクトベース
   */
  namespace Object {
    class CollisionCapsule;
  } // namespace Object
  /**
   * @brief プレイヤーベース
   */
  namespace Player {
    namespace AppMath = AppFrame::Math;
    class JumpComponent; //!< 
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
        Idle,       //!< 待機
        Walk,       //!< 歩き
        Run,        //!< 移動
        Attack1,    //!< 攻撃1
        Attack2,    //!< 攻撃2
        Attack3,    //!< 攻撃3
        Jump        //!< ジャンプ
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

      // 仮
      int StageHandle() const {
        return _handleMap;
      }
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
      // AppFrame::Math::Vector4 _move{}; //!< 移動量

      int _model;       //!< モデルハンドル
      int _animaIndex;  //!< アタッチされているアニメ番号
      float _totalTime; //!< アニメーションの総再生時間
      float _animaTime; //!< アニメーションの再生時間
      ModelAnim::ModelAnimComponent _modelAnim; //!< AnimComponentの実態
      Gauge::GaugeHP _gaugeHp;       //!< HPゲージの実態
      Gauge::GaugeTrick _gaugeTrick; //!< トリックゲージの実態
      std::unique_ptr<Object::CollisionSphere> _sphere;   //!< 当たり判定コリジョン(球)
      std::unique_ptr<Object::CollisionCapsule> _capsule; //!< カプセル
      PlayerState _playerState{PlayerState::Idle};        //!< 自機状態
      PlayerState _oldState{ PlayerState::Idle };

      bool _attackFlag{false};   //!< 攻撃フラグ(true:強攻撃 false:弱攻撃)

      std::unique_ptr<AppMath::Plane> _plane; //!< 平面
      int _handleMap;
      int _frameMapCollision;
      int _handleSkySphere;   //!< スカイスフィアハンドル
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
      /**
       * @brief モーション切り替え
       */
      void Anime();
      /**
       * @brief 指定したアニメーションインデックスの取得
       * @param key アニメーションに紐づけられた文字列
       */
      int AnimaIndex(std::string_view key) const;
      /**
       * @brief アニメーションのアタッチ
       */
      bool AttachAnima(std::string_view key);
      /**
       * @brief 現在の状態に応じたアニメキーを返す
       */
      std::string_view GetAnimaKey() const;
#ifdef _DEBUG
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
      //!< モデルサーバに紐づけられた文字列
      static inline std::string _modelKey{"player"};
      //!< ジャンプコンポーネント
      std::unique_ptr<JumpComponent> _jump;
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
    };
  } // namespace Player
} // namespace Gyro
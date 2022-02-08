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
#include "ModelAnim/ModelAnimComponent.h"
#include "CollisionSphere.h"
#include "CollisionCapsule.h"
#include "GaugeHP.h"
#include "GaugeTrick.h"

namespace AppFrame::Math{}
/**
 * @brief ゲームベース
 */
namespace Gyro {
  namespace Object {
    class CollisionCapsule;
  }
  /**
   * @brief プレイヤーベース
   */
  namespace Player {
    namespace AppMath = AppFrame::Math;
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
    private:
      AppFrame::Math::Vector4 _move{}; //!< 移動量

      int _model;          //!< モデルハンドル
      int _animaIndex;     //!< アタッチされているアニメ番号
      float _totalTime;    //!< アニメーションの総再生時間
      float _animaTime;    //!< アニメーションの再生時間
      ModelAnim::ModelAnimComponent _modelAnim; //!< AnimComponentの実態
      Gauge::GaugeHP _gaugeHp;       //!< HPゲージの実態
      Gauge::GaugeTrick _gaugeTrick; //!< トリックゲージの実態
      std::unique_ptr<Object::CollisionSphere> _sphere;   //!< 当たり判定コリジョン(球)
      std::unique_ptr<Object::CollisionCapsule> _capsule; //!< カプセル
      PlayerState _playerState{PlayerState::Idle};        //!< 自機状態

      bool _attackFlugY = false; //!< 弱攻撃フラグ
      bool _attackFlugX = false; //!< 強攻撃フラグ
      int _cnt;

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
       */
      AppMath::Vector4 Move(AppMath::Vector4 move);
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
       * @brief アニメーション処理
       * @param old 前フレームの状態
       */
      void Animation(PlayerState old);
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
       * @brief  地形との衝突判定
       * @return true:衝突 false:衝突していない
       */
      bool IsStand() override;

      /**
       * @brief 衝突判定処理
       */
      void Hit();
      /**
       * @brief ジャンプ処理
       */
      void Jump();

      float _jumpPower{0.0f};    //!< ジャンプ力
      float _jumpInterval{0.0f}; //!< ジャンプインターバル
      bool _jump;                //!< ジャンプフラグ
    };
  }
    //} // namespace Player
} // namespace Gyro
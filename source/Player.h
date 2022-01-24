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
//#include "camera.h"

namespace AppFrame::Math{}

/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief カメラベース
   */
  namespace Camera {
    /**
     * @class Camera
     * @brief カメラクラス
     */
    class Camera {
    public:
      VECTOR _pos;
      VECTOR _target;
      float _clipNear, _clipFar;
    };
  } // namespace Camera
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
        Idle,   //!< 待機
        Walk,   //!< 歩き
        Run,    //!< 移動
        Attack, //!< 攻撃
        Jump    //!< ジャンプ
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
    private:
      AppFrame::Math::Vector4 _move{}; //!< 移動量

      int _model;          //!< モデルハンドル
      int _animaIndex;     //!< アタッチされているアニメ番号
      float _totalTime;    //!< アニメーションの総再生時間
      float _animaTime;    //!< アニメーションの再生時間
      Camera::Camera _cam; //!< カメラの実体

      PlayerState _playerState{PlayerState::Idle}; //!< 自機状態
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
       * @param  stick 入力値
       * @return 移動量
       */
      float Speed(const AppFrame::Math::Vector4 stick) const;
      /**
       * @brief  移動量の算出
       */
      void Move(AppMath::Vector4 move);
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
      /**
       * @briefs
       *
       */
      bool WorldMatrixUpdate() override;
#ifdef _DEBUG
      /**
       * @brief Debug専用描画
       */
      void DebugString() const;
#endif
    };
  }
    /**
     * @brief プレイヤー
     */
    //namespace Player {
    //    /**
    //     * @class Player
    //     * @brief オブジェクトベースのサブクラス
    //     */
    //    class Player : public Object::ObjectBase {
    //    public:
    //      /**
    //       * @brief コンストラクタ
    //       * @param app アプリケーションの参照
    //       */
    //      Player(Application::ApplicationMain& app);
    //      /**
    //       * @brief  初期化処理
    //       * @return true
    //       */
    //      bool Init() override;
    //      /**
    //       * @brief  更新処理
    //       * @return true
    //       */
    //      bool Process() override;
    //      /**
    //       * @brief  描画処理
    //       * @return true
    //       */
    //      bool Draw() const override;


    //        /**
    //         * @enum class
    //         */
    //        enum class STATE {
    //            IDLE,
    //            WALK,
    //            RUN,
    //            ATTACK,
    //            JUMP,
    //        };
    //        /**
    //         * @brief コンストラクタ
    //         */
    //        Player(Application::ApplicationMain& app);
    //        //Player();
    //        /**
    //         * @brief  初期化処理
    //         * @return true
    //         */
    //        bool Init() override;
    //        /**
    //         * @brief  更新処理
    //         * @return true
    //         */
    //        bool Process() override;
    //        /**
    //         * @brief  描画処理
    //         * @return true
    //         */
    //        bool Draw() const override;
    //    protected:
    //        int _handleMap;
    //        int _frameMapCollision;
    //        int _handleModel;       //!< モデルハンドル
    //        int _handleSkySphere;   //!< スカイスフィアハンドル
    //        int _attachIndex;       //!< アニメーションのアタッチ
    //        float _totalTime;       //!< 総再生時間
    //        float _playTime;        //!< 
    //        VECTOR _position;       //!< 座標
    //        VECTOR _dir;            //!< 向き

    //        STATE _state;           //!< 状態

    //        Camera::Camera _cam;
    //        /**
    //         * @brief リソースの読み取り処理
    //         */
    //        void LoadResource();
    //        /**
    //         * @brief カメラの設定
    //         */
    //        void SetCamera();
    //    };
    //} // namespace Player
} // namespace Gyro
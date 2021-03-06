/*****************************************************************//**
 * @file    EnemyWheel.h
 * @brief   地上敵クラス
 *
 * @author  土橋峡介
 * @date    January 2022
 *********************************************************************/
#pragma once
#include "EnemyBase.h"

 /**
  * @brief ゲームベース
  */
namespace Gyro {
  /**
   * @brief 敵ベース
   */
  namespace Enemy {
    /**
     * @class EnemyWheel
     * @brief 地上敵クラス
     */
    class EnemyWheel : public EnemyBase {
    public:
      /**
       * @brief  コンストラクタ
       */
      EnemyWheel(Application::ApplicationMain& app);
      /**
       * @brief  デストラクタ
       */
      ~EnemyWheel();
      /**
       * @brief  初期化
       */
      bool Init() override;
      /**
       * @brief  更新
       */
      bool Process() override;
      /**
       * @brief  描画
       */
      bool Draw() const override;
      /**
       * @brief  攻撃状態の座標の取得
       * @return 攻撃状態の座標
       */
      AppFrame::Math::Vector4 GetAttackPosition() {
        return _oldPosition;
      }
      /**
       * @brief  識別IDの取得
       * @return 識別ID
       */
      unsigned short GetThis() const override {
        return _this;
      }
      /**
       * @brief  モデル番号の初期化
       */
      static inline void ModelNumberReset() {
        _number = 1;
      }
    private:
      /**
       * @brief  モデルの読み込み
       */
      void LoadModel() override;
      /**
       * @brief  パラメータの設定
       */
      void SetParameter() override;
      /**
       * @brief  当たり判定の設定処理
       * @author 鈴木希海
       */
      void SetCollision() override;
      /**
       * @brief  移動処理
       */
      void Move() override;
      /**
       * @brief  攻撃準備処理
       */
      void AttackReady();
      /**
       * @brief  攻撃処理
       */
      void Attack() override;
      /**
       * @brief  ノックバック処理
       */
      void NockBack() override;
      /**
       * @brief  探索処理
       */
      void Search() override;
      /**
       * @brief  衝突処理
       */
      void Hit() override;
      /**
       * @brief  アニメーション切り替え
       */
      void ChangeAnim() override;
      /**
       * @brief  エフェクト初期化(生成)
       */
      void EffectInit() override;
      /**
       * @brief  エフェクト更新呼び出し
       */
      void EffectProcess() override;
      /**
       * @brief  エフェクト再生呼び出し
       */
      void EffectPlay() override;
      /**
       * @brief  エフェクト消去呼び出し
       */
      void EffectDead() override;
      /**
       * @brief  回転攻撃エフェクト
       */
      void SlashEffect();
      /**
       * @brief  ダメージを受けたかの判定
       * @return true:衝突
       *         false:ダメージ無し
       */
      bool IsDamege() override;

      bool _iMove{ false };  //!< 移動フラグ
      bool _slash{ false };  //!< 回転攻撃フラグ
      AppFrame::Math::Vector4 _oldPosition;   //!< 攻撃状態に移行したタイミングの座標
      AppFrame::Math::Vector4 _move;          //!< 移動距離
      static inline unsigned short _number{ 1 };  //!< 生成番号
      unsigned short _this{ 0 };  //!< 識別ID

      //!< 眼光エフェクト
      std::shared_ptr<Effect::EffectEnemyEyeLight> _eyeLight{ nullptr };
      //!< 突進攻撃エフェクト
      std::shared_ptr<Effect::EffectEnemyGroundAttack1> _groundAttack1{ nullptr };
      //!< 回転攻撃エフェクト
      std::shared_ptr<Effect::EffectEnemyGroundAttack2> _groundAttack2{ nullptr };
      //!< 被ダメエフェクト
      std::shared_ptr<Effect::EffectEnemyHit> _hit{ nullptr };
      //!< 爆発エフェクト
      std::shared_ptr<Effect::EffectEnemyExprosion> _exprosion{ nullptr };
    };
  } // namespace Enemy
} // namespace Gyro
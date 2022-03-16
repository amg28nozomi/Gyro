/*****************************************************************//**
 * @file   EnemyDroneBoss.h
 * @brief  空中敵ボスクラス
 * 
 * @author 土橋峡介
 * @date   March 2022
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
     * @class EnemyDroneBoss
     * @brief 空中敵ボスクラス
     */
    class EnemyDroneBoss : public EnemyBase {
    public:
      /**
       * @brief コンストラクタ
       * @param app アプリケーション
       */
      EnemyDroneBoss(Application::ApplicationMain& app);
      /**
       * @brief デストラクタ
       */
      ~EnemyDroneBoss();
      /**
       * @brief  初期化
       * @return true
       */
      bool Init() override;
      /**
       * @brief  更新
       * @return true
       */
      bool Process() override;
      /**
       * @brief  描画
       * @return true
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
       * @brief  攻撃処理
       */
      void Attack() override;
      /**
       * @brief  ノックバック処理
       */
      void NockBack() override;
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
       * @brief  オブジェクトの死亡処理
       */
      void Dead() override;
      /**
       * @brief  ダメージを受けたかの判定
       * @return true:衝突
       *         false:ダメージ無し
       */
      bool IsDamege() override;

      bool _iMove{ false };  //!< 移動フラグ
      AppFrame::Math::Vector4 _oldPosition;   //!< 攻撃状態に移行したタイミングの座標
      static inline unsigned short _number{ 1 };  //!< 生成番号
      unsigned short _this{ 0 };  //!< 識別ID

      //!< 眼光エフェクト
      std::shared_ptr<Effect::EffectEnemyBossEyeLight> _eyeLight{ nullptr };
      //!< 空中攻撃エフェクト
      std::shared_ptr<Effect::EffectEnemyBossAirAttack> _airAttack{ nullptr };
      //!< 被ダメエフェクト
      std::shared_ptr<Effect::EffectEnemyBossHit> _hit{ nullptr };
      //!< 爆発エフェクト
      std::shared_ptr<Effect::EffectEnemyBossExprosion> _exprosion{ nullptr };
    };
  } // namespace Enemy
} // namespace Gyro
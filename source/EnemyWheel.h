/*****************************************************************//**
 * @file    EnemyWheel.h
 * @brief   地上敵クラス
 *
 * @author  宮澤耀生
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
      unsigned short GetThis() const override {
        return _this;
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
       * @brief  エフェクト再生
       */
      void PlayEffect() override;
      /**
       * @brief  ダメージを受けたかの判定
       * @return true:衝突
       *         false:ダメージ無し
       */
      bool IsDamege() override;

      bool _iMove{ false };  //!< 移動フラグ
      AppFrame::Math::Vector4 _oldPosition;   //!< 攻撃状態に移行したタイミングの座標
      static inline unsigned short _number{ 0 };  //!< 生成番号
      unsigned short _this{ 0 };  //!< 識別ID
    };
  } // namespace Enemy
} // namespace Gyro
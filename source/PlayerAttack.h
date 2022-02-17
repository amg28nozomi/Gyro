/*****************************************************************//**
 * @file   PlayerAttack.h
 * @brief  自機の攻撃処理クラス
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "AttackComponent.h"
  
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief プレイヤーベース
   */
  namespace Player {
    /**
     * @class  PlaterAttack
     * @brief  自機の攻撃処理クラス
     */
    class PlayerAttack : public Object::AttackComponent {
    public:
      /**
       * @brief 攻撃の種類を表す列挙型クラス
       */
      enum class AttackType {
        None,  //!< なし
        Light, //!< 弱攻撃
        Heavy, //!< 強攻撃
        Trick  //!< トリック
      };
      /**
       * @brief コンストラクタ
       * @param owner 所有者の判定
       */
      PlayerAttack(Object::ObjectBase& owner);
      /**
       * @brief 開始処理
       */
      void Start() override;
      /**
       * @brief 終了勝利
       */
      void Finish() override;
      /**
       * @brief  攻撃状態の取得
       * @return 攻撃状態
       */
      AttackType GetAttackType() const {
        return _attackType;
      }
    private:
      //!< 攻撃の種類
      AttackType _attackType{AttackType::None};
      //!< チェインカウント
      int _chain{0};
    };
  } // namespace Player
} // namespace Gyro
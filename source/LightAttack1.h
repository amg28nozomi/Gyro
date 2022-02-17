/*****************************************************************//**
 * @file   LightAttack1.h
 * @brief  弱攻撃
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
     * @class  LightAttack1
     * @brief  自機の弱攻撃1処理
     */
    class LightAttack1 : public Object::AttackComponent {
    public:
      /**
       * @brief  コンストラクタ
       * @param  owner 所有者の参照
       * @param  collision 当たり判定情報
       */
      LightAttack1(Object::ObjectBase& owner, std::shared_ptr<Object::CollisionBase> collision);
    protected:
    };
  } // namespace Player
} // namespace Gyro
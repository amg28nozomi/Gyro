/*****************************************************************//**
 * @file   LightAttack1.h
 * @brief  ��U��
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "AttackComponent.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �v���C���[�x�[�X
   */
  namespace Player {
    /**
     * @class  LightAttack1
     * @brief  ���@�̎�U��1����
     */
    class LightAttack1 : public Object::AttackComponent {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  owner ���L�҂̎Q��
       * @param  collision �����蔻����
       */
      LightAttack1(Object::ObjectBase& owner, std::shared_ptr<Object::CollisionBase> collision);
    protected:
    };
  } // namespace Player
} // namespace Gyro
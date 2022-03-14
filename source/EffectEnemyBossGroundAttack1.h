/*****************************************************************//**
 * @file    EffectEnemyBossGroundAttack1.h
 * @brief   �G�{�X�n��U��1�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#pragma once
#include "EffectBase.h"

 /**
  * @brief �Q�[���x�[�X
  */
namespace Gyro {
  /**
   * @brief �G�t�F�N�g�x�[�X
   */
  namespace Effect {
    /**
     * @class EffectEnemyBossGroundAttack1
     * @brief �G�{�X�n��U��1�G�t�F�N�g�N���X
     */
    class EffectEnemyBossGroundAttack1 : public EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectEnemyBossGroundAttack1(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectEnemyBossGroundAttack1();
      /**
       * @brief  ������
       */
      void Init() override;
      /**
       * @brief  �X�V
       */
      void Process() override;
    };
  } // namespace Effect
} // namespace Gyro
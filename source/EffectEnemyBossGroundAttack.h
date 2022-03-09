/*****************************************************************//**
 * @file    EffectEnemyBossGroundAttack.h
 * @brief   �G�{�X�n��U���G�t�F�N�g�N���X
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
     * @class EffectEnemyBossGroundAttack
     * @brief �G�{�X�n��U���G�t�F�N�g�N���X
     */
    class EffectEnemyBossGroundAttack : public EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectEnemyBossGroundAttack(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectEnemyBossGroundAttack();
      /**
       * @brief  ������
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
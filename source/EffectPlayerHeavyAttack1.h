/*****************************************************************//**
 * @file    EffectPlayerHeavyAttack1.h
 * @brief   �v���C���[���U��1�G�t�F�N�g�N���X
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
     * @class EffectPlayerHeavyAttack1
     * @brief �v���C���[���U��1�G�t�F�N�g�N���X
     */
    class EffectPlayerHeavyAttack1 : public EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectPlayerHeavyAttack1(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectPlayerHeavyAttack1();
      /**
       * @brief  ������
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectPlayerAirHeavyAttack1.h
 * @brief   �v���C���[�󒆋��U��1�G�t�F�N�g�N���X
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
     * @class EffectPlayerAirHeavyAttack1
     * @brief �v���C���[�󒆋��U��1�G�t�F�N�g�N���X
     */
    class EffectPlayerAirHeavyAttack1 : public EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectPlayerAirHeavyAttack1(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectPlayerAirHeavyAttack1();
      /**
       * @brief  ������
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectPlayerAirWeakAttack1.h
 * @brief   �v���C���[�󒆎�U��1�G�t�F�N�g�N���X
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
     * @class EffectPlayerAirWeakAttack1
     * @brief �v���C���[�󒆎�U��1�G�t�F�N�g�N���X
     */
    class EffectPlayerAirWeakAttack1 : public EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectPlayerAirWeakAttack1(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectPlayerAirWeakAttack1();
      /**
       * @brief  ������
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
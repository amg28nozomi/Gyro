/*****************************************************************//**
 * @file    EffectPlayerAirWeakAttack3.h
 * @brief   �v���C���[�󒆎�U��3�G�t�F�N�g�N���X
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
     * @class EffectPlayerAirWeakAttack3
     * @brief �v���C���[�󒆎�U��3�G�t�F�N�g�N���X
     */
    class EffectPlayerAirWeakAttack3 : public EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectPlayerAirWeakAttack3(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectPlayerAirWeakAttack3();
      /**
       * @brief  ������
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
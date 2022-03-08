/*****************************************************************//**
 * @file    EffectPlayerJump.h
 * @brief   �v���C���[�W�����v�G�t�F�N�g�N���X
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
     * @class EffectPlayerJump
     * @brief �v���C���[�W�����v�G�t�F�N�g�N���X
     */
    class EffectPlayerJump : public EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectPlayerJump(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectPlayerJump();
      /**
       * @brief  ������
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
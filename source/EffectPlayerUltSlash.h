/*****************************************************************//**
 * @file    EffectPlayerUltSlash.h
 * @brief   �v���C���[�K�E�U���G�t�F�N�g�N���X
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
     * @class EffectPlayerUltSlash
     * @brief �v���C���[�K�E�U���G�t�F�N�g�N���X
     */
    class EffectPlayerUltSlash : public EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectPlayerUltSlash(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectPlayerUltSlash();
      /**
       * @brief  ������
       */
      void Init() override;

    private:
      /**
       * @brief  �G�t�F�N�g����
       */
      void DeadEffect() override;
    };
  } // namespace Effect
} // namespace Gyro
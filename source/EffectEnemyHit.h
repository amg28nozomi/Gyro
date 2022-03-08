/*****************************************************************//**
 * @file    EffectEnemyHit.h
 * @brief   �G��_���G�t�F�N�g�N���X
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
     * @class EffectEnemyHit
     * @brief �G��_���G�t�F�N�g�N���X
     */
    class EffectEnemyHit : public EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectEnemyHit(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectEnemyHit();
      /**
       * @brief  ������
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
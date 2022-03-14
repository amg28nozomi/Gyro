/*****************************************************************//**
 * @file    EffectEnemyBossEyeLight.h
 * @brief   �G�{�X����G�t�F�N�g�N���X
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
     * @class EffectEnemyBossEyeLight
     * @brief �G�{�X����G�t�F�N�g�N���X
     */
    class EffectEnemyBossEyeLight : public EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectEnemyBossEyeLight(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectEnemyBossEyeLight();
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
/*****************************************************************//**
 * @file    EffectEnemyBossExprosion.h
 * @brief   �G�{�X�����G�t�F�N�g�N���X
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
     * @class EffectEnemyBossExprosion
     * @brief �G�{�X�����G�t�F�N�g�N���X
     */
    class EffectEnemyBossExprosion : public EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectEnemyBossExprosion(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectEnemyBossExprosion();
      /**
       * @brief  ������
       */
      void Init() override;
    };
  } // namespace Effect
} // namespace Gyro
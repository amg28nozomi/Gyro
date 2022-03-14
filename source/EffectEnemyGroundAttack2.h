/*****************************************************************//**
 * @file    EffectEnemyGroundAttack2.h
 * @brief   �G�n��U��2�G�t�F�N�g�N���X
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
     * @class EffectEnemyGroundAttack2
     * @brief �G�n��U��2�G�t�F�N�g�N���X
     */
    class EffectEnemyGroundAttack2 : public EffectBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      EffectEnemyGroundAttack2(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~EffectEnemyGroundAttack2();
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
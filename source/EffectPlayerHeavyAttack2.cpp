/*****************************************************************//**
 * @file    EffectPlayerHeavyAttack2.cpp
 * @brief   �v���C���[���U��2�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerHeavyAttack2.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerHeavyAttack2::EffectPlayerHeavyAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerHeavyAttack2::~EffectPlayerHeavyAttack2() {

    }

    void EffectPlayerHeavyAttack2::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerHeavyAttack2);
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectPlayerAirHeavyAttack2.cpp
 * @brief   �v���C���[�󒆋��U��2�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirHeavyAttack2.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerAirHeavyAttack2::EffectPlayerAirHeavyAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerAirHeavyAttack2::~EffectPlayerAirHeavyAttack2() {

    }

    void EffectPlayerAirHeavyAttack2::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirHeavyAttack2);
    }
  } // namespace Effect
} // namespace Gyro
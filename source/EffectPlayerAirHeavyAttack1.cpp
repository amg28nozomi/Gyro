/*****************************************************************//**
 * @file    EffectPlayerAirHeavyAttack1.cpp
 * @brief   �v���C���[�󒆋��U��1�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirHeavyAttack1.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerAirHeavyAttack1::EffectPlayerAirHeavyAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerAirHeavyAttack1::~EffectPlayerAirHeavyAttack1() {

    }

    void EffectPlayerAirHeavyAttack1::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirHeavyAttack1);
    }
  } // namespace Effect
} // namespace Gyro
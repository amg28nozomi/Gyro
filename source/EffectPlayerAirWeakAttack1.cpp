/*****************************************************************//**
 * @file    EffectPlayerAirWeakAttack1.cpp
 * @brief   �v���C���[�󒆎�U��1�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirWeakAttack1.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerAirWeakAttack1::EffectPlayerAirWeakAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerAirWeakAttack1::~EffectPlayerAirWeakAttack1() {

    }

    void EffectPlayerAirWeakAttack1::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirWeakAttack1);
    }
  } // namespace Effect
} // namespace Gyro
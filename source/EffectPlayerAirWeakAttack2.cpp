/*****************************************************************//**
 * @file    EffectPlayerAirWeakAttack2.cpp
 * @brief   �v���C���[�󒆎�U��2�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirWeakAttack2.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerAirWeakAttack2::EffectPlayerAirWeakAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerAirWeakAttack2::~EffectPlayerAirWeakAttack2() {

    }

    void EffectPlayerAirWeakAttack2::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirWeakAttack2);
    }
  } // namespace Effect
} // namespace Gyro
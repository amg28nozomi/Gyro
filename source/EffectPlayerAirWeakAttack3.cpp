/*****************************************************************//**
 * @file    EffectPlayerAirWeakAttack3.cpp
 * @brief   �v���C���[�󒆎�U��3�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirWeakAttack3.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerAirWeakAttack3::EffectPlayerAirWeakAttack3(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerAirWeakAttack3::~EffectPlayerAirWeakAttack3() {

    }

    void EffectPlayerAirWeakAttack3::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirWeakAttack3);
    }
  } // namespace Effect
} // namespace Gyro
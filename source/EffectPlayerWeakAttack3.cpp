/*****************************************************************//**
 * @file    EffectPlayerWeakAttack3.cpp
 * @brief   �v���C���[��U��3�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerWeakAttack3.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerWeakAttack3::EffectPlayerWeakAttack3(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerWeakAttack3::~EffectPlayerWeakAttack3() {

    }

    void EffectPlayerWeakAttack3::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerWeakAttack3);
    }
  } // namespace Effect
} // namespace Gyro
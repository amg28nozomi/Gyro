/*****************************************************************//**
 * @file    EffectPlayerWeakAttack2.cpp
 * @brief   �v���C���[��U��2�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerWeakAttack2.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerWeakAttack2::EffectPlayerWeakAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerWeakAttack2::~EffectPlayerWeakAttack2() {

    }

    void EffectPlayerWeakAttack2::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerWeakAttack2);
    }
  } // namespace Effect
} // namespace Gyro
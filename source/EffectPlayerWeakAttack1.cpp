/*****************************************************************//**
 * @file    EffectPlayerWeakAttack1.cpp
 * @brief   �v���C���[��U��1�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerWeakAttack1.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerWeakAttack1::EffectPlayerWeakAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerWeakAttack1::~EffectPlayerWeakAttack1() {

    }

    void EffectPlayerWeakAttack1::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerWeakAttack1);
    }
  } // namespace Effect
} // namespace Gyro
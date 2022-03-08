/*****************************************************************//**
 * @file    EffectPlayerWeakAttackEX.cpp
 * @brief   �v���C���[��U��EX�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerWeakAttackEX.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerWeakAttackEX::EffectPlayerWeakAttackEX(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerWeakAttackEX::~EffectPlayerWeakAttackEX() {

    }

    void EffectPlayerWeakAttackEX::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerWeakAttackEX);
    }
  } // namespace Effect
} // namespace Gyro
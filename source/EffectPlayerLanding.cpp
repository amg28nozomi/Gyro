/*****************************************************************//**
 * @file    EffectPlayerLanding.cpp
 * @brief   �v���C���[��_���G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerLanding.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerLanding::EffectPlayerLanding(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerLanding::~EffectPlayerLanding() {

    }

    void EffectPlayerLanding::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerLanding);
    }
  } // namespace Effect
} // namespace Gyro
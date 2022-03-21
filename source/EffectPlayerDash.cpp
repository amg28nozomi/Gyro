/*****************************************************************//**
 * @file    EffectPlayerDash.cpp
 * @brief   �v���C���[�_�b�V���G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerDash.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerDash::EffectPlayerDash(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerDash::~EffectPlayerDash() {

    }

    void EffectPlayerDash::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerDash);
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectPlayerJustEmit.cpp
 * @brief   �v���C���[�W���X�g�I���G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerJustEmit.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerJustEmit::EffectPlayerJustEmit(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerJustEmit::~EffectPlayerJustEmit() {

    }

    void EffectPlayerJustEmit::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerJustEmit);
    }
  } // namespace Effect
} // namespace Gyro
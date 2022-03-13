/*****************************************************************//**
 * @file    EffectPlayerJustActivate.cpp
 * @brief   �v���C���[�W���X�g�����G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerJustActivate.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerJustActivate::EffectPlayerJustActivate(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerJustActivate::~EffectPlayerJustActivate() {

    }

    void EffectPlayerJustActivate::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerJustActivate);
    }
  } // namespace Effect
} // namespace Gyro
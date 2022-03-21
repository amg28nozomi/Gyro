/*****************************************************************//**
 * @file    EffectPlayerUltActivate.cpp
 * @brief   �v���C���[�K�E�����G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerUltActivate.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerUltActivate::EffectPlayerUltActivate(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerUltActivate::~EffectPlayerUltActivate() {

    }

    void EffectPlayerUltActivate::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerUltActivate);
    }
  } // namespace Effect
} // namespace Gyro
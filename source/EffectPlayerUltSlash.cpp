/*****************************************************************//**
 * @file    EffectPlayerUltSlash.cpp
 * @brief   �v���C���[�K�E�����G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerUltSlash.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerUltSlash::EffectPlayerUltSlash(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerUltSlash::~EffectPlayerUltSlash() {

    }

    void EffectPlayerUltSlash::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerUltSlash);
    }
  } // namespace Effect
} // namespace Gyro
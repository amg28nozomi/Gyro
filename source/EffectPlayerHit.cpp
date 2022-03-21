/*****************************************************************//**
 * @file    EffectPlayerHit.cpp
 * @brief   �v���C���[��_���G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerHit.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerHit::EffectPlayerHit(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerHit::~EffectPlayerHit() {

    }

    void EffectPlayerHit::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerHit);
    }
  } // namespace Effect
} // namespace Gyro
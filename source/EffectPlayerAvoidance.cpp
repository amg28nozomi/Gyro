/*****************************************************************//**
 * @file    EffectPlayerAvoidance.cpp
 * @brief   �v���C���[��_���G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAvoidance.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerAvoidance::EffectPlayerAvoidance(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerAvoidance::~EffectPlayerAvoidance() {

    }

    void EffectPlayerAvoidance::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerAvoidance);
    }
  } // namespace Effect
} // namespace Gyro
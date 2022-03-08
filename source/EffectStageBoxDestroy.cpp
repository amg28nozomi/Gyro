/*****************************************************************//**
 * @file    EffectStageBoxDestroy.cpp
 * @brief   �X�e�[�W���j��G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectStageBoxDestroy.h"

namespace Gyro {
  namespace Effect {
    EffectStageBoxDestroy::EffectStageBoxDestroy(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectStageBoxDestroy::~EffectStageBoxDestroy() {

    }

    void EffectStageBoxDestroy::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::StageBoxDestroy);
    }
  } // namespace Effect
} // namespace Gyro
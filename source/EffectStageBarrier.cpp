/*****************************************************************//**
 * @file    EffectStageBarrier.cpp
 * @brief   �X�e�[�W�o���A�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectStageBarrier.h"

namespace Gyro {
  namespace Effect {
    EffectStageBarrier::EffectStageBarrier(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectStageBarrier::~EffectStageBarrier() {

    }

    void EffectStageBarrier::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::StageBarrier);
    }
  } // namespace Effect
} // namespace Gyro
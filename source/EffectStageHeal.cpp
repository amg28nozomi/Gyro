/*****************************************************************//**
 * @file    EffectStageHeal.cpp
 * @brief   �X�e�[�W�񕜃G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectStageHeal.h"

namespace Gyro {
  namespace Effect {
    EffectStageHeal::EffectStageHeal(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectStageHeal::~EffectStageHeal() {

    }

    void EffectStageHeal::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::StageHeal);
    }
  } // namespace Effect
} // namespace Gyro
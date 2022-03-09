/*****************************************************************//**
 * @file    EffectEnemyBossEyeLight.cpp
 * @brief   �G�{�X����G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossEyeLight.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossEyeLight::EffectEnemyBossEyeLight(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyBossEyeLight::~EffectEnemyBossEyeLight() {

    }

    void EffectEnemyBossEyeLight::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossEyeLight);
    }
  } // namespace Effect
} // namespace Gyro
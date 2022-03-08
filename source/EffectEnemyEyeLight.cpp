/*****************************************************************//**
 * @file    EffectEnemyEyeLight.cpp
 * @brief   �G����G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyEyeLight.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyEyeLight::EffectEnemyEyeLight(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyEyeLight::~EffectEnemyEyeLight() {

    }

    void EffectEnemyEyeLight::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyEyeLight);
    }
  } // namespace Effect
} // namespace Gyro
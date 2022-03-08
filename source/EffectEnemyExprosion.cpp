/*****************************************************************//**
 * @file    EffectEnemyExprosion.cpp
 * @brief   �G�����G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyExprosion.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyExprosion::EffectEnemyExprosion(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyExprosion::~EffectEnemyExprosion() {

    }

    void EffectEnemyExprosion::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyExprosion);
    }
  } // namespace Effect
} // namespace Gyro
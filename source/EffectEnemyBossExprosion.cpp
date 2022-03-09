/*****************************************************************//**
 * @file    EffectEnemyBossExprosion.cpp
 * @brief   �G�{�X�����G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossExprosion.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossExprosion::EffectEnemyBossExprosion(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyBossExprosion::~EffectEnemyBossExprosion() {

    }

    void EffectEnemyBossExprosion::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossExprosion);
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectEnemyBossHit.cpp
 * @brief   �G�{�X��_���G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossHit.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossHit::EffectEnemyBossHit(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyBossHit::~EffectEnemyBossHit() {

    }

    void EffectEnemyBossHit::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossHit);
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectEnemyBossAirAttack.cpp
 * @brief   �G�{�X�󒆍U���G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossAirAttack.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossAirAttack::EffectEnemyBossAirAttack(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyBossAirAttack::~EffectEnemyBossAirAttack() {

    }

    void EffectEnemyBossAirAttack::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossAirAttack);
    }
  } // namespace Effect
} // namespace Gyro
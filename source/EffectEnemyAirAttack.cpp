/*****************************************************************//**
 * @file    EffectEnemyAirAttack.cpp
 * @brief   �G�󒆍U���G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyAirAttack.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyAirAttack::EffectEnemyAirAttack(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyAirAttack::~EffectEnemyAirAttack() {

    }

    void EffectEnemyAirAttack::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyAirAttack);
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectEnemyBossGroundAttack.cpp
 * @brief   �G�{�X�n��U���G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossGroundAttack.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossGroundAttack::EffectEnemyBossGroundAttack(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyBossGroundAttack::~EffectEnemyBossGroundAttack() {

    }

    void EffectEnemyBossGroundAttack::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossGroundAttack);
    }
  } // namespace Effect
} // namespace Gyro
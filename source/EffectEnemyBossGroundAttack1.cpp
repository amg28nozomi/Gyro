/*****************************************************************//**
 * @file    EffectEnemyBossGroundAttack1.cpp
 * @brief   �G�{�X�n��U��1�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossGroundAttack1.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossGroundAttack1::EffectEnemyBossGroundAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyBossGroundAttack1::~EffectEnemyBossGroundAttack1() {

    }

    void EffectEnemyBossGroundAttack1::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossGroundAttack1);
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectEnemyBossGroundAttack2.cpp
 * @brief   �G�{�X�n��U��2�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossGroundAttack2.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossGroundAttack2::EffectEnemyBossGroundAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyBossGroundAttack2::~EffectEnemyBossGroundAttack2() {

    }

    void EffectEnemyBossGroundAttack2::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossGroundAttack2);
    }
  } // namespace Effect
} // namespace Gyro
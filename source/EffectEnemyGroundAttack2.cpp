/*****************************************************************//**
 * @file    EffectEnemyGroundAttack2.cpp
 * @brief   �G�n��U��2�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyGroundAttack2.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyGroundAttack2::EffectEnemyGroundAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyGroundAttack2::~EffectEnemyGroundAttack2() {

    }

    void EffectEnemyGroundAttack2::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyGroundAttack2);
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectEnemyGroundAttack1.cpp
 * @brief   �G�n��U��1�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyGroundAttack1.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyGroundAttack1::EffectEnemyGroundAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyGroundAttack1::~EffectEnemyGroundAttack1() {

    }

    void EffectEnemyGroundAttack1::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyGroundAttack1);
    }
  } // namespace Effect
} // namespace Gyro
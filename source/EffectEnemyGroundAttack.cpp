/*****************************************************************//**
 * @file    EffectEnemyGroundAttack.cpp
 * @brief   �G�n��U���G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyGroundAttack.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyGroundAttack::EffectEnemyGroundAttack(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyGroundAttack::~EffectEnemyGroundAttack() {

    }

    void EffectEnemyGroundAttack::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyGroundAttack);
    }
  } // namespace Effect
} // namespace Gyro
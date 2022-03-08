/*****************************************************************//**
 * @file    EffectEnemyHit.cpp
 * @brief   �G��_���G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyHit.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyHit::EffectEnemyHit(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyHit::~EffectEnemyHit() {

    }

    void EffectEnemyHit::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyHit);
    }
  } // namespace Effect
} // namespace Gyro
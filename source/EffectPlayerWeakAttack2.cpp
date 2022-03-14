/*****************************************************************//**
 * @file    EffectPlayerWeakAttack2.cpp
 * @brief   �v���C���[��U��2�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerWeakAttack2.h"

namespace {
  // �G�t�F�N�g�������v���C���[�̏��
  constexpr auto CheckState = Gyro::Player::Player::PlayerState::Attack2;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerWeakAttack2::EffectPlayerWeakAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerWeakAttack2::~EffectPlayerWeakAttack2() {

    }

    void EffectPlayerWeakAttack2::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerWeakAttack2);
      // �v���C���[��Ԋm�F����
      _isCheck = true;
      _checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
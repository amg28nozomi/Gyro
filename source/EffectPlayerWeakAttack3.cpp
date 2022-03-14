/*****************************************************************//**
 * @file    EffectPlayerWeakAttack3.cpp
 * @brief   �v���C���[��U��3�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerWeakAttack3.h"

namespace {
  // �G�t�F�N�g�������v���C���[�̏��
  constexpr auto CheckState = Gyro::Player::Player::PlayerState::Attack3;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerWeakAttack3::EffectPlayerWeakAttack3(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerWeakAttack3::~EffectPlayerWeakAttack3() {

    }

    void EffectPlayerWeakAttack3::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerWeakAttack3);
      // �v���C���[��Ԋm�F����
      _isCheck = true;
      _checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
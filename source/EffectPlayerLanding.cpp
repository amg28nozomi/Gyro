/*****************************************************************//**
 * @file    EffectPlayerLanding.cpp
 * @brief   �v���C���[���n�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerLanding.h"

namespace {
  // �G�t�F�N�g�������v���C���[�̏��
  //constexpr auto CheckState = Gyro::Player::Player::PlayerState::;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerLanding::EffectPlayerLanding(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerLanding::~EffectPlayerLanding() {

    }

    void EffectPlayerLanding::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerLanding);
      // �v���C���[��Ԋm�F����
      //_isCheck = true;
      //_checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
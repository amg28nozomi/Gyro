/*****************************************************************//**
 * @file    EffectPlayerAvoidance.cpp
 * @brief   �v���C���[����G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAvoidance.h"

namespace {
  // �G�t�F�N�g�������v���C���[�̏��
  //constexpr auto CheckState = Gyro::Player::Player::PlayerState::Dash;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerAvoidance::EffectPlayerAvoidance(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerAvoidance::~EffectPlayerAvoidance() {

    }

    void EffectPlayerAvoidance::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerAvoidance);
      // �v���C���[��Ԋm�F����
      //_isCheck = true;
      //_checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
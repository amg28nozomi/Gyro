/*****************************************************************//**
 * @file    EffectPlayerDash.cpp
 * @brief   �v���C���[�_�b�V���G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerDash.h"

namespace {
  // �G�t�F�N�g�������v���C���[�̏��
  //constexpr auto CheckState = Gyro::Player::Player::PlayerState::Run;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerDash::EffectPlayerDash(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerDash::~EffectPlayerDash() {

    }

    void EffectPlayerDash::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerDash);
      // �v���C���[��Ԋm�F����
      //_isCheck = true;
      //_checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
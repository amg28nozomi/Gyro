/*****************************************************************//**
 * @file    EffectPlayerJump.cpp
 * @brief   �v���C���[�W�����v�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerJump.h"

namespace {
  // �G�t�F�N�g�������v���C���[�̏��
  //constexpr auto CheckState = Gyro::Player::Player::PlayerState::Jump;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerJump::EffectPlayerJump(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerJump::~EffectPlayerJump() {

    }

    void EffectPlayerJump::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerJump);
      // �v���C���[��Ԋm�F����
      //_isCheck = true;
      //_checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
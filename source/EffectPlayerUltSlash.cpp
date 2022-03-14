/*****************************************************************//**
 * @file    EffectPlayerUltSlash.cpp
 * @brief   �v���C���[�K�E�����G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerUltSlash.h"

namespace {
  // �G�t�F�N�g�������v���C���[�̏��
  //constexpr auto CheckState = Gyro::Player::Player::PlayerState::Attack1;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerUltSlash::EffectPlayerUltSlash(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerUltSlash::~EffectPlayerUltSlash() {

    }

    void EffectPlayerUltSlash::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerUltSlash);
      // �v���C���[��Ԋm�F����
      //_isCheck = true;
      //_checkState = CheckState;
    }

    void EffectPlayerUltSlash::DeadEffect() {
      // �G�t�F�N�g����
      EffectBase::DeadEffect();
      // �K�E�U���G�t�F�N�g�I��
      _app.GetEffectServer().SetUltSlashEnd(true);
    }
  } // namespace Effect
} // namespace Gyro
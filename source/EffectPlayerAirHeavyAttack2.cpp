/*****************************************************************//**
 * @file    EffectPlayerAirHeavyAttack2.cpp
 * @brief   �v���C���[�󒆋��U��2�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirHeavyAttack2.h"

namespace {
  // ��������Đ��܂ł̃��O�萔
  constexpr int PlayLag = 10;
  // �G�t�F�N�g�������v���C���[�̏��
  constexpr auto CheckState = Gyro::Player::Player::PlayerState::JumpAttack2;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerAirHeavyAttack2::EffectPlayerAirHeavyAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerAirHeavyAttack2::~EffectPlayerAirHeavyAttack2() {

    }

    void EffectPlayerAirHeavyAttack2::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirHeavyAttack2);
      // ���O�ݒ�
      _playLag = PlayLag;
      // �v���C���[��Ԋm�F����
      _isCheck = true;
      _checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
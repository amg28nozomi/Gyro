/*****************************************************************//**
 * @file    EffectPlayerAirHeavyAttack1.cpp
 * @brief   �v���C���[�󒆋��U��1�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirHeavyAttack1.h"

namespace {
  // ��������Đ��܂ł̃��O�萔
  constexpr int PlayLag = 5;
  // �G�t�F�N�g�������v���C���[�̏��
  constexpr auto CheckState = Gyro::Player::Player::PlayerState::JumpAttack1;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerAirHeavyAttack1::EffectPlayerAirHeavyAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerAirHeavyAttack1::~EffectPlayerAirHeavyAttack1() {

    }

    void EffectPlayerAirHeavyAttack1::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirHeavyAttack1);
      // ���O�ݒ�
      _playLag = PlayLag;
      // �v���C���[��Ԋm�F����
      _isCheck = true;
      _checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
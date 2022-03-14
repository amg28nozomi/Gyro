/*****************************************************************//**
 * @file    EffectPlayerHeavyAttack3.cpp
 * @brief   �v���C���[���U��3�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerHeavyAttack3.h"

namespace {
  // ��������Đ��܂ł̃��O�萔
  constexpr int PlayLag = 60;
  // �G�t�F�N�g�������v���C���[�̏��
  constexpr auto CheckState = Gyro::Player::Player::PlayerState::Attack3;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerHeavyAttack3::EffectPlayerHeavyAttack3(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerHeavyAttack3::~EffectPlayerHeavyAttack3() {

    }

    void EffectPlayerHeavyAttack3::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerHeavyAttack3);
      // ���O�ݒ�
      _playLag = PlayLag;
      // �v���C���[��Ԋm�F����
      _isCheck = true;
      _checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
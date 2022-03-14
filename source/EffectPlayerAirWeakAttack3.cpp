/*****************************************************************//**
 * @file    EffectPlayerAirWeakAttack3.cpp
 * @brief   �v���C���[�󒆎�U��3�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirWeakAttack3.h"

namespace {
  // ��������Đ��܂ł̃��O�萔
  constexpr int PlayLag = 5;
  // �G�t�F�N�g�������v���C���[�̏��
  constexpr auto CheckState = Gyro::Player::Player::PlayerState::JumpAttack3;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerAirWeakAttack3::EffectPlayerAirWeakAttack3(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerAirWeakAttack3::~EffectPlayerAirWeakAttack3() {

    }

    void EffectPlayerAirWeakAttack3::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirWeakAttack3);
      // ���O�ݒ�
      _playLag = PlayLag;
      // �v���C���[��Ԋm�F����
      _isCheck = true;
      _checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
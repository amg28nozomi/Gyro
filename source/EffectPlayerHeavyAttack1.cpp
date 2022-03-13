/*****************************************************************//**
 * @file    EffectPlayerHeavyAttack1.cpp
 * @brief   �v���C���[���U��1�G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerHeavyAttack1.h"

namespace {
  // ��������Đ��܂ł̃��O�萔
  constexpr int PlayLag = 25;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerHeavyAttack1::EffectPlayerHeavyAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectPlayerHeavyAttack1::~EffectPlayerHeavyAttack1() {

    }

    void EffectPlayerHeavyAttack1::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::PlayerHeavyAttack1);
      // ���O�ݒ�
      _playLag = PlayLag;
    }
  } // namespace Effect
} // namespace Gyro
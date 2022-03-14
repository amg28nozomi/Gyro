/*****************************************************************//**
 * @file    EffectEnemyBossAirAttack.cpp
 * @brief   �G�{�X�󒆍U���G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossAirAttack.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossAirAttack::EffectEnemyBossAirAttack(Application::ApplicationMain& app) : EffectBase(app) {
      // ������
      Init();
    }

    EffectEnemyBossAirAttack::~EffectEnemyBossAirAttack() {

    }

    void EffectEnemyBossAirAttack::Init() {
      // �G�t�F�N�g�n���h���̎擾
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossAirAttack);
    }

    void EffectEnemyBossAirAttack::Process() {
      // �Đ����łȂ��ꍇ���f
      if (!_isPlay) {
        return;
      }
      // �G�t�F�N�g�̈ʒu��ݒ�
      auto& [x, y, z] = _ePos.GetVector3();
      SetPosPlayingEffekseer3DEffect(_playHandle, x, y, z);
      // �G�t�F�N�g�̌�����ݒ�
      SetRotationPlayingEffekseer3DEffect(_playHandle, 0.0f, _eRadY, 0.0f);
      // �G�t�F�N�g�Đ��I��������
      if (IsEffekseer3DEffectPlaying(_playHandle)) {
        // �G�t�F�N�g����
        DeadEffect();
      }
    }
  } // namespace Effect
} // namespace Gyro
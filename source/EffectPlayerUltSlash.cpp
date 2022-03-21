/*****************************************************************//**
 * @file    EffectPlayerUltSlash.cpp
 * @brief   �v���C���[�K�E�����G�t�F�N�g�N���X
 *
 * @author  �{�V�s��
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerUltSlash.h"

namespace {
  // �G�t�F�N�g�I���t���O�Z�b�g�J�E���g�l�萔
  constexpr int EndCount = 105;
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
    }

    void EffectPlayerUltSlash::Process() {
      EffectBase::Process();
      // �I���t���O�J�E���g��1���₷
      _endCount++;
      if (EndCount <= _endCount) {
        // �K�E�U���G�t�F�N�g�I��
        _app.GetEffectServer().SetUltSlashEnd(true);
      }
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectBase.cpp
 * @brief   �G�t�F�N�g�̊��N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "EffectBase.h"

namespace Gyro {
  namespace Effect {
    EffectBase::EffectBase(Application::ApplicationMain& app) : _app(app) {

    }

    EffectBase::~EffectBase() {

    }

    void EffectBase::Init() {

    }

    void EffectBase::Process() {
      // �Đ�����������
      if (_isPlay) {
        // �G�t�F�N�g�Đ��I��������
        if (IsEffekseer3DEffectPlaying(_playHandle)) {
          // �G�t�F�N�g����
          DeadEffect();
        }
        return;
      }
      // ��������Đ��܂ł̃��O�����O�J�E���g����������
      if (_playLag <= _lagCount) {
        // �G�t�F�N�g�Đ�
        PlayEffect();
        return;
      }
      // ���O�J�E���g�𑝂₷
      _lagCount++;
    }

    void EffectBase::PlayEffect() {
      // �G�t�F�N�g�Đ�
      _playHandle = PlayEffekseer3DEffect(_effectHandle);
      // �G�t�F�N�g�̈ʒu��ݒ�
      auto& [x, y, z] = _ePos.GetVector3();
      SetPosPlayingEffekseer3DEffect(_playHandle, x, y, z);
      // �G�t�F�N�g�̌�����ݒ�
      SetRotationPlayingEffekseer3DEffect(_playHandle, 0.0f, _eRad, 0.0f);
      // �G�t�F�N�g�������
      _effectState = EffectState::Active;
      // �G�t�F�N�g�Đ�����
      _isPlay = true;
    }

    void EffectBase::DeadEffect() {
      // �G�t�F�N�g��~
      StopEffekseer3DEffect(_playHandle);
      // �G�t�F�N�g�Đ��n���h������
      _playHandle = -1;
      // �G�t�F�N�g���S���
      _effectState = EffectState::Dead;
    }
  } // namespace Effect
} // namespace Gyro
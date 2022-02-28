/*****************************************************************//**
 * @file   SoundComponent.cpp
 * @brief  �T�E���h�R���|�[�l���g�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "SoundComponent.h"
#include <DxLib.h>
#include "../Application/ApplicationBase.h"

namespace AppFrame {
  namespace Sound {

    SoundComponent::SoundComponent(Application::ApplicationBase& app) : _app(app) {
    }

    bool SoundComponent::PlayBackGround(std::string_view key) const {
      // �w�肵�������t�@�C���̃o�b�N�O���E���h�Đ����s��
      return Play(key, DX_PLAYTYPE_BACK);
    }

    bool SoundComponent::PlayLoop(std::string_view key) const {
      // �w�肵�������t�@�C���̃��[�v�Đ����s��
      return Play(key, DX_PLAYTYPE_LOOP);
    }

    bool SoundComponent::StopSound(std::string_view key) const {
      // �T�E���h�n���h�����擾
      auto handle = SoundHandle(key);
      if (handle == -1) {
        return false; // �擾���s
      }
      // �T�E���h�̍Đ����~����
      if (StopSoundMem(handle) == -1) {
        return false; // ��蔭��
      }
      return true; // ��~����
    }

    bool SoundComponent::CheckSound(std::string_view key) const {
      // �T�E���h�n���h���̎擾
      const auto handle = SoundHandle(key);
      // �T�E���h�n���h���̎擾�ɐ���������
      if (handle == -1) {
        return false; // ���s
      }
      // �������Đ������ɉ����ăt���O��Ԃ�
      return (CheckSoundMem(handle) == 1) ? true : false;
    }

    bool SoundComponent::SetVolume(std::string_view key, int volume) const {
      // �T�E���h�n���h�����擾
      auto handle = SoundHandle(key);
      // �T�E���h�n���h���̎擾�ɐ���������
      if (handle == -1) {
        return false; // �T�E���h�n���h���̎擾�Ɏ��s
      }
      // �T�E���h�̉��ʂ�ݒ肷��
      if (ChangeVolumeSoundMem(volume, handle) == -1) {
        return false;
      }
      return true;
    }

    bool SoundComponent::Play(std::string_view key, const int type) const {
      // �~���[�g��ԂɂȂ��Ă��Ȃ���
      if (_mute) {
        return false; // �Đ����s��Ȃ�
      }
      // �擾�����T�E���h�n���h���̍Đ�
      if (PlaySoundMem(SoundHandle(key), type, TRUE) == -1) {
        return false; // �Đ����s
      }
      return true; // �Đ�����
    }

    const int SoundComponent::SoundHandle(std::string_view key) const {
      // �擾�����T�E���h�n���h����Ԃ�
      return _app.GetSoundServer().GetSoundMem(key);
    }
  } // namespace Sound
} // namespace Gyro
/*****************************************************************//**
 * @file   SoundServer.cpp
 * @brief  �������Ǘ�����T�[�o�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#include "SoundServer.h"
#include <DxLib.h>
#include "SoundMem.h"

namespace AppFrame {
  namespace Sound {

    SoundServer::SoundServer() : Server::ServerTemplateUnordered<std::string, int>() {
#ifdef _DEBUG
      SetServerName("SoundServer"); // �T�[�o���̐ݒ�
#endif
    }

    bool SoundServer::Release() {
      if (_registry.empty()) {
        return true; // �f�[�^����
      }
      // �T�E���h�n���h���̑S�J�����s��
      for (auto [key, handle] : _registry) {
        // �T�E���h�n���h���̉�����s��
        DeleteSoundMem(handle);
      }
      _registry.clear(); // ���W�X�g�����������
      return true; // ����I��
    }

    bool SoundServer::AddSound(std::string_view key, const std::filesystem::path soundFile) {
      // �L�[�͖��g�p��
      if (_registry.contains(key.data())) {
        return false; // �L�[���d�����Ă���
      }
      // �������̓ǂݎ��
      auto handle = LoadSoundMem(soundFile.string().data());
      // �T�E���h�n���h���̎擾�ɐ���������
      if (handle == -1) {
        return false; // �ǂݎ�莸�s
      }
      // ���W�X�g���ɓo�^
      _registry.emplace(key.data(), handle);
      return true;
    }

    void SoundServer::AddSounds(const SoundMap& soundMap) {
      // �R���e�i�̏�����Ƀf�[�^��ǂݎ��
      for (auto [key, path] : soundMap) {
        AddSound(key, path);
      }
    }

    int SoundServer::GetSoundMem(std::string_view key) const {
      if (!_registry.contains(key.data())) {
        return -1; // �L�[���L���ł͂Ȃ�
      }
      // �T�E���h�n���h����Ԃ�
      return _registry.at(key.data());
    }
  } // namespace Sound
} // nemaspace AppFrame
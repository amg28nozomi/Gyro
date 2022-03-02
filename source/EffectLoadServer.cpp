/*****************************************************************//**
 * @file    EffectLoadServer.cpp
 * @brief   �G�t�F�N�g���Ǘ�����T�[�o�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#include "EffectLoadServer.h"

namespace Gyro {
  namespace Effect {
    EffectLoadServer::EffectLoadServer() : AppServer::ServerTemplateUnordered<std::string, int>() {
#ifdef _DEBUG
      SetServerName("EffectLoadServer"); // �T�[�o���̐ݒ�
#endif
    }

    bool EffectLoadServer::Release() {
      if (_registry.empty()) {
        return true; // �f�[�^����
      }
      // �G�t�F�N�g�n���h���̑S�J�����s��
      for (auto [key, handle] : _registry) {
        // �G�t�F�N�g�n���h���̉�����s��
        DeleteEffekseerEffect(handle);
      }
      _registry.clear(); // ���W�X�g�����������
      return true; // ����I��
    }


    void EffectLoadServer::AddEffects(const EffectMap& effectMap) {
      // �R���e�i�̏�����Ƀf�[�^��ǂݎ��
      for (auto [key, path, magni] : effectMap) {
        AddEffect(key, path, magni);
      }
    }

    int EffectLoadServer::GetEffectHandle(std::string_view key) const {
      if (!_registry.contains(key.data())) {
        return -1; // �L�[���L���ł͂Ȃ�
      }
      // �G�t�F�N�g�n���h����Ԃ�
      return _registry.at(key.data());
    }

    bool EffectLoadServer::AddEffect(std::string_view key, const std::filesystem::path effectFile, const float magni) {
      // �L�[�͖��g�p��
      if (_registry.contains(key.data())) {
        return false; // �L�[���d�����Ă���
      }
      // �G�t�F�N�g���̓ǂݎ��
      auto handle = LoadEffekseerEffect(effectFile.string().data(), magni);
      // �G�t�F�N�g�n���h���̎擾�ɐ���������
      if (handle == -1) {
        return false; // �ǂݎ�莸�s
      }
      // ���W�X�g���ɓo�^
      _registry.emplace(key.data(), handle);
      return true;
    }
  } // namespace Effect
} // namespace Gyro
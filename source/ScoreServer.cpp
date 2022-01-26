/*****************************************************************//**
 * @file   ScoreServer.cpp
 * @brief  �Q�[���X�R�A���Ǘ�����X�R�A�T�[�o�̒�`
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "ScoreServer.h"
#include "ScoreBase.h"

namespace Gyro {
  namespace Score {

    ScoreServer::ScoreServer() : AppFrame::Server::ServerTemplateUnordered<std::string, ScoreBase>() {
#ifdef _DEBUG
      SetServerName("ScoreServer"); // �T�[�o���̐ݒ�
#endif
    }

    bool ScoreServer::Release() {
      using UnorderedServer = AppFrame::Server::ServerTemplateUnordered<std::string, ScoreBase>;
      return UnorderedServer::Release();
    }

    bool ScoreServer::AddScore(std::string_view key, ScoreBase score) {
      // �L�[���o�^�ς݂̏ꍇ�̓X�R�A�̔�r���s��
      if (!UseKey(key.data())) {
        // �o�^�Ώۂ͓o�^����Ă���X�R�A�������Ă��邩
        if (_registry[key.data()].IsBig(score) != true) {
          return false; // �Ώۖ����̂��ߓo�^���Ȃ�
        }
        // �ΏۃX�R�A���폜����
        _registry.erase(key.data());
      }
      // �X�R�A��o�^����
      _registry.emplace(key.data(), score);
      return true;
    }

    int ScoreServer::GetScore(std::string_view key) const {
      // �L�[���o�^����Ă��邩
      if (UseKey(key.data())) {
        return -1; // ���o�^
      }
      // �Q�[���X�R�A��Ԃ�(�����l)
      return _registry.at(key.data()).GetInteger();
    }

    bool ScoreServer::EraceScore(std::string_view key) {
      // �L�[���o�^����Ă��邩
      if (UseKey(key.data())) {
        return false; // ���o�^
      }
      // �ΏۃX�R�A�f�[�^���폜����
      _registry.erase(key.data());
      return true; // �폜����
    }
  } // namespace Score
} // namespace Gyro
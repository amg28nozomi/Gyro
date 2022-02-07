/*****************************************************************//**
 * @file   SpawnServer.cpp
 * @brief  �I�u�W�F�N�g�̃X�|�[�������Ǘ�����T�[�o�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "SpawnServer.h"
#include "ApplicationMain.h"
#include "ObjectBase.h"
#include "ObjectServer.h"
#include "Player.h"

namespace Gyro {
  namespace Object {

    SpawnServer::SpawnServer(Application::ApplicationMain& app) : AppFrame::Server::ServerTemplateUnordered<std::string, SpawnMap>(), _appMain(app) {
#ifdef _DEBUG
      // �T�[�o���ݒ�
      SetServerName("SpawnServer");
#endif
      _stage.clear();
    }

    bool SpawnServer::Release() {
      // �X�|�[�������������
      for (auto&& [key, stage] : _registry) {
        stage.clear();
      }
      _registry.clear(); // ���폜
      return true;
    }

    bool SpawnServer::AddSpawnTable(std::string_view key, const SpawnMap& spawnMap) {
      // �f�[�^���o�^����Ă��邩
      if (spawnMap.empty()) [[unlikely]] {
#ifdef _DEBUG
        throw LogicError("�X�|�[����񂪋�ł�");
#endif
        return false; // ��蔭��
      }
      // �L�[���d�����Ă��邩
      if (!UseKey(key.data())) {
        // �d�����Ă���ꍇ�͊����f�[�^���폜����
        DeleteSpawnMap(key);
      }
      // �f�[�^�x�[�X��ɃX�e�[�W����o�^����
      _registry.emplace(key.data(), spawnMap);
      return true; // �o�^����
    }

    bool SpawnServer::Spawn(const int number) const {
      // �L�[���s���ȏꍇ�͐������s��Ȃ�
      if (!_registry.contains(_stage)) [[unlikely]] {
        return false; // �L�[���s���ł�
      }
      // ���W�X�g���[�ɓo�^����Ă��邩
      if (!NowSpawnMap().contains(number)) {
        return false; // �����ԍ����s��
      }
      // �I�u�W�F�N�g�𐶐�����
      return Spawn(NowSpawnMap().at(number));
    }

    bool SpawnServer::SetStage(std::string_view key) {
      // �L�[���o�^����Ă��邩
      if (!_registry.contains(key.data())) {
        return false; // �L�[�����o�^�̂��ߐ؂�ւ��Ȃ�
      }
      // ���݂̃L�[�Əd�����Ă��邩�̔���
      if (key.data() == _stage) {
#ifdef _DEBUG
        throw LogicError("�L�[���d�����Ă��܂�");
#endif
        return false; // �L�[������
      }
      // �L�[�̐؂�ւ�
      _stage = key.data();
      return true; // �ݒ芮��
    }

    const SpawnMap SpawnServer::NowSpawnMap() const {
      return _registry.at(_stage);
    }

    void SpawnServer::DeleteSpawnMap(std::string_view key) {
      // �X�e�[�W�̃X�|�[�������o��
      auto stageMap = _registry[key.data()];
      // �X�e�[�W�����폜
      stageMap.clear();
      // �f�[�^�x�[�X�ォ��폜����
      _registry.erase(key.data());
    }

    bool SpawnServer::Spawn(const SpawnTable& table) const {
      // �X�|�[��������ɃI�u�W�F�N�g�̐������s��
      for (auto num = 0; const auto spawn : table) {
        // �I�u�W�F�N�g�^�C�v����ɐ������s��
        switch (spawn.GetType()) {
          // ���@
        case SpawnData::ObjectType::Player:
          // ���@�̏ꍇ�͓o�^���s��
          AddObject(Player(spawn));
          break;
          // �I�u�W�F�N�g�^�C�v�̊Y�����Ȃ��ꍇ
        case SpawnData::ObjectType::None:
#ifdef _DEBUG
          try {
            SpawnError(num);
          } catch (std::logic_error error) {
            DebugString(error.what()); // ��O�����o�͂���
          }
#endif
          break; // �������s
        }
        ++num; // �����񐔂��J�E���g
      }
      return true;
    }

    bool SpawnServer::AddObject(std::shared_ptr<ObjectBase> object) const {
#ifndef _DEBUG
      // �I�u�W�F�N�g�T�[�o�ւ̓o�^���s��
      return _appMain.GetObjectServer().Register(std::move(object));
#else
      auto flag = false; // �����t���O
      try {
        flag = _appMain.GetObjectServer().Register(std::move(object));
        // ��O���擾�����ꍇ�̓��O�ɏo�͂���
      } catch (std::logic_error error) {
        DebugString(error.what());
      }
      return flag;
#endif
    }

    std::shared_ptr<Player::Player> SpawnServer::Player(const SpawnData& spawn) const {
      // ���@�͊��ɓo�^����Ă��Ȃ���
      if (_appMain.GetObjectServer().FindPlayer()) {
        return nullptr; // �o�^����Ă���ꍇ��nullptr��Ԃ�
      }
      // ���@�̐���
      auto player = std::make_shared<Player::Player>(_appMain);
      // �������̎��o��
      auto [position, rotation, scale] = spawn.GetTransform();
      // �������W�̐ݒ�
      player->Set(position, rotation, scale);
      // �����������@��Ԃ�
      return std::move(player);
    }

#ifdef _DEBUG
    std::logic_error SpawnServer::SpawnError(const int number) const {
      std::string message = _stage + ":" + std::to_string(number) + ":�̏�񂪗L���ł͂���܂���";
      return LogicError(message);
    }
#endif
  } // namespace Object
} // namespace Gyro
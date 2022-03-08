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
#include "EnemyWheel.h"
#include "EnemyDrone.h"
#include "SkySphere.h"
#include "StageComponent.h"

namespace Gyro {
  namespace Object {

    SpawnServer::SpawnServer(Application::ApplicationMain& app) : AppFrame::Server::ServerTemplateUnordered<std::string, SpawnMap>(), _appMain(app) {
#ifdef _DEBUG
      // �T�[�o���ݒ�
      SetServerName("SpawnServer");
#endif
      _stage.clear(); // �X�e�[�W�����폜
    }

    bool SpawnServer::Release() {
      // �e�X�e�[�W�̃X�|�[�������폜����
      for (auto&& [key, stage] : _registry) {
        stage.clear(); // �X�e�[�W�̃X�|�[�������������
      }
      _registry.clear(); // �f�[�^�x�[�X�폜
      return true;
    }

    bool SpawnServer::AddSpawnTable(std::string_view key, SpawnData spawnMap) {
      // �f�[�^���o�^����Ă��邩
      if (spawnMap.empty()) [[unlikely]] {
#ifdef _DEBUG
        throw LogicError("�X�|�[����񂪋�ł�");
#endif
        return false; // ��蔭��
      }
      // �L�[���d�����Ă��邩
      if (Contains(key.data())) {
        // �d�����Ă���ꍇ�͊����f�[�^���폜����
        Delete(key);
      }
      // �X�|�[�����p�̘A�z�z��
      SpawnMap map;
      // �X�|�[�������Ǘ����铮�I�z��
      std::vector<std::shared_ptr<SpawnBase>> table;
      // �X�|�[�������V�F�A�[�h�|�C���^�ɕϊ����ēo�^���s��
      for (auto&& [number, spawn] : spawnMap) {
        // �����e�[�u���̎擾
        auto [normal, enemy] = spawn;
        // �ʏ�̃X�|�[������ϊ�
        for (auto&& value : normal) {
          table.emplace_back(std::make_shared<SpawnBase>(value));
        }
        // �G�̃X�|�[������ϊ�
        for (auto&& value : enemy) {
          table.emplace_back(std::make_shared<SpawnEnemy>(value));
        }
        // �ϊ������e�[�u�����R���e�i�ɓo�^
        map.emplace(number, table);
      }
      // �f�[�^�x�[�X�ɏ���o�^����
      _registry.emplace(key.data(), map);
      return true; // �o�^����
    }

    bool SpawnServer::Spawn(const int number) {
      // �L�[���s���ȏꍇ�͐������s��Ȃ�
      if (!_registry.contains(_stage)) [[unlikely]] {
        return false; // �L�[���s���ł�
      }
      // ���W�X�g���[�ɓo�^����Ă��邩
      if (!NowSpawnMap().contains(number)) {
        return false; // �����ԍ����s��
      }
      // �I�u�W�F�N�g�𐶐�����
      return SpawnObject(number);
    }

    bool SpawnServer::SetStage(std::string_view key) {
      // �L�[�͓o�^����Ă��邩
      if (!_registry.contains(key.data())) {
        return false; // �L�[�����o�^�̂��ߐ؂�ւ��Ȃ�
      }
      // ���݂̃L�[�Əd�����Ă��邩�̔���
      if (key.data() == _stage) {
        return false; // �L�[���d�����Ă���
      }
      // �L�[�̐؂�ւ�
      _stage = key.data();
      return true; // �ݒ芮��
    }

    SpawnMap& SpawnServer::NowSpawnMap() {
      // �X�e�[�W�ɑΉ������X�|�[����񂪊i�[���ꂽ�X�e�[�W����Ԃ�
      return _registry.at(_stage);
    }

    void SpawnServer::Delete(std::string_view key) {
      // �X�e�[�W�̃X�|�[�������o��
      auto stageMap = _registry[key.data()];
      // �X�e�[�W�����폜
      stageMap.clear();
      // �f�[�^�x�[�X�ォ��폜����
      _registry.erase(key.data());
    }

    bool SpawnServer::SpawnObject(const int number) {
      // �X�|�[��������ɃI�u�W�F�N�g�̐������s��
      for (auto num = 0; auto spawn : NowSpawnMap().at(number)) {
        // �I�u�W�F�N�g�^�C�v����ɐ������s��
        switch (spawn->GetType()) {
          // ���@
        case SpawnBase::ObjectType::Player:
          // ���@�̐����E�o�^
          AddObject(Player(spawn));
          break;
          // �G
        case SpawnBase::ObjectType::Enemy:
          // �G�̐����E�o�^���s��
          AddObject(Enemy(spawn));
          break;
          // �X�J�C�X�t�B�A
        case SpawnBase::ObjectType::SkySphere:
          // �X�J�C�X�t�B�A�̐����E�o�^���s��
          AddSkySphere(Skysphere(spawn));
          break;
          // �I�u�W�F�N�g�^�C�v�̊Y�����Ȃ��ꍇ
        case SpawnBase::ObjectType::None:
#ifdef _DEBUG
          try {
            // �X�|�[�����s�p�̃��b�Z�[�W���o��
            SpawnError(num);
          } catch (std::logic_error error) {
            DebugString(error.what());
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

    void SpawnServer::AddSkySphere(std::shared_ptr<SkySphere> skysphere) {
      // �X�e�[�W�ɓo�^����
      auto skySkysphere = skysphere;
      return _appMain.GetStageComponent().AddSky(skySkysphere);
    }

    std::shared_ptr<Player::Player> SpawnServer::Player(std::shared_ptr<SpawnBase>& spawn) const {
      // ���@�͊��ɓo�^����Ă��Ȃ���
      if (_appMain.GetObjectServer().FindPlayer()) {
        return nullptr; // �o�^����Ă���ꍇ��nullptr��Ԃ�
      }
      // ���@�̐���
      auto player = std::make_shared<Player::Player>(_appMain);
      player->Set(*spawn.get());       // �X�|�[�����̐ݒ�
      return std::move(player); // ���������V�F�A�[�h�|�C���^��Ԃ�
    }

    std::shared_ptr<ObjectBase> SpawnServer::Enemy(std::shared_ptr<SpawnBase>& spawn) const {
      // �G�l�~�[�^�C�v�̎擾
      auto enemy = std::dynamic_pointer_cast<SpawnEnemy>(spawn);
      // �G�l�~�[�^�C�v�ɉ������V�F�A�[�h�|�C���^�𐶐����ĕԂ�
      switch (enemy->GetEnemyType()) {
      case SpawnEnemy::EnemyType::Wheel: // ����^
        return EnemyWheel(*enemy.get());
      case SpawnEnemy::EnemyType::Drone: // �󒆌^
        return EnemyDrone(*enemy.get());
      case SpawnEnemy::EnemyType::None:  // �Y���Ȃ�
        return nullptr;  // �Y�����Ȃ��ꍇ��nullptr��Ԃ�
      default:
        return nullptr;  // �ݒ肳��Ă��Ȃ��ꍇ��nullptr��Ԃ�
      }
    }

    std::shared_ptr<Enemy::EnemyWheel> SpawnServer::EnemyWheel(SpawnEnemy& enemy) const {
      // ����^�G�l�~�[�̐���
      auto wheel = std::make_shared<Enemy::EnemyWheel>(_appMain);
      wheel->Set(enemy);       // �X�|�[�����̐ݒ�
      return std::move(wheel); // ���������V�F�A�[�h�|�C���^��Ԃ�
    }

    std::shared_ptr<Enemy::EnemyDrone> SpawnServer::EnemyDrone(SpawnEnemy& enemy) const {
      // �󒆌^�G�l�~�[�̐���
      auto drone = std::make_shared<Enemy::EnemyDrone>(_appMain);
      drone->Set(enemy);       // �X�|�[�����̐ݒ�
      return std::move(drone); // ���������V�F�A�[�h�|�C���^��Ԃ�
    }

    std::shared_ptr<SkySphere> SpawnServer::Skysphere(std::shared_ptr<SpawnBase>& spawn) const {
      // ���@�͓o�^����Ă��邩
      if (!_appMain.GetObjectServer().FindPlayer()) {
        return nullptr; // ���o�^
      }
      // �X�J�C�X�t�B�A�̐���
      auto skySphere = std::make_shared<SkySphere>(_appMain, *_appMain.GetObjectServer().GetPlayer());
      skySphere->SetKey("sky");
      skySphere->Set(*spawn);
      return std::move(skySphere);
    }

#ifdef _DEBUG
    std::logic_error SpawnServer::SpawnError(const int number) const {
      std::string message = _stage + ":" + std::to_string(number) + ":�̏�񂪗L���ł͂���܂���";
      return LogicError(message);
    }
#endif
  } // namespace Object
} // namespace Gyro

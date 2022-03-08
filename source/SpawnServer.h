/*****************************************************************//**
 * @file   SpawnServer.h
 * @brief  �I�u�W�F�N�g�̃X�|�[�������Ǘ�����T�[�o�N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <appframe.h>
#include "SpawnBase.h"
#include "SpawnEnemy.h"
#include "StageComponent.h"
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �v���C���[�x�[�X
   */
  namespace Player {
    class Player; //!< �v���C���[
  } // namespace Player
  /**
   * @brief �G�l�~�[�x�[�X
   */
  namespace Enemy {
    class EnemyWheel; //!< �O���錾
    class EnemyDrone; //!< �O���錾
  } // namespace 
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    class ApplicationMain; //!< �O���錾
  } // namespace Application
  namespace Stage {
    class StageComponent;
  }
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    class ObjectBase; //!< �O���錾
    class SkySphere;  //!< �X�J�C�X�t�B�A
    /**
     * @brief �X�|�[�������i�[���铮�I�z��̕ʖ�
     */
    using SpawnTable = std::vector<SpawnBase>;
    /**
     * @brief �G�l�~�[�̃X�|�[�������i�[���铮�I�z��̕ʖ�
     */
    using EnemyTable = std::vector<SpawnEnemy>;
    /**
     * @brief �o�^���Ɏg�p����e��X�|�[�����𐔒l�ŊǗ�����A�z�z��
     *        0:�X�|�[���e�[�u�� 1:�G�l�~�[�e�[�u��
     */
    using SpawnData = std::unordered_map<int, std::tuple<SpawnTable, EnemyTable>>;
    /**
     * @brief �ԍ����L�[�Ƃ��ăX�|�[�����̃V�F�A�[�h�|�C���^���Ǘ�����A�z�z��̕ʖ�
     */
    using SpawnMap = std::unordered_map<int, std::vector<std::shared_ptr<SpawnBase>>>;
    /**
     * @class SpawnServer
     * @brief �X�e�[�W�����L�[�Ƃ��ăX�|�[�������Ǘ�����T�[�o�N���X
     */
    class SpawnServer : public AppFrame::Server::ServerTemplateUnordered<std::string, SpawnMap> {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�������C���̎Q��
       */
      SpawnServer(Application::ApplicationMain& app);
      /**
       * @brief  �������
       * @return true
       */
      bool Release() override;
      /**
       * @brief  �X�|�[�����̓o�^
       * @param  key �X�|�[�����ɕR�Â��镶����(�X�e�[�W��)
       * @param  spawnMap �X�|�[�����̃C���X�^���X���o�^���ꂽ�A�z�z��
       * @return true:�o�^���� false:��蔭��
       */
      bool AddSpawnTable(std::string_view key, SpawnData spawnMap);
      /**
       * @brief  �I�u�W�F�N�g�̐�������
       * @param  number �����ԍ�
       * @return true:�������� false:�������s
       */
      bool Spawn(const int number);
      /**
       * @brief  �X�e�[�W�L�[�̐ݒ�
       * @param  key �X�e�[�W�L�[
       * @return true:�؂�ւ����� false:�؂�ւ����s
       */
      bool SetStage(std::string_view key);
    private:
      Application::ApplicationMain& _appMain; //!< �A�v���P�[�V�����̎Q��
      std::string _stage; //!< �X�e�[�W�L�[
      //!< �G�l�~�[�̃e�[�u�������Ǘ�����A�z�z��
      std::unordered_map<std::string, std::unordered_map<int, EnemyTable>> _enemyTable;
      /**
       * @brief  ���݂̃X�e�[�W�ɑΉ�����R���e�i�̎擾
       * @return �X�e�[�W�ɕR�Â���ꂽ�X�|�[�����
       */
      SpawnMap& NowSpawnMap();
      /**
       * @brief �w�肵���X�|�[�������폜����
       * @param key �X�e�[�W�L�[
       */
      void Delete(std::string_view key);
      /**
       * @brief  �I�u�W�F�N�g�̐�������
       * @param  spawn �X�|�[�����̎Q��
       * @return true:�������� false:�������s
       */
      bool SpawnObject(const int numebr);
      /**
       * @brief  �I�u�W�F�N�g�T�[�o�ɐ��������I�u�W�F�N�g��o�^����
       * @param  object �I�u�W�F�N�g�̃V�F�A�[�h�|�C���^
       * @return true:�o�^���� false:�o�^���s
       */
      bool AddObject(std::shared_ptr<ObjectBase> object) const;
      /**
       * @brief
       * @param  skysphere
       * @return 
       */
      void AddSkySphere(std::shared_ptr<SkySphere> skysphere);
      /**
       * @brief  ���@�̐���
       * @param  spawn �X�|�[�����
       * @return ���@�̃V�F�A�[�h�|�C���^
       *         ���@�����ɓo�^����Ă���ꍇ��nullptr��Ԃ�
       */
      std::shared_ptr<Player::Player> Player(std::shared_ptr<SpawnBase>& spawn) const;
      /**
       * @brief  �G�l�~�[�̐���
       * @param  spawn �X�|�[�����
       * @return �G�l�~�[�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<ObjectBase> Enemy(std::shared_ptr<SpawnBase>& spawn) const;
      /**
       * @brief  ����^�G�̐���
       * @param  spawn �X�|�[�����
       * @return ����^�G�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<Enemy::EnemyWheel> EnemyWheel(SpawnEnemy& spawn) const;
      /**
       * @brief  �󒆌^�G�̐���
       * @param  spawn �X�|�[�����
       * @return �󒆌^�G�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<Enemy::EnemyDrone> EnemyDrone(SpawnEnemy& spawn) const;
      /**
       * @brief  �X�J�C�X�t�B�A�̐���
       * @param  spawn �X�|�[�����
       * @return �X�J�C�X�t�B�A�̃V�F�A�[�h�|�C���^
       */
      std::shared_ptr<SkySphere> Skysphere(std::shared_ptr<SpawnBase>& spawn) const;
#ifdef _DEBUG
      /**
       * @brief  �X�|�[�����s���b�Z�[�W�̐���
       * @param  number ������
       */
      std::logic_error SpawnError(const int number) const;
#endif
    };
  } // namespace Object
} // namespace Gyro
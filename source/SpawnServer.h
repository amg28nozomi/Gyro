/*****************************************************************//**
 * @file   SpawnServer.h
 * @brief  �I�u�W�F�N�g�̃X�|�[�������Ǘ�����T�[�o�N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <appframe.h>
#include "SpawnData.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    class ApplicationMain; //!< �O���錾
  } // namespace Application
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    class ObjectBase; //!< �O���錾
    /**
     * @brief �X�|�[�������i�[�������I�z��̕ʖ�
     */
    using SpawnTable = std::vector<SpawnData>;
    /**
     * @brief �ԍ����L�[�Ƃ��ăX�|�[�������Ǘ�����A�z�z��
     */
    using SpawnMap = std::unordered_map<int, SpawnTable>;
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
       * @param  spawnMap �X�|�[����񂪊i�[���ꂽ�A�z�z��
       * @return true:�o�^���� false:��蔭��
       */
      bool AddSpawnTable(std::string_view key, const SpawnMap& spawnMap);
      /**
       * @brief  �I�u�W�F�N�g�̐�������
       * @param  number �����ԍ�
       * @return true:�������� false:�������s
       */
      bool Spawn(const int number) const;
      /**
       * @brief  �X�e�[�W�L�[�̐ݒ�
       * @param  key �X�e�[�W�L�[
       * @return true:�؂�ւ����� false:�؂�ւ����s
       */
      bool SetStage(std::string_view key);
    private:
      Application::ApplicationMain& _appMain; //!< �A�v���P�[�V�����̎Q��
      std::string _stage; //!< �X�e�[�W�L�[
      /**
       * @brief  ���݂̃X�e�[�W�ɑΉ�����R���e�i�̎擾
       * @return �X�e�[�W�ɕR�Â���ꂽ�X�|�[�����
       */
      const SpawnMap NowSpawnMap() const;
      /**
       * @brief �w�肵���X�e�[�W�����폜����
       * @param key �X�e�[�W�L�[
       */
      void DeleteSpawnMap(std::string_view key);
      /**
       * @brief  �I�u�W�F�N�g�̐�������
       * @param  spawn �X�|�[�����
       * @return true:�������� false:�������s
       */
      bool Spawn(const SpawnTable& table) const;
      /**
       * @brief  �I�u�W�F�N�g�T�[�o�ɐ��������I�u�W�F�N�g��o�^����
       * @param  object �I�u�W�F�N�g�̃V�F�A�[�h�|�C���^
       * @return true:�o�^���� false:�o�^���s
       */
      bool AddObject(std::shared_ptr<ObjectBase> object) const;
      /**
       * @brief  ���@�̐���
       * @param  spawn �X�|�[�����
       * @return ���@�̃V�F�A�[�h�|�C���^
       *         ���@�����ɓo�^����Ă���ꍇ��nullptr��Ԃ�
       */
      std::shared_ptr<Player::Player> Player(const SpawnData& spawn) const;
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
/*****************************************************************//**
 * @file   ModeServer.h
 * @brief  �e�탂�[�h���Ǘ�����T�[�o�N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "../Server/ServerTemplateUnordered.h"
#include <memory>
#include <list>

/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    class ApplicationBase; //!< �O���錾
  } // namespace Application
  /**
   * @brief ���[�h�x�[�X
   */
  namespace Mode {
    class ModeBase; //!< �O���錾
    /**
     * @class ModeServer
     * @brief ���[�h�̊Ǘ����s���T�[�o
     */
    class ModeServer : public Server::ServerTemplateUnordered<std::string, std::shared_ptr<ModeBase>> {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      ModeServer(Application::ApplicationBase& app);
      /**
       * @brief  �R���X�g���N�^
       * @param  key  �o�^�Ɏg�p���镶����
       * @param  mode �ŏ��ɓo�^����V�[���̃|�C���^
       */
      ModeServer(std::string_view key, std::shared_ptr<ModeBase> mode);
      /**
       * @brief  ���[�h�̉��
       * @return true:�J������ false:������s
       */
      bool Release() override;
      /**
       * @brief  �f�[�^�x�[�X�Ƀ��[�h��o�^����
       * @param  key �o�^�Ɏg�p���镶����
       * @param  mode �o�^���郂�[�h�̃V�F�A�[�h�|�C���^
       */
      void AddMode(std::string_view key, std::shared_ptr<ModeBase> mode);
      /**
       * @brief  �w�肵�����[�h�����X�g�̖����ɒǉ�����
       * @param  key �Ώۃ��[�h�ɕR�Â���ꂽ������
       * @return true:�ǉ����� false:�ǉ����s
       */
      bool PushBack(std::string_view key);
      /**
       * @brief  ���X�g�̖����ɓo�^����Ă��郂�[�h���폜����
       */
      void PopBuck();
      /**
       * @brief  ���[�h�̑J�ڏ���
       * @param  key �Ώۃ��[�h�ɕR�Â���ꂽ������
       * @return true
       */
      bool TransionToMode(std::string_view key);
      /**
       * @brief  ���[�h�̍X�V
       * @return true:����I�� false:��蔭��
       */
      bool Process();
      /**
       * @brief  ���[�h�̕`��
       * @return true:�`�搬�� false:��蔭��
       */
      bool Draw() const;
    private:
      //!< ���[�h���X�g
      std::list<std::shared_ptr<ModeBase>> _modes;
      /**
       * @brief  ���[�h�̓o�^
       * @param  key  ���[�h�ɕR�Â��镶����
       * @param  mode �o�^���郂�[�h
       * @return true
       */
      bool Register(std::string key, std::shared_ptr<ModeBase> mode) override;
      /**
       * @brief  �f�[�^�x�[�X����w�肵�����[�h���擾����
       * @param  key �Ώۃ��[�h�ɕR�Â���ꂽ������
       * @return �w�肵�����[�h��Ԃ�
       *         �L�[���L���ł͂Ȃ��ꍇ�Anullptr��Ԃ�
       */
      std::shared_ptr<ModeBase> FetchMode(std::string_view key);
      /**
       * @brief  ���X�g�̖����̗v�f�̒��O�Ɏw�肵�����[�h��ǉ�����
       * @param  key �Ώۃ��[�h�ɕR�Â���ꂽ������
       * @return true:�ǉ����� false:�ǉ����s
       */
      bool InsertBeforeBack(std::string_view key);
    };
  } // namespace Mode
} // namespace AppFrame
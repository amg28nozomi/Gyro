#pragma once
#include <appframe.h>

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    class ApplicationMain;
  } // namespace Application
  /**
   * @brief ���f���x�[�X
   */
  namespace Model {
    /**
     * @brief ���O��Ԃ̕ʖ���`
     */
    namespace AppServer = AppFrame::Server;
    /**
     * @class ModelServer
     * @brief ���f���f�[�^�ƃA�j���[�V�������Ǘ�����T�[�o�N���X
     */
    class ModelServer : public AppServer::ServerTemplateUnordered<std::string, std::vector<int>> {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�������C���̎Q��
       */
      ModelServer(Application::ApplicationMain& app);
      /**
       * @brief  ���\�[�X�̉������
       * @return 
       */
      bool Release() override;
      /**
       * @brief  ���f���t�@�C�����i�[����Ă���f�B���N�g���p�X�̐ݒ�
       * @param  directry �f�B���N�g���p�X
       * @return true:�ݒ芮�� false:���s
       */
      bool SetDirectryPath(std::string_view directry);
      /**
       * @brief  ���f���n���h���̓ǂݎ��
       * @param  filePath �Ώۃ��f���̃t�@�C���p�X
       * @return true:�ǂݎ�萬�� false:�ǂݎ�莸�s
       */
      bool LoadModel(std::string_view fileName);
      /**
       * @brief  �w�肵�����f���n���h���̎擾
       * @param  key ���f�����ɕR�Â���ꂽ������
       * @param  no ���f���ԍ�
       * @return key���L���ȏꍇ�̓��f���n���h����Ԃ�
       *         �L���ł͂Ȃ��ꍇ��-1��Ԃ�
       */
      const int GetModelHandle(std::string_view key, const int no);
    private:
      Application::ApplicationMain& _app; //!< �A�v���P�[�V�������C���̎Q��
      //!< ���[�V�����f�[�^���t�@�C����(������)�ŊǗ�����A�z�z��
      std::unordered_map<std::string, int> _animations{};
      std::filesystem::path _directry{}; //!< �f�B���N�g���p�X
      /**
       * @brief  �p�X���L�����̔���
       * @param  path ����p�X
       * @return true:�L�� false:�L���ł͂Ȃ�
       */
      bool PathExist(std::filesystem::path path);
      /**
       * @brief ���f���n���h���̍폜���s��
       * @param handles ���f���n���h�����i�[���ꂽ�R���e�i�̎Q��
       */
      void DeleteHandles(std::vector<int>& handles);
      /**
       * @brief  Mv1���f���̓ǂݎ��
       * @param  path �t�@�C����
       * @return ���f���n���h��
       *         �ǂݎ��Ɏ��s�����ꍇ��-1��Ԃ�
       */
      int MV1LoadModel(std::filesystem::path path) const;
    };
  } // namespace Model
} // namespace Gyro
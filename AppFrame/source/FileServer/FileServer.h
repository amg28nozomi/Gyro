/*****************************************************************//**
 * @file   FileServer.h
 * @brief  �t�@�C���f�[�^���Ǘ�����T�[�o�N���X
 *
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "../Server/ServerTemplateUnordered.h"
#include <filesystem>
#include "FileOutput.h"
#include "FileBase.h"

/** FileWorker�p���O��� */
namespace AppFrame {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    class ApplicationBase; //!< �A�v���P�[�V����
  } // namespace Application
  /**
   * @brief �t�@�C���T�[�o
   */
  namespace FileServer {
    class LoadJson; //!< �O���錾
    /**
     * @class FileServer
     * @brief �t�@�C���Ǘ��p�T�[�o
     */
    class FileServer : public Server::ServerTemplateUnordered<std::string, std::filesystem::path> {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      FileServer(Application::ApplicationBase& app);
      /**
       * @brief  ������
       * @return true:���������� false:���������s
       */
      bool Init() override;
      /**
       * @brief  json�t�@�C���̓ǂݎ��
       * @param  jsonFile json�t�@�C���̃p�X
       * @return true:�ǂݎ����s false:��蔭��
       */
      bool LoadJsonFile(std::string_view jsonFile) const;
      /**
       * @brief  �Ώۃt�@�C���`���̎w��(Instance��A��x�̂ݐݒ�\)
       * @param  extensions �t�@�C���g���q(������)���i�[�������I�z��
       */
      bool SetExtension(std::vector<std::string> extensions);
    protected:
      std::unique_ptr<LoadJson> _loadJson;  //!< json�t�@�C���̓ǂݎ��
      std::vector<std::string> _extensions; //!< �Ή��t�@�C���`��
      bool _setExtension{false}; //!< �Ώۃt�@�C���`�����w�肵�����̔���
      /**
       * @brief  �Ώۃt�@�C�����o�^�Ώۂ��̔���
       * @param  filePath �Ώۃt�@�C���̃p�X
       * @param  extension �o�^�\�ȃt�@�C���`��
       * @return true:�o�^�Ώ� false:��o�^�Ώ�
       */
      bool IsTarget(std::filesystem::path filePath, std::string_view extension = "") const;
      /**
       * @brief  �t�@�C���`������v���Ă��邩�̔���
       * @param  filePath �Ώۃt�@�C���̃p�X
       * @return true:��v false:�Ώۂł͂Ȃ�
       */
      bool HasExtension(std::filesystem::path filePath, std::string_view extension = "") const;
      /**
       * @brief  �Ώۃp�X�����݂��邩�̔���
       * @param  filePath �Ώۃt�@�C���̃p�X
       * @return true:�L�� false:�p�X���s��
       */
      bool Exist(std::filesystem::path filePath) const;
    };

//    class FileServer : public Data::ServerBase < FileBase, std::filesystem::path > {
//    public:
//#ifndef _DEBUG
//      /**
//       * @brief �R���X�g���N�^
//       */
//      FileServer();
//#else
//      /**
//       * @brief �R���X�g���N�^
//       * @param filePath ���O�o�͗p�t�@�C���̃p�X(�f�t�H���g�ł͋�)
//       */
//      FileServer(std::filesystem::path filePath = "");
//#endif
//      /**
//       * @brief �f�X�g���N�^
//       */
//      ~FileServer() override;
//      /**
//       * @brief  ������
//       */
//      bool Init() override;
//      /**
//       * @brief  ���W�X�g���̏�����
//       * @return 
//       */
//      bool Release() override;
//      /**
//       * @brief  �t�@�C�����̓o�^
//       * @param  key  �o�^�Ɏg�p���镶����
//       * @param  path �t�@�C���̃p�X
//       * @return true:�o�^���� false:�o�^���s
//       */
//      bool Register(std::string_view key, const std::filesystem::path path) override;
//      /**
//       * @brief  �t�@�C�����̓ǂݎ��
//       * @param  jsonPath json�t�@�C���̃|�X
//       * @return true:�ǂݎ�萬�� false:��蔭��
//       */
//      bool LoadFiles(std::filesystem::path jsonPath);
//    protected:
//#ifdef _DEBUG
//      class FileOutput _fileLog; //!< �t�@�C���o�̓V�X�e��
//      bool _debug{false};        //!< ���O�o�̓t���O
//#endif
//    };

    /**
     * @class FileServer
     * @brief �t�@�C���f�[�^���Ǘ�����T�[�o
     */
//    class FileServer {
//    private:
//      /** ��������L�[�Ƃ��ăt�@�C���f�[�^���Ǘ�����A�z�z�� */
//      using FileBaseMap = std::unordered_map<std::string, FileBase>;
//    public:
//      /**
//       * @brief  �t�@�C���T�[�o�̐���
//       */
//      FileServer();
//      /**
//       * @brief  �t�@�C���T�[�o�̔j��
//       */
//      ~FileServer();
//      /**
//       * @brief  �T�[�o�̏���������
//       * @return �������t���O
//       */
//      bool Init();
//      /**
//       * @brief  �f�[�^�̉������
//       */
//      void Release();
//      /**
//       * @brief  �t�@�C�����̓ǂݎ�菈��
//       * @param  jsonPath �ǂݎ��Json�t�@�C���̃p�X
//       * @return �ǂݎ�菈���ɐ��������ꍇ��true��Ԃ�
//       */
//      bool LoadFileMap(std::filesystem::path jsonPath);
//      /**
//       * @brief  ���O�o�̓t���O�̐ݒ�
//       * @param  flag �o�̓t���O
//       * @param  logPath ���O�t�@�C�����o�͂���f�B���N�g���p�X
//       * @return �ݒ�ɐ��������ꍇ��true
//       *         ���s�����ꍇ��false��Ԃ�
//       */
//      bool SetLogTextFlag(bool flag, std::filesystem::path logPath);
//    private:
//      FileBaseMap _fileMap; //!< �t�@�C�������Ǘ�����R���e�i
//      FileOutput _debugLog; //!< �f�o�b�O�p�t�@�C���o�̓V�X�e��
//      bool _debug;          //!< �f�o�b�O�o�͗p�t���O
//      /**
//       * @brief  �t�@�C�����̓o�^����
//       * @param  fileMap �o�^���s���t�@�C�����
//       * @return �o�^����������I�������ꍇ��true
//       *         ���s�����ꍇ��false��Ԃ�
//       */
//      bool LoadFileMap(FileBaseMap& fileMap);
//      /**
//       * @brief      ���ʎq�̔�����s��
//       * @param path ����t�@�C��
//       * @return
//       */
//      bool FileCheck(const std::filesystem::path path);
//#ifdef _DEBUG
//      /**
//       * @brief  ���O�o��
//       * @param  text �o�͂��镶����
//       */
//      void DebugStringLog(const std::string text);
//#endif
//    };
  } // namespace FileServer
} // namespace AppFrame
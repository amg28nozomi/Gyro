/*****************************************************************//**
 * @file   LoadJson.h
 * @brief  json�t�@�C���̓ǂݎ�菈���N���X
 *
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <unordered_map>
#include <vector>
#include <filesystem>
#ifdef _DEBUG
#include <stdexcept>
#endif
#include <nlohmann/json.hpp>
#include "../Data/DivGraph.h"

/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    class ApplicationBase;
  }
  /**
   * @brief �t�@�C���T�[�o
   */
  namespace FileServer {
    constexpr auto JSON = ".json"; //!< json�t�@�C���̃t�H�[�}�b�g
    /**
     * @class LoadJson
     * @brief json�t�@�C���̓ǂݎ����s���ÓI�N���X
     */
    class LoadJson {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      LoadJson(Application::ApplicationBase& app);
      /**
       * @brief  json�t�@�C���̓ǂݎ�菈��
       * @param  path json�t�@�C���̃p�X
       * @return true:�ǂݎ�萬�� false:�ǂݎ�莸�s
       */
      bool LoadJsonFile(std::string_view path);
      /**
       * @brief  json�t�@�C���̓ǂݎ�菈��(DivGraph�p)
       * @param  jsonPath
       * @return DivGraph�p�̃f�[�^���i�[���ꂽ���I�z��
       *         first:�A�z�z��̓o�^�Ɏg�p����L�[ pair:�摜�t�@�C�����
       */
      //static std::vector<std::pair<std::string_view,
      //  std::filesystem::path>> LoadDivGraoh(std::filesystem::path jsonPath);
      /**
       * @brief  json�t�@�C���̓ǂݎ�菈��
       * @param  jsonPath json�t�@�C���̃p�X
       * @return �擾�����t�@�C���f�[�^��Ԃ�
       * @throw  std::logic_error
       */
      //static std::vector<std::pair<std::string, Data::DivGraph>> LoadJsonFile(std::filesystem::path jsonPath);
      /**
       * @brief  �Ώۃt�@�C����json�t�@�C�����𔻒肷��
       * @param  path ����t�@�C���̃p�X
       * @return json�t�@�C���̏ꍇ��true
       *         �����ł͂Ȃ��ꍇ��false��Ԃ�
       */
      static bool IsJson(const std::filesystem::path path);
    private:
      Application::ApplicationBase& _app; //!< �A�v���P�[�V�����̎Q��
      /**
       * @brief  ���f�����̓ǂݎ�菈��
       * @param  json ���f����񂪊i�[���ꂽjson�I�u�W�F�N�g
       * @return true:�ǂݎ�萬�� false:��蔭��
       */
      bool LoadModelData(const nlohmann::json json);
      /**
       * @brief  LoadDivGraph���̓ǂݎ��
       * @param  json �摜��񂪊i�[���ꂽjson�I�u�W�F�N�g
       * @return 
       */
      bool LoadDivGraphData(const nlohmann::json json);
      /**
       * @brief  Json�t�@�C���p�X�ւ̕ϊ�
       * @param  directory �f�B���N�g���p�X
       * @param  fileName  json�t�@�C����
       * @return json�t�@�C���̃p�X
       */
      std::filesystem::path ToJsonName(std::string directory, std::string fileName) const;
      /**
       * @brief  json�t�@�C���̓ǂݎ��
       * @param  jsonFile �Ώۃt�@�C���̃p�X
       * @return �ǂݎ��ɐ��������ꍇ�͑Ώۂ�json�I�u�W�F�N�g��Ԃ�
       *         �ǂݎ��Ɏ��s�����ꍇ�͋�̃I�u�W�F�N�g��Ԃ�
       */
      //static nlohmann::json LoadJsonFile(std::filesystem::path jsonFile);
#ifdef _DEBUG
      /**
       * @brief  �G���[���b�Z�[�W�̎擾
       * @param  left  ���Ӓl
       * @param  right �E�Ӓl
       * @return �����ɉ������G���[���b�Z�[�W��Ԃ�
       * @throw  std::logic_error
       */
      std::string_view Differebce(const int key, const int path) noexcept;
      /**
       * @brief  std::logic_error�̎擾
       * @param  message �G���[�Ɏ������镶����
       * @return �ݒ肵��logic_error��Ԃ�
       */
      static std::logic_error GetLogicError(std::string message);
#endif
    };
  } // namespace FileServer
} // namespace AppFrame
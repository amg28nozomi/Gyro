/*****************************************************************//**
 * @file   ResourceServer.h
 * @brief  2D�f�ނ��Ǘ����郊�\�[�X�T�[�o�N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "../Server/ServerTemplateUnordered.h"
#include <filesystem>
#include "../Data/DivGraph.h"

/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief ���\�[�X�x�[�X
   */
  namespace Resource {
    /**
     * @class  ResourceServer
     * @brief  ��������L�[�Ƃ��ĉ摜���ƃO���t�B�b�N�n���h�����Ǘ�����T�[�o
     *         Key �摜���ɕR�Â��镶����
     *         Value first:�摜��� second:�O���t�B�b�N�n���h�����i�[����R���e�i
     */
    class ResourceServer : Server::ServerTemplateUnordered<std::string, std::pair<Data::DivGraph, std::vector<int>>> {
    public:
      /**
       * @brief 
       * @param first:�R�Â��镶����
       * @param second:�摜���
       */
      using DivGraphTable = std::pair<std::string, Data::DivGraph>;
      /**
       * @brief �R���X�g���N�^
       * @param path �f�B���N�g���p�X
       */
      ResourceServer(std::string_view path = "");
      /**
       * @brief  �O���t�B�b�N���̉��
       * @return 
       */
      bool Release() override;
      /**
       * @brief  �摜�̓ǂݎ��
       * @param  �O���t�B�b�N�n���h���ɕR�Â��镶����
       * @param  divGraph �摜���
       * @return true:�o�^���� false:�o�^���s
       */
      bool LoadDivGraph(std::string_view key, Data::DivGraph divGraph);
      /**
       * @brief  �w�肵���摜���̎擾
       * @param  key �Ώۏ��ɕR�Â���ꂽ������
       * @return first:�摜��� second:�O���t�B�b�N�n���h�����i�[���ꂽ�R���e�i
       */
      Data::DivGraph GetDivGraph(std::string_view key) const;
      /**
       * @brief  �w�肵���O���t�B�b�N�n���h���̎擾
       * @param  key �ΏۂɕR�Â���ꂽ������
       * @param  no  �Ώۂ̃n���h���ԍ�
       * @return �擾�ɐ��������ꍇ�̓O���t�B�b�N�n���h����Ԃ�
       *         ���s�����ꍇ��-1��Ԃ�
       */
      const int GetHandle(std::string_view key ,const int no = 0) const;
      /**
       * @brief  �f�B���N�g���p�X�̐ݒ�(���o�^�̏ꍇ�̂ݓo�^�\)
       * @param  path �f�B���N�g���p�X
       * @return true:�ݒ萬�� false:���s
       */
      bool SetDirectryPath(std::filesystem::path path);
    private:
      std::filesystem::path _directory{}; //!< �f�B���N�g���p�X
      /**
       * @brief  �t�@�C���p�X�̌���
       * @param  filePath �Ώۂ̃t�@�C����
       * @return �t�@�C���p�X
       */
      inline std::filesystem::path FilePath(std::filesystem::path filePath) const {
        return (_directory / filePath);
      }
      /**
       * @brief  �O���t�B�b�N�n���h���̍폜
       * @param  handles �O���t�B�b�N�n���h�����i�[���ꂽ�R���e�i
       */
      void DeleteGraphs(std::vector<int> handles) const;
    };
  } // namespace Resource
} // namespace AppFrame
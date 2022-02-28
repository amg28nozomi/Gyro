/*****************************************************************//**
 * @file   WriteJson.h
 * @brief  json�t�@�C���̏������ݏ����N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <filesystem>

/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �t�@�C���T�[�o
   */
  namespace FileServer {
    /**
     * @class WriteJson
     * @brief json�t�@�C���̏������ݏ����N���X
     */
    class WriteJson {
    public:
    private:
      static std::filesystem::path _path; //!< �������s���f�B���N�g��
      /**
       * @brief  json�t�@�C���̐���
       * @param  jsonName json�t�@�C���̖��O
       * @return ��������json�t�@�C���̃p�X
       * @throw  logic_error
       */
      static std::filesystem::path AddJson(std::filesystem::path jsonName);
      /**
       * @brief  json�t�@�C���̃Z�[�u
       * @param  path
       * @return 
       */
      static bool Save(std::string_view path);
    };
  } // namespace FileServer
} // namespace AppFrame
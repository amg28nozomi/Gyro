/*****************************************************************//**
 * @file   FileBase.h
 * @brief  �t�@�C���f�[�^��ێ�����X�[�p�[�N���X
 *
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <filesystem>

/** FileWorker�p���O��� */
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �t�@�C���T�[�o
   */
  namespace FileServer {
    /**
     * @class FileBase
     * @brief �t�@�C���f�[�^
     */
    class FileBase {
    public:
      /**
       * @brief ��f�[�^�𐶐�
       */
      FileBase();
      /**
       * @brief �t�@�C���f�[�^�̐���(�L�[��񖳂�)
       * @param filePath �t�@�C���̃p�X
       */
      FileBase(std::filesystem::path filePath);
      /**
       * @brief �t�@�C���f�[�^�̐���(�L�[���L��)
       * @param filrPath 
       * @param key
       */
      FileBase(std::filesystem::path filrPath, std::string_view key);
      /**
       * @brief �t�@�C���f�[�^�̔j��
       */
      ~FileBase();
      /**
       * @brief �t�@�C���f�[�^�̃��Z�b�g
       */
      void Clear();
      /**
       * @brief  �p�X�̎擾
       * @return �t�@�C���p�X��Ԃ�
       */
      inline std::filesystem::path GetFilePath() const {
        return _path;
      }
      /**
       * @brief  �t�@�C�����̎擾
       * @return �g���q���������t�@�C������Ԃ�
       */
      inline std::string GetFileName() const {
        return _path.stem().string();
      }
      /**
       * @brief  �L�[���̎擾
       * @return �A�z�z��ɓo�^����L�[
       */
      inline std::string GetKey() const {
        return _key;
      }
      /**
       * @brief  �L�[�ƃp�X�̎擾
       * @return ����:�L�[ �E��:�p�X
       */
      inline std::pair<std::string_view, std::filesystem::path> GetFileData() {
        return { _key, _path };
      }
    protected:
      std::filesystem::path _path; //!< �t�@�C���p�X
      std::string _key;            //!< �A�z�z��Ŏg�p����L�[
    };
  } // namespace FileServer
} // namespace AppFrame
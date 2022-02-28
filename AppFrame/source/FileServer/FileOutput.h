/*****************************************************************//**
 * @file   FileOutput.h
 * @brief  �t�@�C���̓��o�̓N���X
 *
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <filesystem>
#include <string_view>

/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �t�@�C���T�[�o
   */
  namespace FileServer {
    /**
     * @class FileOutput
     * @brief �t�@�C���̓��o�͏����N���X
     */
    class FileOutput {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  path �t�@�C���̃p�X
       */
      FileOutput(std::filesystem::path path);
      /**
       * @brief  �f�X�g���N�^
       */
      ~FileOutput();
      /**
       * @brief  �e�L�X�g�t�@�C���ւ̏o��
       * @param  text �o�͂��镶����
       * @return �����ɐ��������ꍇ��true
       *         ���s�����ꍇ��false��Ԃ�
       */
      bool OutputText(std::string_view text);
      /**
       * @brief  ���o�̓t�@�C���̐ݒ�
       * @param  file �ݒ肷��t�@�C���̃p�X
       * @return �ݒ�ɐ����������̔���
       */
      bool SetFilePath(std::filesystem::path file);
    private:
      std::filesystem::path _file; //!< ���o�̓t�@�C��
      /**
       * @brief  �p�X���L�����̔���
       * @param  path ����t�@�C��
       * @return �p�X���L���ȏꍇ��true
       *         �L���ł͂Ȃ��ꍇ��false��Ԃ�
       */
      bool IsPath(std::filesystem::path path);
    };
  } // namespace FileServer
} // namespace AppFrame
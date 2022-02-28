/*****************************************************************//**
 * @file   SoundServer.h
 * @brief  �������Ǘ�����T�[�o�N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "../Server/ServerTemplateUnordered.h"
#include <filesystem>
#include <unordered_map>
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �T�E���h�x�[�X
   */
  namespace Sound {
    /**
     * @class SoundServer
     * @brief �������Ǘ�����T�E���h�T�[�o
     */
    class SoundServer : Server::ServerTemplateUnordered<std::string, int> {
    public:
      /**
       * @brief ���������i�[���铮�I�z��
       *        first:�����t�@�C���ɕR�Â��镶���� second:�����t�@�C���̃p�X
       */
      using SoundMap = std::vector<std::pair<std::string_view, std::string_view>>;
      /**
       * @brief �R���X�g���N�^
       */
      SoundServer();
      /**
       * @brief  �������
       * @return true:���� false:�ُ�I��
       */
      bool Release() override;
      /**
       * @brief  �����t�@�C���̓ǂݎ��
       * @param  key �T�E���h�n���h���ɕR�Â��镶����
       * @param  soundFile �����t�@�C���̃p�X
       * @return true:����I�� false:�ǂݎ�莸�s
       */
      bool AddSound(std::string_view key, const std::filesystem::path soundFile);
      /**
       * @brief  �R���e�i���g�p���������t�@�C���̓ǂݎ��
       * @param  soundMap �T�E���h��񂪊i�[���ꂽ�R���e�i
       */
      void AddSounds(const SoundMap& soundMap);
      /**
       * @brief  �w�肵���T�E���h�n���h���̎擾
       * @param  key �Ώۂ̃T�E���h�n���h���ɕR�Â���ꂽ������
       * @return �T�E���h�n���h��
       *         �L�[���L���ł͂Ȃ��ꍇ��-1��Ԃ�
       */
      int GetSoundMem(std::string_view key) const;
    };
  } // namespace Sound
} // namespace AppFrame
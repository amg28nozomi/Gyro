/*****************************************************************//**
 * @file    EffectServer.h
 * @brief   �G�t�F�N�g���Ǘ�����T�[�o�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "../ApplicationMain.h"

 /** ��i�p���O��� */
namespace Gyro {
  /** �G�t�F�N�g�p���O��� */
  namespace Effect {
    namespace AppServer = AppFrame::Server;
    /**
     * @class EffectServer
     * @brief �G�t�F�N�g���Ǘ�����T�[�o�N���X
     */
    class EffectServer : AppServer::ServerTemplateUnordered<std::string, int> {
    public:
      /**
       * @brief  �G�t�F�N�g�����i�[���铮�I�z��
                 first:�G�t�F�N�g�t�@�C���ɕR�Â��镶����
                 second:�G�t�F�N�g�t�@�C���̃p�X
       */
      using EffectMap = std::vector<std::pair<std::string_view, std::string_view>>;
      /**
       * @brief  �G�t�F�N�g�����i�[���铮�I�z��
                 first:�G�t�F�N�g�t�@�C���ɕR�Â��镶����
                 second:�G�t�F�N�g�g�嗦
       */
      using EffectMagniMap = std::vector<std::pair<std::string_view, float>>;
      /**
       * @brief  �R���X�g���N�^
       */
      EffectServer();
      /**
       * @brief  �������
       * @return true:����
       *         false:�ُ�I��
       */
      bool Release() override;
      /**
       * @brief  �G�t�F�N�g�t�@�C���̓ǂݎ��
       * @param  key �G�t�F�N�g�n���h���ɕR�Â��镶����
       * @param  effectFile �G�t�F�N�g�t�@�C���̃p�X
       * @param  magni �G�t�F�N�g�g�嗦
       * @return true:����I��
       *         false:�ǂݎ�莸�s
       */
      bool AddEffect(std::string_view key, const std::filesystem::path effectFile, const float magni);
      /**
       * @brief  �R���e�i���g�p�����G�t�F�N�g�t�@�C���̓ǂݎ��
       * @param  effectMap �G�t�F�N�g��񂪊i�[���ꂽ�R���e�i
       * @param  effectMagniMap �G�t�F�N�g�g�嗦���i�[���ꂽ�R���e�i
       */
      void AddEffects(const EffectMap& effectMap, const EffectMagniMap& effectMagniMap);
      /**
       * @brief  �w�肵���G�t�F�N�g�n���h���̎擾
       * @param  key �Ώۂ̃G�t�F�N�g�n���h���ɕR�Â���ꂽ������
       * @return �G�t�F�N�g�n���h��
       *         �L�[���L���ł͂Ȃ��ꍇ��-1��Ԃ�
       */
      int GetEffectHandle(std::string_view key) const;
    };
  } // namespace Effect
} // namespace Gyro
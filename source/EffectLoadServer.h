/*****************************************************************//**
 * @file    EffectLoadServer.h
 * @brief   �G�t�F�N�g���Ǘ�����T�[�o�N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"

 /**
  * @brief �Q�[���x�[�X
  */
namespace Gyro {
  /**
   * @brief �G�t�F�N�g�x�[�X
   */
  namespace Effect {
    namespace AppServer = AppFrame::Server;
    /**
     * @class EffectLoadServer
     * @brief �G�t�F�N�g���Ǘ�����T�[�o�N���X
     */
    class EffectLoadServer : AppServer::ServerTemplateUnordered<std::string, int> {
    public:
      /**
       * @brief  �G�t�F�N�g�����i�[���铮�I�z��
       * @param  �G�t�F�N�g�t�@�C���ɕR�Â��镶����
       * @param  �G�t�F�N�g�t�@�C���̃p�X
       * @param  �G�t�F�N�g�g�嗦
       */
      using EffectMap = std::vector<std::tuple<std::string_view, std::string_view, float>>;
      /**
       * @brief  �R���X�g���N�^
       */
      EffectLoadServer();
      /**
       * @brief  �������
       * @return true
       */
      bool Release() override;
      /**
       * @brief  �R���e�i���g�p�����G�t�F�N�g�t�@�C���̓ǂݎ��
       * @param  effectMap �G�t�F�N�g��񂪊i�[���ꂽ�R���e�i
       */
      void AddEffects(const EffectMap& effectMap);
      /**
       * @brief  �w�肵���G�t�F�N�g�n���h���̎擾
       * @param  key �Ώۂ̃G�t�F�N�g�n���h���ɕR�Â���ꂽ������
       * @return �G�t�F�N�g�n���h��
       *         �L�[���L���ł͂Ȃ��ꍇ��-1��Ԃ�
       */
      int GetEffectHandle(std::string_view key) const;

    private:
      /**
       * @brief  �G�t�F�N�g�t�@�C���̓ǂݎ��
       * @param  key �G�t�F�N�g�n���h���ɕR�Â��镶����
       * @param  effectFile �G�t�F�N�g�t�@�C���̃p�X
       * @param  magni �G�t�F�N�g�g�嗦
       * @return true:����I��
       *         false:�ǂݎ�莸�s
       */
      bool AddEffect(std::string_view key, const std::filesystem::path effectFile, const float magni);
    };
  } // namespace Effect
} // namespace Gyro
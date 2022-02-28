/*****************************************************************//**
 * @file   ModelServer.h
 * @brief  ��������L�[�Ƃ��ă��f�����ƃA�j���[�V�������Ǘ�����T�[�o�N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "../Server/ServerTemplateUnordered.h"
#include "ModelData.h"
/**
 * @�A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief ���f���x�[�X
   */
  namespace Model {
    constexpr auto AllDelete = true;
    constexpr auto OneDelete = false;
    /**
     * @class ModelServer
     * @brief ��������L�[�Ƃ��ă��f�����ƃA�j���[�V�������Ǘ�����T�[�o
     */
    class ModelServer : Server::ServerTemplateUnordered<std::string, ModelData>{
    public:
      /**
       * @brief ���f�������i�[����R���e�i�̕ʖ�
       */
      using ModelDatas = std::vector<std::pair<std::string_view, std::string_view>>;
      /**
       * @brief �R���X�g���N�^
       */
      ModelServer();
      /**
       * @brief  ����������
       * @return 
       */
      bool Init() override;
      /**
       * @brief  ���\�[�X�̉��
       * @return 
       */
      bool Release() override;
      /**
       * @brief  MV1�t�@�C���̓ǂݎ�菈��
       * @param  key  ���f�����ɕR�Â��镶����
       * @param  path �Ώۃt�@�C���̃p�X
       * @return true:�o�^���� false:�o�^���s
       */
      bool AddMV1Model(std::string_view key, std::string_view path);
      /**
       * @brief  MV1�t�@�C���̓ǂݎ�菈��(����)
       * @param  mv1Files ���f�����ɕR�Â��镶����
       */
      void AddMV1Model(const ModelDatas& mv1Files);
      /**
       * @brief  �o�^����Ă���S�Ẵ��f�������폜����
       */
      void DeleteModels();
      /**
       * @brief  �����������f���n���h�����폜����
       * @param  key ���f�����ɕR�Â���ꂽ������
       * @param  flag �S�폜�t���O(true:�S�Ă̕����n���h�����폜 false:�L�[�ɑΉ������R���e�i�̂ݍ폜)
       * @return true:�������� false:�L�[���q�b�g���Ȃ�����
       */
      bool DeleteDuplicateModels(std::string_view key, bool flag = false);
      /**
       * @brief  ���f���n���h���̎擾
       * @param  key ���f�����ɕR�Â���ꂽ������
       * @return first:�擾�ɐ��������ꍇ�̓��f���n���h����Ԃ� ���s�����ꍇ��-1��Ԃ�
       *         second:���ʔԍ�
       */
      std::pair<int, unsigned short> GetModel(std::string_view key, unsigned short number);
      /**
       * @brief  �w�肵���A�j���[�V�����ԍ��̎擾
       * @param  key ���f�����ɕR�Â���ꂽ������
       * @param  animeName �A�j���[�V������
       * @return �擾�ɐ��������ꍇ�̓A�j���[�V�����ԍ���Ԃ�
       *         �擾�Ɏ��s�����ꍇ��-1��Ԃ�
       */
      int GetAnimIndex(std::string_view key, std::string_view animName);
    private:
      /**
       * @brief �o�^����Ă��郂�f���n���h�����������
       * @param handles ���f���n���h�����i�[����Ă���R���e�i�̎Q��
       */
      void DeleteModels(std::unordered_map<unsigned short, int>& handles);
      /**
       * @brief �����o�^����Ă���n���h���݂̂��폜����
       * @param handles ���f���n���h�����i�[����Ă���R���e�i�̎Q��
       */
      void DeleteDuplicateModels(std::unordered_map<unsigned short, int>& handles);
      /**
       * @brief  �A�j���[�V�����ԍ��̎擾
       * @param  key ���f�����ɕR�Â���ꂽ������
       * @param  animeName �A�j���[�V������
       * @return �擾�ɐ��������ꍇ�̓A�j���[�V�����ԍ���Ԃ�
       *         ���s�����ꍇ��-1��Ԃ�
       */
      int AnimNumber(std::string_view key, std::string_view animeName) const;
     };
  } // namespace Model
} // namespace AppFrame
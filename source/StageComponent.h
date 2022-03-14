/*****************************************************************//**
 * @file   StageComponent.h
 * @brief  �X�e�[�W���쐬����N���X
 * 
 * @author �y�� ����
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "StageData.h"
#include <appframe.h>
#include <string>
#include <unordered_map>
#include "appframe.h"
#include "SkySphere.h"
#include "SpawnServer.h"
#include "ObjectBase.h"
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    class ApplicationMain; //!< �O���錾
  } // namespace Application

  namespace Object {
    class SkySphere;
  } // namespace Object
  /**
   * @brief �X�e�[�W
   */
  namespace Stage {
    namespace AppMath = AppFrame::Math;
    /**
     * @class StageComponent
     * @brief �X�e�[�W�R���|�[�l���g�N���X
     */
    class StageComponent{
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      StageComponent(Application::ApplicationMain& app);
      /**
       * @brief �f�X�g���N�^
       */
      ~StageComponent();
      /**
       * @brief  ������
       * @param  jsonName json�̃t�@�C����
       * @return true
       */
      bool Init(std::filesystem::path jsonName);
      /**
       * @brief �X�e�[�W����ǂݍ���
       * @param key _stageModelMap�ɓo�^����L�[
       * @param stageData �X�e�[�W���
       */
      void LoadStage(std::string_view key, StageData& stageData);
      /**
       * @brief  �X�e�[�W�������ƂɃI�u�W�F�N�g�������Ă���
       * @param  key _stageModelMap�ɓo�^����L�[
       * @return true
       */
      bool CreateStage(std::string key);
      /**
       * @brief  �X�V
       * @return true
       */
      bool Process();
      /**
       * @brief �`��
       */
      bool Draw() const;
      /**
       * @brief  �X�e�[�W���̉��
       * @return true
       */
      bool ReleaseStageInfo();
      /**
       * @brief  �X�e�[�W���f���������
       * @return true
       */
      bool ReleaseModel();
      void AddSky(std::shared_ptr<Object::SkySphere> sky);
      /**
       * @brief  �X�e�[�W���̎擾
       * @param  key �e�X�e�[�W�Ɋ֘A�Â����C�ӂ̕�����
       * @return �n���h���ƃX�e�[�W���
       */
      std::vector<std::pair<int, StageData>> GetStageModels(std::string key);
      /**
       * @brief  ���f���n���h���i�[�R���e�i�̎擾
       * @return ���f���n���h���i�[�R���e�i
       */
      std::vector<int> GetStageModel() const {
          return _model;
      }
      /**
       * @brief  �X�J�C�X�t�B�A�̎擾
       * @return �X�J�C�X�t�B�A
       */
      std::shared_ptr<Object::SkySphere> GetSkySphere() {
        return _skySphere;
      }
      /**
       * @brief  �X�e�[�W�l�[���̎擾
       * @return �X�e�[�W�l�[��
       */
      std::filesystem::path GetStageName() {
        return _stageName;
      }
    private:
      /**
       * @brief ��������L�[�Ƃ��ăX�e�[�W�����Ǘ�����A�z�z��
       */
      std::unordered_map<std::string, std::vector<std::pair<int, StageData>>> _stageModelMap;
      std::vector<int> _model{ -1 }; //!< ���f���n���h���i�[�p�R���e�i
      std::shared_ptr<Object::SkySphere> _skySphere{ nullptr };
      std::filesystem::path _stageName;
    };
  } //namespace Stage
} // namespace Gyro
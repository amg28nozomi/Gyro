/*****************************************************************//**
 * @file   StageComponent.h
 * @brief  �X�e�[�W���쐬����N���X
 * 
 * @author �y�� ����
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "StageData.h"
#include "StageBase.h"
#include "appframe.h"
#include <string>
#include <unordered_map>
#include "appframe.h"
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �X�e�[�W
   */
  namespace Stage {
    namespace AppMath = AppFrame::Math;
    /**
     * @class StageComponent
     * @brief �X�e�[�W�R���|�[�l���g�N���X
     */
    class StageComponent : public Object::StageBase {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      StageComponent(Application::ApplicationMain& app);
      /**
       * ������
       */
      bool Init() override;
      /**
       * @brief 
       */
      void LoadStage(std::string_view key, StageData& stageData);
      /**
       * @brief  
       * @param  key 
       * @return 
       */
      bool CreateStage(std::string key);
      /**
       * @brief �X�V
       */
      bool Process() override;
      /**
       * @brief �`��
       */
      bool Draw() const override;
      /**
       * @brief  �X�e�[�W���̎擾
       * @param  key �e�X�e�[�W�Ɋ֘A�Â����C�ӂ̕�����
       * @return �n���h���ƃX�e�[�W���
       */
      std::vector<std::pair<int, StageData>> GetStageModels(std::string key);

    private:
      std::unordered_map<std::string, std::vector<std::pair<int, StageData>>> _stageModelMap; //!< �e�X�e�[�W���̘A�z�z��
    };
  } //namespace Stage
} // namespace Gyro

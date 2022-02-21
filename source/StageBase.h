/*****************************************************************//**
 * @file   StageBase.h
 * @brief  �X�e�[�W�̃X�[�p�[�N���X
 * 
 * @author �y�� ����
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
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
  /**
   * @brief �X�e�[�W�x�[�X
   */
  namespace Object {
    namespace AppMath = AppFrame::Math;
    class SpawnBase; //!< �X�|�[�����
    /**
     * @class StageBase
     * @brief �X�e�[�W�̃X�[�p�[�N���X
     */
    class StageBase {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param �A�v���P�[�V�����̎Q��
       */
      StageBase(Application::ApplicationMain& app);
      /**
       * 
       */
      ~StageBase();
      /**
       * @brief  ����������
       * @return true
       */
      virtual bool Init();
      /**
       * @brief  �X�V����
       * @return true
       */
      virtual bool Process();
      /**
       * @brief  �`�揈��
       * @return true
       */
      virtual bool Draw() const;
      /**
       * @brief  ���f���n���h���i�[�R���e�i�̎擾
       * @return ���f���n���h���i�[�R���e�i
       */
      std::vector<int> GetStageModel() const {
          return _model;
      }
    protected:
      Application::ApplicationMain& _app;        //!< �A�v���P�[�V�����̎Q��
      std::vector<int> _model{ -1 }; //!< ���f���n���h���i�[�p�R���e�i
    };
  } // namespace Stage
} // namespace Gyro

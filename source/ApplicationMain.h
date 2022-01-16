/*****************************************************************//**
 * @file   ApplicationMain.h
 * @brief  �A�v���P�[�V�����x�[�X�̃T�u�N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
/**
 * @brief �Q�[���X�y�[�X
 */
namespace Gyro {
  /**
   * @brief �A�v���P�[�V����
   */
  namespace Application {
    /**
     * @class ApplicationMain
     * @brief �A�v���P�[�V�������C��
     */
    class ApplicationMain : public AppFrame::Application::ApplicationBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       */
      ApplicationMain();
      /**
       * @brief  ������
       * @return true:���������� false:���������s
       */
      bool Init() override;
      /**
       * @brief  ���͏���
       * @return 
       */
      bool Input() override;
      /**
       * @brief  �t���[���J�E���^�̎擾
       * @return �t���[���J�E���^
       */
      const int GetFrameCount() const override {
        return 0;
      }
    private:
      /**
       * @brief  �X�V����
       * @return
       */
      bool Process() override;
    };
  } // namespace Application
} // namespace Gyro
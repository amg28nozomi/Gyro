/*****************************************************************//**
 * @file    ModePause.h
 * @brief   ���[�h�|�[�Y�N���X
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
   * @brief ���[�h�x�[�X
   */
  namespace Mode {
    namespace AppMath = AppFrame::Math;
    /**
     * @class ModePause
     * @brief ���[�h�|�[�Y�N���X
     */
    class ModePause : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      ModePause(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~ModePause() override;
      /**
       * @brief  ����������
       * @return true
       */
      bool Init() override;
      /**
       * @brief  ��������
       * @return true
       */
      bool Enter() override;
      /**
       * @brief  �I������
       * @return true
       */
      bool Exit() override;
      /**
       * @brief  ���͏���
       * @param  input �C���v�b�g�I�y���[�V�����̎Q��
       * @return true
       */
      bool Input(AppFrame::Application::InputOperation& input) override;
      /**
       * @brief  �X�V����
       * @return true
       */
      bool Process() override;
      /**
       * @brief  �`�揈��
       * @return true
       */
      bool Draw() const override;

    private:
      /**
       * @brief  ���\�[�X�ǂݍ���
       */
      void LoadResource();
      /**
       * @brief  ���[�h�؂�ւ�
       */
      void ChangeMode();

      int _pauseHandle{ -1 };            //!< �|�[�Y�摜
      int _continueHandle[2]{ -1, -1 };  //!< �R���e�B�j���[�摜
      int _quitGameHandle[2]{ -1, -1 };  //!< �Q�[���I���摜
      int _continue{ 1 };                //!< �R���e�j���[
      int _quitGame{ 0 };                //!< �Q�[���I��
      bool _decision{ false };           //!< �I������
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
    };
  }
}
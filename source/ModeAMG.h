/*****************************************************************//**
 * @file    ModeAMG.h
 * @brief   ���[�hAMG�N���X
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
  namespace Application {
    class ApplicationMain; //!< �O���錾
  } // namespace Application
  /**
   * @brief ���[�h�x�[�X
   */
  namespace Mode {
    namespace AppMath = AppFrame::Math;
    /**
     * @class ModeAMG
     * @brief ���[�hAMG�N���X
     */
    class ModeAMG : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      ModeAMG(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~ModeAMG() override;
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
       * @brief  �ϐ����
       */
      void Release();
      /**
       * @brief  ���\�[�X�ǂݍ���
       */
      void LoadResource();
      /**
       * @brief  ���[�h�؂�ւ�
       */
      void ChangeMode();

      int _amgHandle{ -1 };  //!< AMG�摜
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
    };
  }
}
/*****************************************************************//**
 * @file    ModeCredit.h
 * @brief   ���[�h�N���W�b�g�N���X
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
     * @class ModeCredit
     * @brief ���[�h�N���W�b�g�N���X
     */
    class ModeCredit : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      ModeCredit(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~ModeCredit() override;
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

      int _creditHandle{ -1 };  //!< �N���W�b�g�摜
      bool _backTitle{ false };  //!< �^�C�g���o�b�N
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
    };
  }
}
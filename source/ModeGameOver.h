/*****************************************************************//**
 * @file    ModeGameOver.h
 * @brief   ���[�h�Q�[���I�[�o�[�N���X
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
     * @class ModeGameOver
     * @brief ���[�h�Q�[���I�[�o�[�N���X
     */
    class ModeGameOver : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      ModeGameOver(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~ModeGameOver() override;
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
       * @brief  ���X�e�B�b�N�㉺����
       * @param  leftY ���X�e�B�b�N�㉺���͒l
       */
      void LeftStickYInput(const int leftY);
      /**
       * @brief  ���[�h�؂�ւ�
       */
      void ChangeMode();

      int _gameOverHandle{ -1 };          //!< �Q�[���I�[�o�[�摜
      int _retryHandle[2]{ -1, -1 };      //!< ���g���C�摜
      int _backTitleHandle[2]{ -1, -1 };  //!< �^�C�g���o�b�N�摜
      int _retry{ 0 };                    //!< ���g���C�ԍ�
      int _backTitle{ 0 };                //!< �^�C�g���o�b�N�ԍ�
      bool _isStick{ false };             //!< ���X�e�B�b�N�㉺���͗L��
      bool _decision{ false };            //!< �I������
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
    };
  }
}
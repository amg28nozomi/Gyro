/*****************************************************************//**
 * @file    ModeTitle.h
 * @brief   ���[�h�^�C�g���N���X
 *
 * @author  �{�V�s��
 * @date    February 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"
#include "Studio.h"

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
     * @class ModeTitle
     * @brief ���[�h�^�C�g���N���X
     */
    class ModeTitle : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      ModeTitle(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~ModeTitle() override;
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
       * @brief  ���X�e�B�b�N�㉺����
       * @param  leftY ���X�e�B�b�N�㉺���͒l
       */
      void LeftStickYInput(const int leftY);
      /**
       * @brief  �g�嗦�ݒ�
       */
      void SetExRate();
      /**
       * @brief  ���[�h�؂�ւ�
       */
      void ChangeMode();
      /**
       * @brief  �C���Q�[���J��
       */
      void InGame();
      /**
       * @brief  �N���W�b�g�J��
       */
      void Credit();

      int _titleHandle{ -1 };          //!< �^�C�g���摜
      int _pressButtonHandle{ -1 };    //!< �v���X�{�^���摜
      int _gameStartHandle{ -1 };      //!< �Q�[���J�n�摜
      int _creditHandle{ -1 };         //!< �N���W�b�g�摜
      int _quitGameHandle{ -1 };       //!< �Q�[���I���摜
      int _sceneNum{ 0 };              //!< ��ʔԍ�
      float _gameStartExRate{ 1.0f };  //!< �Q�[���J�n�g�嗦
      float _creditExRate{ 1.0f };     //!< �N���W�b�g�g�嗦
      float _quitGameExRate{ 1.0f };   //!< �Q�[���I���g�嗦
      bool _isStick{ false };          //!< ���X�e�B�b�N�㉺���͔���
      bool _decision{ false };         //!< �I������
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
      //!< �X�^�W�I
      std::unique_ptr<Studio::Studio> _studio{ nullptr };
    };
  }
}
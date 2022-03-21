/*****************************************************************//**
 * @file    ModeResult.h
 * @brief   ���[�h���U���g�N���X
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
     * @class ModeResult
     * @brief ���[�h���U���g�N���X
     */
    class ModeResult : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  app �A�v���P�[�V�����̎Q��
       */
      ModeResult(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      ~ModeResult() override;
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

      int _resultHandle{ -1 };   //!< ���U���g�摜
      bool _backTitle{ false };  //!< �^�C�g���o�b�N
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
      //!< �X�^�W�I
      std::unique_ptr<Studio::Studio> _studio{ nullptr };
    };
  }
}
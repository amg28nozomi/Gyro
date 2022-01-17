/*****************************************************************//**
 * @file   ModeGame.h
 * @brief  �C���Q�[���������s�����[�h
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  // �O���錾
  class ApplicationMain;
  /**
   * @brief ���[�h�x�[�X
   */
  namespace Mode {
    /**
     * @class ModeGame
     * @brief �Q�[���������s�����[�h
     */
    class ModeGame : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      ModeGame(AppFrame::Application::ApplicationBase& app);
      /**
       * @brief �f�X�g���N�^
       */
      ~ModeGame() override;
      /**
       * @brief  ����������
       * @return true:���������� false:���������s
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
       * @return true:����I�� false:��蔭��
       */
      bool Input(AppFrame::Application::InputOperation& input) override;
      /**
       * @brief  �X�V����
       * @return true:����I�� false:��蔭��
       */
      bool Process() override;
      /**
       * @brief  �`�揈��
       * @return 
       */
      bool Draw() const override;
    private:
    };
  } // namespace Mode
} // namespace Gyro
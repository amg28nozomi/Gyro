/*****************************************************************//**
 * @file   ModeLoading.h
 * @brief  ���[�h���[�f�B���O�N���X
 * 
 * @author �y������
 * @date   March 2022
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
    /**
     * @class ModeLoading
     * @brief ���[�h���[�f�B���O�N���X
     */
    class ModeLoading : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      ModeLoading(Application::ApplicationMain& app);
      /**
       * @brief �f�X�g���N�^
       */
      ~ModeLoading() override;
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
       * @brief  ���\�[�X�ǂݍ���
       */
      void LoadResource();
      /**
       * @brief  ���[�h�؂�ւ�
       */
      void ChangeMode();

      int _loadHandle[ 4 ]{ -1 };  //!< AMG�摜
      int _cnt{ 0 };               //!< �J�E���g
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
    };
  } // namespace Mode
} // namespace Gyro
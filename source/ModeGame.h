/*****************************************************************//**
 * @file   ModeGame.h
 * @brief  �C���Q�[���������s�����[�h
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "Player.h"
#include "PrimitiveBase.h"
#include "PrimitivePlane.h"
#include "SpawnServer.h"
#include "Light.h"
#include "Shadow.h"
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  // �O���錾
  namespace Application {
    class ApplicationMain;
  }
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
      ModeGame(Application::ApplicationMain& app);
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
      /**
       * @brief  �X�e�[�W�̐ݒ�
       * @return true:����I�� false:��蔭��
       */
      bool StageChange(std::string_view key);
      /**
       * @brief  �A�v���P�[�V�������C���̎擾
       * @return �A�v���P�[�V�������C���̎Q�Ƃ�Ԃ�
       */
      Application::ApplicationMain& GetAppMain();
    private:
      bool _isEffectLoad{ false };  //!< �G�t�F�N�g�ǂݍ��݃t���O
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
      //!< ��
      Primitive::Plane _plane;
      //!< ���C�g
      std::unique_ptr<Light::Light> _light;
      //!< �V���h�E
      std::unique_ptr<Shadow::Shadow> _shadow;
      //!< ���݂̃X�e�[�W�L�[
      std::string _key;
      //!< wave�t���O
      bool _wave1{ true };
      bool _wave2{ true };
      bool _wave3{ true };
      bool _wave4{ true };
      bool _bossStage{ true };
      int _waveNum{ 0 };

      /**
       * @brief ���\�[�X�̓ǂݎ��
       */
      void LoadResource();
      /**
       * @brief �G�t�F�N�g���\�[�X�̓ǂݎ��
       */
      void LoadEffectResource();
      /**
       * @brief �X�|�[�����̐ݒ�
       */
      void SetSpawn();
      /**
       * @brief �X�|�[��������^�C�~���O
       */
      void SpawnTiming();
      /**
       * @brief �Q�[���I�[�o�[�؂�ւ�
       */
      void GameOver();
    };
  } // namespace Mode
} // namespace Gyro
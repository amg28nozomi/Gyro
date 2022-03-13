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
#include "StageTransition.h"
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
   * @brief �G�l�~�[�x�[�X
   */
  namespace Enemy {
    class EnemyDroneBoss; //!< �O���錾
    class EnemyWheelBoss; //!< �O���錾
  } // namespace Enemy
  /**
   * @brief ���[�h�x�[�X
   */
  namespace Mode {
    /**
     * @class ModeGame
     * @brief �Q�[���������s�����[�h
     */
    class ModeGame : public AppFrame::Mode::ModeBase {
    private:
      friend class Application::ApplicationMain;
      friend class Enemy::EnemyDroneBoss;
      friend class Enemy::EnemyWheelBoss;
    public:
      /**
       * @brief �Q�[���̏�Ԃ�\���񋓌^�N���X
       */
      enum class GameState {
        Play,    // �v���C��
        Pouse,   // �|�[�Y
        GameOver // �Q�[���I�[�o�[
      };
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
      bool StageChange(const Stage::StageTransition::StageType& key);
      /**
       * @brief  �A�v���P�[�V�������C���̎擾
       * @return �A�v���P�[�V�������C���̎Q�Ƃ�Ԃ�
       */
      Application::ApplicationMain& GetAppMain();
      /**
       * @brief  �Q�[���I�[�o�[��Ԃ��̔���
       * @return true:�Q�[���I�[�o�[ false:�Q�[���I�[�o�[�ł͂Ȃ�
       */
      bool IsGameOver() const {
        return _gameState == GameState::GameOver;
      }
      /**
       * @brief  �{�X�J�E���g�̎擾
       * @return �{�X�J�E���g
       */
      inline int GetBossCount() {
        return _bossCount;
      }
    private:
      bool _isEffectLoad{ false };  //!< �G�t�F�N�g�ǂݍ��݃t���O
      //!< �A�v���P�[�V�������C���̎Q��
      Application::ApplicationMain& _appMain;
      //!< �Q�[�����
      GameState _gameState{GameState::Pouse};
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
      //!< �{�X�����J�E���g
      int _bossCount{0};
      //!< �{�X��
      int _bossNum{0};
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
       * @brief  �Q�[���I�[�o�[����
       * @return true:�Q�[���I�[�o�[���������s false:�Q�[���I�[�o�[�ł͂Ȃ�
       */
      bool GameOver();
      /**
       * @brief  �Q�[���I�[�o�[��Ԃւ̐؂�ւ�
       * @brief �X�|�[��������^�C�~���O
       */
      void SpawnTiming();
      /**
       * @brief �Q�[���I�[�o�[�؂�ւ�
       */
      // void GameOver();
      /**
       * @brief ���U���g�؂�ւ�
       */
      void Result();
      /**
       * @brief �|�[�Y�؂�ւ�
       */
      void Pause();
      /**
       * @brief ���[�f�B���O�؂�ւ�
       */
      void Loading();
      void ToGameOver();
      /**
       * @brief �I�u�W�F�N�g�ԍ�������������
       */
      void ResetObjectNumber();
      /**
       * @brief �{�X�����J�E���g�̏�����
       */
      inline void BossCountReset() {
        _bossCount = 0;
      }
      /**
       * @brief  �Q�[���N���A�ɑJ�ڂ��邩�̔���
       * @return true:�J�ڂ��� false:�J�ڂ��Ȃ�
       */
      bool ToGameClear();
      /**
       * @brief  �Q�[���N���A����
       * @return true:�N���A false:�N���A�ł͂Ȃ�
       */
      inline bool IsGameClear() const {
        return _bossCount == _bossNum;
      }
    };
  } // namespace Mode
} // namespace Gyro
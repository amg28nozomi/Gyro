/*****************************************************************//**
 * @file   StageTransition.h
 * @brief  �X�e�[�W�J�ڂ��Ǘ�����}�l�[�W���[�N���X
 * 
 * @author ��؊�C
 * @date   March 2022
 *********************************************************************/
#pragma once
#include <appframe.h>
#include <unordered_map>

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    class ApplicationMain;
  } // namespace Applicaiton
  /**
   * @brief ���[�h�x�[�X
   */
  namespace Mode {
    class ModeGame;
  } // namespace Mode
  /**
   * @brief �X�e�[�W�x�[�X
   */
  namespace Stage {
    /**
     * @class StageTransition
     * @brief �X�e�[�W�J�ڂ��Ǘ�����}�l�[�W���[
     */
    class StageTransition {
    private:
      /**
       * @brief ���[�h�Q�[�����t�����h�N���X�w��
       */
      friend class Mode::ModeGame;
    public:
      /**
       * @brief �X�e�[�W�̎�ނ�����킷�񋓌^�N���X
       */
      enum class StageType {
        Null,   // �Y���Ȃ�
        Normal, // �ʏ�X�e�[�W
        Boss    // �{�X�X�e�[�W
      };
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      StageTransition(Application::ApplicationMain& app);
      /**
       * @brief  ����������
       * @param  haveData �f�[�^�x�[�X��ێ����邩(true:�ێ� false:�ێ����Ȃ�(�f�t�H���g))
       * @return true
       */
      void Init(const bool haveData = false);
      /**
       * @brief  �X�e�[�W�L�[�̓o�^(����)
       * @param  stageMap �X�e�[�W�L�[���i�[���ꂽ�A�z�z��
       */
      bool Register(const std::unordered_map<StageType, std::string_view> stageMap);
      /**
       * @brief  �X�e�[�W�L�[�̓o�^����
       * @param  stage �X�e�[�W�^�C�v
       * @param  key   �X�e�[�W�L�[
       * @return true:�o�^���� false:�o�^���s
       */
      bool Register(const StageType& stage, std::string_view key);
      /**
       * @brief  �X�e�[�W�̑J�ڗ\��
       * @param  stage �J�ڐ�̃X�e�[�W�^�C�v
       * @return true:�\�񐬌� false:�\�񎸔s
       */
      bool ChangeReserve(const StageType& stage);
      /**
       * @brief  �X�e�[�W�𒼐ڐ؂�ւ���
       * @param  stage �J�ڐ�̃X�e�[�W�^�C�v
       * @return true:�J�ڐ��� false:�J�ڎ��s
       */
      bool ChangeStage(const StageType& stage);
      /**
       * @brief  �X�e�[�W�J�ڂ��s����
       * @return true:�J�ڎ��s false:�J�ڂ��s���Ă��Ȃ�
       */
      bool IsTransition();
      /**
       * @brief  �X�e�[�W�L�[�̎擾
       * @return �L�[���o�^����Ă���ꍇ�̓X�e�[�W�L�[��Ԃ�
       *         �X�e�[�W�^�C�v��Null�̏ꍇ�͋�̃L�[��Ԃ�
       */
      std::string GetStageKey() const;
      /**
       * @brief  ���݂̃X�e�[�W�^�C�v�̎擾
       * @return �X�e�[�W�^�C�v
       */
      StageType GetStageType() const {
        return _stageType;
      }
      /**
       * @brief  �X�e�[�W�^�C�v����v���Ă��Ȃ����̔���
       * @param  stage �ΏۂƂȂ�X�e�[�W�^�C�v
       * @return true:��v���Ă��Ȃ� false:��v���Ă���
       */
      bool StageDifferent(const StageType& stage) const {
        return stage != _stageType;
      }
    protected:
      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;
      //!< �X�e�[�W�^�C�v
      StageType _stageType{StageType::Null};
      //!< �X�e�[�W�^�C�v�̗\��
      StageType _reserveType{StageType::Null};
      //!< �X�e�[�W�L�[���Ǘ�����A�z�z��
      std::unordered_map<StageType, std::string> _registry;
      //!< �X�e�[�W�J�ڃt���O
      bool _transition{false};
      /**
       * @brief  �X�e�[�W�̑J�ڏ���
       * @return true:�J�ڏI�� false:�J�ڌp��
       */
      bool Transition();
      /**
       * @brief  �X�e�[�W�^�C�v��Null���̔���
       * @param  stage ���肷��X�e�[�W�^�C�v
       * @return true:�^�C�v��NULL false:�^�C�v��NULL�ł͂Ȃ�
       */
      bool StageNull(const StageType& stage) const {
        return stage == StageType::Null;
      }
      /**
       * @brief  �X�e�[�W�L�[�̎擾
       * @param  stage �X�e�[�W�^�C�v
       * @return �X�e�[�W�^�C�v�ɑΉ������X�e�[�W�L�[
       *         �擾�Ɏ��s�����ꍇ�͋�̕������Ԃ�
       */
      std::string StageKey(const StageType& stage) const;
      /**
       * @brief �X�e�[�W�^�C�v�𒼐ڐݒ肷��
       * @param stage �X�e�[�W�^�C�v
       */
      void SetStageKey(const StageType& stage) {
        _stageType = stage;
      }
    };
  } // namespace Stage
} // namespace Gyro
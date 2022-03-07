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
   * @brief �X�e�[�W�x�[�X
   */
  namespace Stage {
    /**
     * @class StageTransition
     * @brief �X�e�[�W�J�ڂ��Ǘ�����}�l�[�W���[
     */
    class StageTransition {
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
       * @brief  �X�e�[�W�L�[�̓o�^����
       * @param  stage �X�e�[�W�^�C�v
       * @param  key   �X�e�[�W�L�[
       * @return true:�o�^���� false:�o�^���s
       */
      bool Register(const StageType& stage, std::string_view key);
      /**
       * @brief  �X�e�[�W�L�[�̎擾
       * @return �L�[���o�^����Ă���ꍇ�̓X�e�[�W�L�[��Ԃ�
       *         �X�e�[�W�^�C�v��Null�̏ꍇ�͋�̃L�[��Ԃ�
       */
      std::string StageKey() const;
      /**
       * @brief  ���݂̃X�e�[�W�^�C�v�̎擾
       * @return �X�e�[�W�^�C�v
       */
      StageType GetStageType() const {
        return _stageType;
      }
    protected:
      //!< �A�v���P�[�V�����̎Q��
      Application::ApplicationMain& _app;
      //!< �X�e�[�W�^�C�v
      StageType _stageType{StageType::Null};
      //!< �X�e�[�W�L�[���Ǘ�����A�z�z��
      std::unordered_map<StageType, std::string> _registry;
      /**
       * @brief  �X�e�[�W�̑J�ڏ���
       * @return true:�J�ڏI�� false:�J�ڌp��
       */
      bool Transition();
    };
  } // namespace Stage
} // namespace Gyro
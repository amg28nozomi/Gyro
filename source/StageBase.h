/*****************************************************************//**
 * @file   StageBase.h
 * @brief  �X�e�[�W�̃X�[�p�[�N���X
 * 
 * @author �y�� ����
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
      class ApplicationMain; //!< �O���錾
  } // namespace Application
  /**
   * @brief �X�e�[�W�x�[�X
   */
  namespace Object {
    namespace AppMath = AppFrame::Math;
    class SpawnBase; //!< �X�|�[�����
    /**
     * @class StageBase
     * @brief �X�e�[�W�̃X�[�p�[�N���X
     */
    class StageBase {
    public:
      /**
       * @brief �I�u�W�F�N�g���ʔԍ��̗񋓌^�N���X
       */
      enum class ObjectId {
          House,        //!< ��
          LongHouse,    //!< ����
          Board,        //!< ��
          Box,          //!< ��
          Tower         //!< ���v��
      };
      /**
       * @brief �X�e�[�W�̏�Ԃ�\���񋓌^�N���X
       */
      enum class StageState {
        Active, //!< �������
        Dead    //!< ���S���
      };
      /**
       * @brief �R���X�g���N�^
       * @param �A�v���P�[�V�����̎Q��
       */
      StageBase(Application::ApplicationMain& app);
      /**
       * @brief  ����������
       * @return true
       */
      virtual bool Init();
      /**
       * @brief  �X�V����
       * @return true
       */
      virtual bool Process();
      /**
       * @brief  �`�揈��
       * @return true
       */
      virtual bool Draw() const;
      /**
       * @brief �X�|�[�����̓ǂݎ��
       * @param spawn �X�|�[�����
       */
      virtual void Set(SpawnBase& spawn);
      /**
       * @brief  ��Ԃ̎擾
       * @return ���
       */
      StageState GetState() const {
          return _state;
      }
      /**
       * @brief  ���S��Ԃ��̔���
       * @return true:���S��� false:����ł��Ȃ�
       */
      virtual bool IsDead() const {
          return _state == StageState::Dead;
      }
      /**
       * @brief  ���[�J�����W�̎擾
       * @return ���[�J�����W
       */
      AppMath::Vector4 GetPosition() const {
          return _position;
      }
      /**
       * @brief  ��]�l�̎擾
       * @return ��]�l
       */
      AppMath::Vector4 GetRotation() const {
          return _rotation;
      }
      /**
       * @brief  �g�嗦�̎擾
       * @return �g�嗦
       */
      AppMath::Vector4 GetScale() const {
          return _scale;
      }
      /**
       * @brief  ���f���n���h���i�[�R���e�i�̎擾
       * @return ���f���n���h���i�[�R���e�i
       */
      std::vector<int> GetStageModel() {
          return _model;
      }
    protected:
      Application::ApplicationMain& _app;        //!< �A�v���P�[�V�����̎Q��
      StageState _state{ StageState::Active };   //!< ���
      AppFrame::Math::Vector4 _position;         //!< ���[�J�����W
      AppFrame::Math::Vector4 _rotation;         //!< ��](Debug:�f�O���[ Release:���W�A��)
      AppFrame::Math::Vector4 _scale{ 0, 0, 0 }; //!< �g�嗦
      std::vector<int> _model{ -1 }; //!< ���f���n���h���i�[�p�R���e�i
    };
  } // namespace Stage
} // namespace Gyro

/*****************************************************************//**
 * @file   ObjectBase.h
 * @brief  �I�u�W�F�N�g�̃X�[�p�[�N���X
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
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    class ApplicationMain; //!< �O���錾
  } // namespace Application
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    namespace AppMath = AppFrame::Math;
    /**
     * @class ObjectBase
     * @brief �I�u�W�F�N�g�̃X�[�p�[�N���X
     */
    class ObjectBase {
    public:
      /**
       * @brief �I�u�W�F�N�g���ʔԍ��̗񋓌^�N���X
       */
      enum class ObjectId {
        Object, //!< �I�u�W�F�N�g
        Player, //!< �v���C���[
        Enemy   //!< �G
      };
      /**
       * @brief �I�u�W�F�N�g�̏�Ԃ�\���񋓌^�N���X
       */
      enum class ObjectState {
        Active, //!< �������
        Paused, //!< ��~���
        Dead    //!< ���S���
      };
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      ObjectBase(Application::ApplicationMain& app);
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
       * @brief  ���ʔԍ��̎擾
       * @return ���ʔԍ�
       */
      ObjectId GetId() const {
        return _id;
      }
      /**
       * @brief  ��Ԃ̎擾
       * @return ���
       */
      ObjectState GetState() const {
        return _state;
      }
      /**
       * @brief  ���S��Ԃ��̔���
       * @return true:���S��� false:����ł��Ȃ�
       */
      virtual bool IsDead() const {
        return _state == ObjectState::Dead;
      }
      /**
       * @brief  ���[�J�����W�̎擾
       * @return ���[�J�����W
       */
      AppMath::Vector4 GetPosition() const {
        return _position;
      }
      /**
       * @brief  
       * @return 
       */
      AppMath::Vector4 GetRotation() const {
        return _rotation;
      }
      /**
       * @brief  �g�嗦�̎擾
       * @return 
       */
      AppMath::Vector4 GetScale() const {
        return _scale;
      }
    protected:
      Application::ApplicationMain& _app; //!< �A�v���P�[�V�����̎Q��
      ObjectId _id{ObjectId::Object}; //!< �I�u�W�F�N�g�̎��ʔԍ�
      ObjectState _state{ObjectState::Active}; //!< ���
      AppFrame::Math::Matrix44 _world;         //!< ���[���h���W
      AppFrame::Math::Vector4 _position;       //!< ���[�J�����W
      AppFrame::Math::Vector4 _rotation;       //!< ��](Debug:�f�O���[ Release:���W�A��)
      AppFrame::Math::Vector4 _scale{0, 0, 0}; //!< �g�嗦
      bool _stand{false};   //!< �����t���O(true:���ɗ����Ă��� false:���ƐڐG���Ă��Ȃ�)
      bool _gravity{false}; //!< �d�͏������s����(true:�d�͏������s�� false:�d�͏������s��Ȃ�)
      float _mass{0.0f};    //!< ����
      float _gravityScale{0.0f}; //!< �d�̓X�P�[��
      /**
       * @brief �I�u�W�F�N�g�ɑ΂���d�͏���
       */
      virtual void Gravity();
      /**
       * @brief  �d�̓X�P�[���̍X�V
       */
      virtual void GravityScale();
      /**
       * @brief  ���Ƃ̏Փ˔���
       *         �h���N���X�ŏd�͏������s���ꍇ�͕K���Ē�`���s������
       * @return true:�Փ˂��Ă��� false:�Փ˂��Ă��Ȃ�
       */
      virtual bool IsStand();
      /**
       * @brief  �d�͏����̃��Z�b�g
       */
      virtual void GravityReset();
      /**
       * @brief  ���[���h���W�̍X�V
       */
      void WorldMatrix();
#ifdef _DEBUG
      /**
       * @brief �f�o�b�O��p�̏o�͏���
       *        �A�v���P�[�V�����̃f�o�b�O�t���O��true�̏ꍇ�̂ݏ������s��
       */
      virtual bool DebugDraw() const;
#endif
    };
  } // namespace Object
} // namespace Gyro
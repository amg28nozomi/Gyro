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
    protected:
      Application::ApplicationMain& _app; //!< �A�v���P�[�V�����̎Q��
      ObjectId _id{ObjectId::Object}; //!< �I�u�W�F�N�g�̎��ʔԍ�
      ObjectState _state{ObjectState::Active}; //!< ���
      AppFrame::Math::Matrix44 _world;    //!< ���[���h���W�s��
      AppFrame::Math::Vector4 _position;  //!< ���W
      AppFrame::Math::Vector4 _rotation;  //!< ����
      AppFrame::Math::Vector4 _scale;     //!< �g�嗦
      bool _gravity; //!< �d�͏������s����(true:�d�͏������s�� false:�d�͏������s��Ȃ�)
      float _mass;   //!< ����
      //float _gravityScale; //!< �d�̓X�P�[��
      /**
       * @brief �I�u�W�F�N�g�ɑ΂���d�͏���
       */
      virtual void Gravity();
      /**
       * @brief ���[���h���W�̍X�V
       * @return
       */
      virtual bool WorldMatrixUpdate();
    };
  } // namespace Object
} // namespace Gyro
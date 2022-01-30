/*****************************************************************//**
 * @file   Player.h
 * @brief  �I�u�W�F�N�g�x�[�X�̃T�u�N���X
 *         ���@�̏������s��
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "ObjectBase.h"
#include "Camera.h"
#include "ModelAnim/ModelAnimComponent.h"

namespace AppFrame::Math{}

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �v���C���[�x�[�X
   */
  namespace Player {
    namespace AppMath = AppFrame::Math;
    /**
     * @class Player
     * @brief �I�u�W�F�N�g�x�[�X�̃T�u�N���X
     */
    class Player : public Object::ObjectBase {
    public:
      /**
       * @brief ���@�̏�Ԃ�\���񋓌^�N���X
       */
      enum class PlayerState {
        Idle,       //!< �ҋ@
        Walk,       //!< ����
        Run,        //!< �ړ�
        Attack1,    //!< �U��1
        Attack2,    //!< �U��2
        Attack3,    //!< �U��3
        Jump        //!< �W�����v
      };
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      Player(Application::ApplicationMain& app);
      /**
       * @brief  ����������
       * @return true
       */
      bool Init() override;
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
      AppFrame::Math::Vector4 _move{}; //!< �ړ���

      int _model;          //!< ���f���n���h��
      int _animaIndex;     //!< �A�^�b�`����Ă���A�j���ԍ�
      float _totalTime;    //!< �A�j���[�V�����̑��Đ�����
      float _animaTime;    //!< �A�j���[�V�����̍Đ�����
      Camera::Camera _cam; //!< �J�����̎���
      ModelAnim::ModelAnimComponent _modelAnim; //!< AnimComponent�̎���
      bool AttackFlug = false;
      int _cnt;

      PlayerState _playerState{PlayerState::Idle}; //!< ���@���
      int _handleMap;
      int _frameMapCollision;
      int _handleSkySphere;   //!< �X�J�C�X�t�B�A�n���h��
      /**
       * @brief ���͏���
       */
      void Input();
      /**
       * @brief ���\�[�X�̓ǂݎ�菈��
       */
      void LoadResource();
      /**
       * @brief ��Ԃ̐ݒ�
       */
      void SetState();
      /**
       * @brief �J�����̐ݒ�
       */
      void SetCamera();
      /**
       * @brief  �ړ��ʂ̎Z�o
       * @param  stick ���͒l
       * @return �ړ���
       */
      float Speed(const AppFrame::Math::Vector4 stick) const;
      /**
       * @brief  �ړ��ʂ̎Z�o
       */
      void Move(AppMath::Vector4 move);
      /**
       * @brief �J�����̍X�V
       * @param stick 
       */
      void CameraUpdate(const AppFrame::Math::Vector4 stick);
      /**
       * @brief �����̐ݒ�
       * @param move �ړ���
       */
      void SetRotation(const AppFrame::Math::Vector4 move);
      /**
       * @brief �A�j���[�V��������
       * @param old �O�t���[���̏��
       */
      void Animation(PlayerState old);
      /**
       * @brief �w�肵���A�j���[�V�����C���f�b�N�X�̎擾
       * @param key �A�j���[�V�����ɕR�Â���ꂽ������
       */
      int AnimaIndex(std::string_view key) const;
      /**
       * @brief �A�j���[�V�����̃A�^�b�`
       */
      bool AttachAnima(std::string_view key);
      /**
       * @brief ���݂̏�Ԃɉ������A�j���L�[��Ԃ�
       */
      std::string_view GetAnimaKey() const;
#ifdef _DEBUG
      /**
       * @brief Debug��p�`��
       */
      void DebugString() const;
#endif
    };
  }
    //} // namespace Player
} // namespace Gyro
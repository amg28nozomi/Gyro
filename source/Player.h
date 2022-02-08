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
#include "CollisionSphere.h"
#include "CollisionCapsule.h"
#include "GaugeHP.h"
#include "GaugeTrick.h"

namespace AppFrame::Math{}
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  namespace Object {
    class CollisionCapsule;
  }
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
      /**
       * @brief  �X�|�[�����̓ǂݎ��
       * @param  spawn �X�|�[�����
       */
      void Set(Object::SpawnBase& spawn) override;
    private:
      AppFrame::Math::Vector4 _move{}; //!< �ړ���

      int _model;          //!< ���f���n���h��
      int _animaIndex;     //!< �A�^�b�`����Ă���A�j���ԍ�
      float _totalTime;    //!< �A�j���[�V�����̑��Đ�����
      float _animaTime;    //!< �A�j���[�V�����̍Đ�����
      ModelAnim::ModelAnimComponent _modelAnim; //!< AnimComponent�̎���
      Gauge::GaugeHP _gaugeHp;       //!< HP�Q�[�W�̎���
      Gauge::GaugeTrick _gaugeTrick; //!< �g���b�N�Q�[�W�̎���
      std::unique_ptr<Object::CollisionSphere> _sphere;   //!< �����蔻��R���W����(��)
      std::unique_ptr<Object::CollisionCapsule> _capsule; //!< �J�v�Z��
      PlayerState _playerState{PlayerState::Idle};        //!< ���@���

      bool _attackFlugY = false; //!< ��U���t���O
      bool _attackFlugX = false; //!< ���U���t���O
      int _cnt;

      std::unique_ptr<AppMath::Plane> _plane; //!< ����
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
       */
      AppMath::Vector4 Move(AppMath::Vector4 move);
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
      bool DebugDraw() const override;

      /**
       * @brief Debug��p�`��
       */
      void DebugString() const;
#endif
      /**
       * @brief  �n�`�Ƃ̏Փ˔���
       * @return true:�Փ� false:�Փ˂��Ă��Ȃ�
       */
      bool IsStand() override;

      /**
       * @brief �Փ˔��菈��
       */
      void Hit();
      /**
       * @brief �W�����v����
       */
      void Jump();

      float _jumpPower{0.0f};    //!< �W�����v��
      float _jumpInterval{0.0f}; //!< �W�����v�C���^�[�o��
      bool _jump;                //!< �W�����v�t���O
    };
  }
    //} // namespace Player
} // namespace Gyro
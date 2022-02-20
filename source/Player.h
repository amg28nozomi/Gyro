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
#include "ModelAnimComponent.h"
#include "CollisionSphere.h"
#include "CollisionCapsule.h"
#include "GaugeHP.h"
#include "GaugeTrick.h"
#include "JumpComponent.h"
#include "MoveComponent.h"
#include "WireComponent.h"
#include "AttackComponent.h"
#include "InvincibleComponent.h"
#include "StateComponent.h"

namespace AppFrame::Math{}
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    class CollisionCapsule;
  } // namespace Object
  /**
   * @brief �v���C���[�x�[�X
   */
  namespace Player {
    namespace AppMath = AppFrame::Math;
    class JumpComponent; //!< 
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

      // ��
      int StageHandle() const {
        return _handleMap;
      }
      /**
       * @brief  �A�^�b�N�R���|�[�l���g�̎擾
       * @return �A�^�b�N�R���|�[�l���g�̎Q��
       */
      Object::AttackComponent& AttackComponent() const {
        return *_attack;
      }
      /**
       * @brief  ���f���L�[�̎擾
       * @return ���f���L�[
       */
      std::string_view ModelKey() const override {
        return _modelKey;
      }
    private:
      // AppFrame::Math::Vector4 _move{}; //!< �ړ���

      int _model;       //!< ���f���n���h��
      int _animaIndex;  //!< �A�^�b�`����Ă���A�j���ԍ�
      float _totalTime; //!< �A�j���[�V�����̑��Đ�����
      float _animaTime; //!< �A�j���[�V�����̍Đ�����
      ModelAnim::ModelAnimComponent _modelAnim; //!< AnimComponent�̎���
      Gauge::GaugeHP _gaugeHp;       //!< HP�Q�[�W�̎���
      Gauge::GaugeTrick _gaugeTrick; //!< �g���b�N�Q�[�W�̎���
      std::unique_ptr<Object::CollisionSphere> _sphere;   //!< �����蔻��R���W����(��)
      std::unique_ptr<Object::CollisionCapsule> _capsule; //!< �J�v�Z��
      PlayerState _playerState{PlayerState::Idle};        //!< ���@���
      PlayerState _oldState{ PlayerState::Idle };

      bool _attackFlag{false};   //!< �U���t���O(true:���U�� false:��U��)

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
       * @param  leftX ���X�e�B�b�N�̓��͏��(x��)
       * @param  leftY ���X�e�B�b�N�̓��͏��(y��)
       */
      AppMath::Vector4 Move(const float leftX, const float leftY);
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
       * @brief  
       * @param  state
       * @return 
       */
      bool State(const PlayerState& state) const {
        return _playerState == state;
      }
      /**
       * @brief �A�j���[�V��������
       * @param old �O�t���[���̏��
       */
      void Animation(PlayerState old);
      /**
       * @brief  ��Ԃ̐؂�ւ�����(���v���[����p)
       * @param  move XBOX�R���g���[���̓��͏�ԃN���X�̎Q��
       * @return true:�`�F���W false:�ύX�Ȃ�
       */
      bool StateChanege(const AppFrame::Application::XBoxState& input);
      /**
       * @brief ���[�V�����؂�ւ�
       */
      void Anime();
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
       * @brief �d�͏���
       */
      void GravityScale() override;
      /**
       * @brief  �n�`�Ƃ̏Փ˔���
       * @return true:�Փ� false:�Փ˂��Ă��Ȃ�
       */
      bool IsStand() override;
      /**
       * @brief  �����o������
       */
      void Extrude() override;
      /**
       * @brief �Փ˔��菈��
       */
      void Hit();
      /**
       * @brief �W�����v����
       */
      void Jump();
      /**
       * @brief ���C���[�A�N�V����
       */
      void Wire(AppMath::Vector4& move);
      /**
       * @brief  ��ԑJ��
       * @param  state �J�ڐ�̏��
       * @param  animName �A�j���[�V������
       */
      void ChangeState(const PlayerState& state, std::string_view animName);
      /**
       * @brief  �U������
       */
      void Attack();
      /**
       * @brief  �U����Ԃ��̔���
       * @return true:�U����� false:�U����Ԃł͂Ȃ�
       */
      bool IsAttackState() const;
      /**
       * @brief  �L�[�̐ݒ�
       * @return ���݂̏�ԂɑΉ�����W���C�p�b�h�L�[��Ԃ�
       *         �ŏI�R���{�̏ꍇ��-1��Ԃ�
       *         ����ȊO�̏ꍇ��-2��Ԃ�
       */
      int NextKey() const;
      /**
       * @brief  ��Ԃ̕ύX
       * @return true: false:
       */
      bool SetStateParam(PlayerState pState);
      /**
       * @brief  �����ԂɑJ�ڂ��邩�̔���
       * @param  move �ړ���
       * @return true:�J�ڂ��� false:�J�ڂ��Ȃ�
       */
      bool IsRun(const AppMath::Vector4& move);
      /**
       * @brief  �v���C���[��Ԃ𐔒l�ɕϊ�����
       * @return �v���C���[��ԂɑΉ�����
       */
      int PlayerStateToNumber() const;
      //!< ���f���T�[�o�ɕR�Â���ꂽ������
      static inline std::string _modelKey{"player"};
      //!< �W�����v�R���|�[�l���g
      std::unique_ptr<JumpComponent> _jump;
      //!< ���[�u�R���|�[�l���g
      std::unique_ptr<Object::MoveComponent> _move;
      //!< ���C���[�R���|�[�l���g
      std::unique_ptr<WireComponent> _wire;
      //!< �A�^�b�N�R���|�[�l���g
      std::unique_ptr<Object::AttackComponent> _attack;
      //!< �C���r�W�u���R���|�[�l���g
      std::unique_ptr<Object::InvincibleComponent> _invincible;
      //!< �X�e�[�g�R���|�[�l���g
      std::unique_ptr<Object::StateComponent> _stateComponent;
      //!< �A�j���[�V��������ێ����镶����
      std::string _animationKey;
      //!< �d�̓��Z�b�g����
      bool _gravityReset{false};
    };
  } // namespace Player
} // namespace Gyro
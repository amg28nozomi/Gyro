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
#include "KnockBackComponent.h"
#include "MoveComponent.h"
#include "WireComponent.h"
#include "AttackComponent.h"
#include "InvincibleComponent.h"
#include "StateComponent.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �G�l�~�[�N���X
   */
  namespace Enemy {
    class EnemyBase;
  }
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    class CollisionCapsule; //!< �O���錾
  } // namespace Object
  /**
   * @brief �v���C���[�x�[�X
   */
  namespace Player {
    /**
     * @brief ���O��Ԃ̏ȗ�
     */
    namespace AppMath = AppFrame::Math;
    constexpr auto DefaultRadius = 30.0f; //!< �f�t�H���g�̔��a
    class JumpComponent; //!< �W�����v�R���|�[�l���g
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
        Idle,        //!< �ҋ@
        Walk,        //!< ����
        Run,         //!< �ړ�
        Attack1,     //!< �U��1
        Attack2,     //!< �U��2
        Attack3,     //!< �U��3
        ExciteTrick, //!< �G�L�T�C�g�g���b�N
        Jump         //!< �W�����v
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
      /**
       * @brief  �X�e�[�W�n���h���̎擾
       * @return �X�e�[�W�n���h��
       */
      int StageHandle() const {
        return _handleMap;
      }
      /**
       * @brief  �Q�[���I�[�o�[�̎擾
       * @return �Q�[���I�[�o�[
       */
      bool GetGameOver() const {
        return _gameOver;
      }
      /**
       * @brief  �w�肵���t���[���̃��[���h���W���擾
       * @param  frame �t���[���ԍ�
       * @return �擾�ɐ��������ꍇ�̓��[���h���W��Ԃ�
       *         ���s�����ꍇ�͋�̃x�N�g����Ԃ�
       */
      AppMath::Vector4 GetFramePosition(int frame) override;
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
      //!< ���f���n���h��
      int _model;
      //!< �����E�_�b�V�����[�V�����̍Đ����x
      float _animSpeed;
      int _playerHP{ 0 };  //!< ���@�̗�
      //!< AnimComponent
      ModelAnim::ModelAnimComponent _modelAnim;
      //!< HP�Q�[�W
      Gauge::GaugeHP _gaugeHp;
      //!< �g���b�N�Q�[�W
      Gauge::GaugeTrick _gaugeTrick;
      //!< �����蔻��R���W����(��)
      std::unique_ptr<Object::CollisionSphere> _sphere;
      //!< �����蔻��R���W����(�J�v�Z��)
      std::unique_ptr<Object::CollisionCapsule> _capsule;
      //!< ���@���
      PlayerState _playerState{PlayerState::Idle};
      //!< �O�t���[�����
      PlayerState _oldState{ PlayerState::Idle };
      //!< �O���x�N�g��
      AppMath::Vector4 _forward{};
      //!< �U���t���O(true:���U�� false:��U��)
      bool _attackFlag{false};
      //!< ����
      std::unique_ptr<AppMath::Plane> _plane;
      int _handleMap;
      int _frameMapCollision;
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
#ifdef _DEBUG
      /**
       * @brief  �f�o�b�O��p�̕`�揈��
       * @return true: false:
       */
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
       * @brief �_���[�W����
       */
      void IsDamage();
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
      /**
       * @brief  �R���W�����𐶐�����
       * @param  num    �������鐔
       * @param  radius ���a
       * @return �R���W������񂪊i�[���ꂽ���I�z��
       */
      std::vector<std::shared_ptr<Object::CollisionBase>> AddSpheres(const int num, float daius = DefaultRadius);
    private:
      //!< ���f���T�[�o�ɕR�Â���ꂽ������
      static inline std::string _modelKey{"player"};
      //!< �W�����v�R���|�[�l���g
      std::unique_ptr<JumpComponent> _jump;
      //!< �m�b�N�o�b�N�R���|�[�l���g
      std::unique_ptr<Object::KnockBackComponent> _knockBack;
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
      //!< �Q�[���I�[�o�[
      bool _gameOver{ false };
    };
  } // namespace Player
} // namespace Gyro
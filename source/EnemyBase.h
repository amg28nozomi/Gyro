/*****************************************************************//**
 * @file    EnemyBase.h
 * @brief   �G�̊��N���X
 *
 * @author  �{�V�s��
 * @date    January 2022
 *********************************************************************/
#pragma once
#include "ApplicationMain.h"
#include "ObjectBase.h"
#include "InvincibleComponent.h"
#include "CollisionSphere.h"
#include "CollisionCapsule.h"
#include "GaugeEnemy.h"
#include "ModelAnimComponent.h"

 /**
  * @brief �Q�[���x�[�X
  */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    class CollisionCapsule;
    class SpawnEnemy;
  } // namespace Object
  /**
   * @brief �G�x�[�X
   */
  namespace Enemy {
    /**
     * @class EnemyBase
     * @brief �G�̊��N���X
     */
    class EnemyBase : public Object::ObjectBase {
    public:
      /**
       * @enum class  EnemyState
       * @brief  �G�̏�ԑJ�ڗp�萔
       */
      enum class EnemyState {
        Idle,        //!< �ҋ@
        Move,        //!< �ړ�
        AttackReady, //!< �U������
        Attack,      //!< �U��
        Damage,      //!< ��_��
        Dead         //!< ���S
      };
      /**
       * @brief  �R���X�g���N�^
       */
      EnemyBase(Application::ApplicationMain& app);
      /**
       * @brief  �f�X�g���N�^
       */
      virtual ~EnemyBase();
      /**
       * @brief  ������
       */
      virtual bool Init();
      /**
       * @brief  �X�V
       */
      virtual bool Process();
      /**
       * @brief  �`��
       */
      bool Draw() const override;
      /**
       * @brief  �X�|�[�����̓ǂݎ��
       * @param  �X�|�[�����̎Q��
       */
      void Set(Object::SpawnEnemy& spawn);
      /**
       * @brief  ���̓����蔻��̎擾
       * @return ���̓����蔻��
       */
      Object::CollisionSphere& GetCollision() {
        return *_sphere;
      }
      /**
       * @brief  �J�v�Z���̓����蔻��̎擾
       * @return �J�v�Z���̓����蔻��
       */
      Object::CollisionCapsule& GetCapsule() {
        return *_capsule;
      }
      /**
       * @brief  ���G�����̎Q�Ƃ��擾
       * @return ���G�����̎Q��
       */
      virtual Object::InvincibleComponent& GetInvincibleComponent() {
        return *_invincible;
      }

      virtual unsigned short GetThis() const {
        return 0;
      }
      /**
       * @brief  �ΏۂƎ��g������I�u�W�F�N�g���̔���
       * @param  handle �n���h��
       * @return true:��v
       *         false:�s��v
       */
      inline bool Equals(const int handle) const {
        return _mHandle == handle;
      }
      /**
       * @brief  ��Ԃ̎擾
       * @return ���
       */
      EnemyState GetEnemyState() const {
        return _enemyState;
      }
    protected:
      /**
       * @brief  ���f���̓ǂݍ���
       */
      virtual void LoadModel();
      /**
       * @brief  �p�����[�^�̐ݒ�
       */
      virtual void SetParameter();
      /**
       * @brief  �����蔻����̐ݒ�
       */
      virtual void SetCollision();
      /**
       * @brief  �ړ�����
       */
      virtual void Move();
      /**
       * @brief  �U������
       */
      virtual void Attack();
      /**
       * @brief  �m�b�N�o�b�N����
       * @author �y������
       */
      virtual void NockBack();
      /**
       * @brief  �T������
       * @author �y������
       */
      virtual void Search();
      /**
       * @brief  �Փˏ���
       */
      virtual void Hit();
      /**
       * @brief  �A�j���[�V�����؂�ւ�
       */
      virtual void ChangeAnim();
      /**
       * @brief  �G�t�F�N�g�Đ�
       */
      virtual void PlayEffect();
      /**
       * @brief  �I�u�W�F�N�g�̎��S����
       */
      virtual void Dead();
      /**
       * @brief  �_���[�W���󂯂����̔���
       * @return true:�Փ� false:�_���[�W����
       */
      virtual bool IsDamege();
      /**
       * @brief  Process���s�������肷��
       * @return true:Process���s�� false:Process���s��Ȃ�
       */
      virtual bool ProcessFlag();
      /**
       * @brief  �n�`�Ƃ̏Փ˔���
       * @return true:���ɗ����Ă���
       *         false:���ɗ����Ă��Ȃ�
       */
      bool IsStand() override;
      /**
       * @brief  ��ԑJ�ڂ�����
       * @param  �O�̏��
       * @return true:��ԑJ�ڂ���
       *         false:��ԑJ�ڂȂ�
       */
      bool IsChangeState(const EnemyState old) {
        return old != _enemyState;
      }

      int _cnt{ 0 };        //!< �J�E���g
      int _mHandle{ -1 };   //!< ���f���n���h��
      int _enemyHP{ 0 };    //!< �G�̗�
      float _serchRadius{ 0.0f };  //!< ���G�͈�(�~)�̔��a
      float _attackRadius{ 0.0f }; //!< �U���͈�(�~)�̔��a
      float _flagRadius{ 700.0f }; //!< Process���s�����ǂ���
       //!< ���̓����蔻��
      std::unique_ptr<Object::CollisionSphere> _sphere{ nullptr };
      //!< �J�v�Z�������蔻��
      std::unique_ptr<Object::CollisionCapsule> _capsule{ nullptr };
      //!< ���G�R���|�[�l���g
      std::unique_ptr<Object::InvincibleComponent> _invincible{ nullptr };
      //!< �G�̏�ԕێ��ϐ�
      EnemyState _enemyState;
      //!< �̗̓Q�[�W
      std::shared_ptr<Gauge::GaugeEnemy> _gaugeHp{ nullptr };
      //!< ���f���A�j��
      ModelAnim::ModelAnimComponent _modelAnim;
    };
  } // namespace Enemy
} // namespace Gyro
/*****************************************************************//**
 * @file    EnemyBase.h
 * @brief   �G�̊��N���X
 *
 * @author  �{�V�s��
 * @date    January 2022
 *********************************************************************/
#pragma once
#include "../ObjectBase.h"
#include "../ModelAnim/ModelAnimComponent.h"
#include "../CollisionSphere.h"
#include "../CollisionCapsule.h"
#include "../InvincibleComponent.h"


 /** ��i�p���O��� */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    class CollisionCapsule;
    class SpawnEnemy;
  } // namespace Object
    /** �G�p���O��� */
    namespace Enemy {
        /**
         * @class EnemyBase
         * @brief �G�̊��N���X
         */
        class EnemyBase : public Object::ObjectBase {
        public:
            /**
             * @brief   �R���X�g���N�^
             */
            EnemyBase(Application::ApplicationMain& app);
            /**
             * @brief   �f�X�g���N�^
             */
            virtual ~EnemyBase();
            /**
             * @brief   ������
             */
            virtual bool Init();
            /**
             * @brief   �X�V
             */
            virtual bool Process();
            /**
             * @brief   �`��
             */
            bool Draw() const override;
            /**
             * @brief  �X�|�[�����̓ǂݎ��
             * @param  �X�|�[�����̎Q��
             */
            void Set(Object::SpawnEnemy& spawn);

            Object::CollisionSphere& GetCollision() {
              return *_sphere;
            }

            Object::CollisionCapsule& GetCapsule() {
              return *_capsule;
            }

            virtual unsigned short GetThis() const {
              return 0;
            }
            /**
             * @brief  ���G�����̎Q�Ƃ��擾
             * @return ���G�����̎Q��
             */
            virtual Object::InvincibleComponent& GetInvincibleComponent() {
              return *_invincible;
            }
            /**
             * @brief  �ΏۂƎ��g������I�u�W�F�N�g���̔���
             * @param  handle �n���h��
             * @return true:��v false:�s��v
             */
            inline bool Equals(const int handle) const {
              return _mHandle == handle;
            }
        protected:
            /**
             * @enum class  EnemyState
             * @brief   �G�̏�ԑJ�ڗp�萔
             */
            enum class EnemyState {
                Idle,   //!<�ҋ@
                Move,   //!<�ړ�
                Attack, //!<�U��
                Dead    //!<���S
            };

            int _mHandle;           //!< ���f���n���h��
            float _enemyMoveSpeed;  //!< �G�ړ����x
            std::unique_ptr<Object::CollisionSphere> _sphere{nullptr}; //!< ���̓����蔻��
            //!< �J�v�Z�������蔻��
            std::unique_ptr<Object::CollisionCapsule> _capsule{ nullptr }; //!< �J�v�Z���̓����蔻��
            //!< ���G�R���|�[�l���g
            std::unique_ptr<Object::InvincibleComponent> _invincible{nullptr};
            EnemyState _enemyState; //!< �G�̏�ԕێ��ϐ�
            ModelAnim::ModelAnimComponent _modelAnim;
            /**
             * @brief �����蔻����̐ݒ�
             */
            virtual void SetCollision();
            /**
             * @brief  �n�`�Ƃ̏Փ˔���
             * @return 
             */
            bool IsStand() override;
            /**
             * @brief  �I�u�W�F�N�g�̎��S����
             */
            virtual void Dead();
        };
    } // namespace Enemy
} // namespace Gyro
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
#include "../Effect/SampleEffect.h"

 /** ��i�p���O��� */
namespace Gyro {
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
             * @brief   �G�ʒu�̐ݒ�
             * @param   vPos �G�ʒu
             */
            virtual void SetEnemyPos(const VECTOR vPos) {
                _enemyPos = vPos;
            }
            /**
             * @brief   �G�ړ���̐ݒ�
             * @param   vTarget �G�ړ���
             */
            virtual void SetEnemyTarget(const VECTOR vTarget) {
                _enemyTarget = vTarget;
            }

            Object::CollisionSphere& GetCollision() {
              return *_sphere;
            }
        protected:
            /**
             * @enum class  EnemyState
             * @brief   �G�̏�ԑJ�ڗp�萔
             */
            enum class EnemyState {
                WAIT,   //!<�҂�
                WALK,   //!<����
                ATTACK, //!<�U��
                DEAD    //!<���S
            };

            int _mHandle;           //!< ���f���n���h��
            float _enemyMoveSpeed;  //!< �G�ړ����x
            VECTOR _enemyPos;       //!< �G�ʒu
            VECTOR _enemyDir;       //!< �G����
            VECTOR _enemyTarget;    //!< �G�ړ���
            std::unique_ptr<Object::CollisionSphere> _sphere{nullptr}; //!< ���̓����蔻��

            EnemyState _enemyState; //!< �G�̏�ԕێ��ϐ�
            ModelAnim::ModelAnimComponent _modelAnim;
            Effect::SampleEffect _eff;
        };
    } // namespace Enemy
} // namespace Gyro
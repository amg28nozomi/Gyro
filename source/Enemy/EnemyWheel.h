/*****************************************************************//**
 * @file    EnemyWheel.h
 * @brief   �G�N���X
 *
 * @author  �{�V�s��
 * @date    January 2022
 *********************************************************************/
#pragma once
#include "EnemyBase.h"

 /** ��i�p���O��� */
namespace Gyro {
    /** �G�p���O��� */
    namespace Enemy {
        /**
         * @class EnemyWheel
         * @brief �G�N���X
         */
        class EnemyWheel : public EnemyBase {
        public:
            /**
             * @brief   �R���X�g���N�^
             */
            EnemyWheel(Application::ApplicationMain& app);
            /**
             * @brief   �f�X�g���N�^
             */
            ~EnemyWheel();
            /**
             * @brief   ������
             */
            bool Init() override;
            /**
             * @brief   �X�V
             */
            bool Process() override;
            /**
             * @brief  �`�攻��
             * @return 
             */
            bool Draw() const override;

            unsigned short GetThis() const override {
              return _this;
            }
        private:
          static inline unsigned short _number{0}; //!< �����ԍ�
          unsigned short _this{0}; //!< ����ID
          bool _iMove{false}; //!< �ړ��t���O
          /**
           * @brief  �����蔻��̐ݒ菈��
           * @author ��؊�C
           */
          void SetCollision() override;

          void Hit();
        };
    } // namespace Enemy
} // namespace Gyro
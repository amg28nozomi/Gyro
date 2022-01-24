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

        private:

        };
    } // namespace Enemy
} // namespace Gyro
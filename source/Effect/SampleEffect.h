/*****************************************************************//**
 * @file   SampleEffect.h
 * @brief  �������G�t�F�N�g�N���X
 *
 * @author �{�V�s��
 * @date   January 2021
 *********************************************************************/
#pragma once
#include "EffectBase.h"

 /** ��i�p���O��� */
namespace Gyro {
    /** �G�t�F�N�g�p���O��� */
    namespace Effect {
        /**
         * @class SampleEffect
         * @brief �������G�t�F�N�g�N���X
         */
        class SampleEffect : public EffectBase {
        public:
            /**
             * @brief     �R���X�g���N�^
             */
            SampleEffect();
            /**
             * @brief     �f�X�g���N�^
             */
            ~SampleEffect() override;
            /**
             * @brief     ������
             */
            void Init() override;
            /**
             * @brief   �X�V
             */
            void Process() override;
            /**
             * @brief   �`��
             */
            void Draw() override;

        };
    } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file   EffectBase.h
 * @brief  �G�t�F�N�g�̊��N���X
 *
 * @author �{�V�s��
 * @date   January 2021
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "../ApplicationMain.h"

 /** ��i�p���O��� */
namespace Gyro {
    /** �G�p�G�t�F�N�g�p���O��� */
    namespace Effect {
        /**
         * @class EffecBase
         * @brief �G�̊��N���X
         */
        class EffectBase {
        public:
            /**
             * @brief   �R���X�g���N�^
             */
            EffectBase();
            /**
             * @brief   �f�X�g���N�^
             */
            virtual ~EffectBase();
            /**
             * @brief   ������
             */
            virtual void Init();
            /**
             * @brief   �X�V
             */
            virtual void Process();
            /**
             * @brief   �`��
             */
            virtual void Draw();
            /**
             * @brief   �G�t�F�N�g���Đ�����
             */
            void PlayEffect();
            /**
             * @brief   �G�t�F�N�g�ʒu�ݒ�
             * @param   vPos �G�t�F�N�g�ʒu
             */
            void SetPosition(const VECTOR& position) {
                _ePos = position;
            }
            /**
             * @brief   �G�t�F�N�g�����ݒ�
             * @param   vDir �G�t�F�N�g����
             */
            void SetDirection(const VECTOR& direction) {
                _eDir = direction;
            }

        protected:
            /**
             * @brief   �G�t�F�N�g�̍Đ�����
             * @return  true:�G�t�F�N�g�Đ���
             *          false:�G�t�F�N�g���Đ�(�܂��͍Đ��I��)
             */
            bool IsEffectPlaying() {
                return IsEffekseer3DEffectPlaying(_playEff) == 0;
            }

            int _eHandle;   //<! �G�t�F�N�g�n���h��
            int _playEff;   //<! �Đ����̃G�t�F�N�g
            float _eMagni;  //<! �G�t�F�N�g�g�嗦
            float _eSpeed;  //<! �G�t�F�N�g�Đ����x
            VECTOR _ePos;   //<! �G�t�F�N�g�ʒu
            VECTOR _eDir;   //<! �G�t�F�N�g����
        };
    } // namespace Effect
} // namespace Gyro
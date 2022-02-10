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
    /** �A�v���P�[�V�����p���O��� */
    namespace Application {
        class ApplicationMain; //!< �O���錾
    } // namespace Application

    /** �G�p�G�t�F�N�g�p���O��� */
    namespace Effect {
        namespace AppMath = AppFrame::Math;
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
            virtual void Draw() const;
            /**
             * @brief   �G�t�F�N�g���Đ�����
             */
            void PlayEffect();
            /**
             * @brief   �G�t�F�N�g�ʒu�ݒ�
             * @param   position �G�t�F�N�g�ʒu
             */
            void SetPosition(const AppMath::Vector4 position) {
                _ePos = position;
            }
            /**
             * @brief   �G�t�F�N�g�����ݒ�
             * @param   rotation �G�t�F�N�g����
             */
            void SetDirection(const float radian) {
                _eRot.SetY(radian);
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
            float _eScale;  //<! �G�t�F�N�g�g�嗦
            float _eSpeed;  //<! �G�t�F�N�g�Đ����x
            AppMath::Vector4 _ePos;   //<! �G�t�F�N�g�ʒu
            AppMath::Vector4 _eRot;   //<! �G�t�F�N�g����
        };
    } // namespace Effect
} // namespace Gyro
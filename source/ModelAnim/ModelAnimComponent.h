/*****************************************************************//**
 * @file    ModelAnimComponent.h
 * @brief   ���f���A�j���N���X
 *
 * @author  �{�V�s��
 * @date    December 2021
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "../ModelAnim/ModelAnimInfo.h"

 /** ��i�p���O��� */
namespace Gyro {
    /** ���f���A�j���p���O��� */
    namespace ModelAnim {
        /**
         * @class ModelAnimComponent
         * @brief ���f���A�j���N���X
         */
        class ModelAnimComponent {
        public:
            /**
             * @brief   �R���X�g���N�^
             */
            ModelAnimComponent();
            /**
             * @brief   �f�X�g���N�^
             */
            ~ModelAnimComponent();
            /**
             * @brief   ������
             */
            void Init();
            /**
             * @brief   �X�V
             */
            void Process();
            /**
             * @brief   ���C���A�j���[�V�����A�^�b�`
             * @param   handle ���f���n���h��
             * @param   animNum �A�j���[�V�����ԍ�
             * @param   speed �A�j���[�V�����Đ����x
             * @param   loop ���[�v�Đ��L��
             */
            void SetMainAttach(const int handle, const int animNum, const float speed, const bool loop);
            /**
             * @brief   �u�����h�A�j���[�V�����A�^�b�`
             * @param   animNum �A�j���[�V�����ԍ�
             * @param   frame �u�����h�t���[��
             * @param   speed �A�j���[�V�����Đ����x
             * @param   loop ���[�v�Đ��L��
             */
            void SetBlendAttach(const int animNum, const float frame, const float speed, const bool loop);

        private:
            /**
             * @brief   �A�j���[�V�����A�^�b�`
             * @param   info ���f�����
             * @param   animNum �A�j���[�V�����ԍ�
             * @param   speed �A�j���[�V�����Đ����x
             * @param   loop ���[�v�Đ��L��
             */
            void SetAttach(ModelAnimInfo& info, const int animNum, const float speed, const bool loop);
            /**
             * @brief   �A�j���[�V�����f�^�b�`
             * @param   info ���f�����
             */
            void SetDetach(ModelAnimInfo& info);
            /**
             * @brief   �A�j���[�V�����Đ�
             * @param   info ���f�����
             */
            void PlayAnim(ModelAnimInfo& info);
            /**
             * @brief   �A�j���[�V�����u�����h
             */
            void AnimBlend();
            /**
             * @brief   ���f���̖��A�^�b�`����
             * @param   info ���f�����
             * @return  true:�A�j���[�V�������o�^
             *          false:�A�j���[�V�����o�^�ς�
             */
            bool IsNotAttachIndex(ModelAnimInfo& info) const {
                return info.GetAttachIndex() == -1;
            }
            /**
             * @brief   �����̃��f���̖��A�^�b�`����
             * @return  true:�ǂ��炩(�܂��͗���)�A�j���[�V�������o�^
             *          false:�ǂ�����A�j���[�V�����o�^�ς�
             */
            bool EitherIsNotAttachIndex() const {
                return _main.GetAttachIndex() == -1 || _blend.GetAttachIndex() == -1;
            }

            int _mHandle;       //!< ���f���n���h��
            int _blendCnt;      //!< �u�����h�J�E���g
            float _blendFrame;  //!< �u�����h�t���[��

            ModelAnimInfo _main;   //!< ���݂̃��f�����
            ModelAnimInfo _blend;  //!< �؂�ւ�郂�f�����
        };
    } // namespace ModelAnim
} // namespace Gyro
/*****************************************************************//**
 * @file    ModelAnimComponent.cpp
 * @brief   ���f���A�j���N���X
 *
 * @author  �{�V�s��
 * @date    December 2021
 *********************************************************************/
#include "../ModelAnim/ModelAnimComponent.h"

namespace Gyro {
    namespace ModelAnim {
        ModelAnimComponent::ModelAnimComponent() {
            // ������
            Init();
        }

        ModelAnimComponent::~ModelAnimComponent() {
            // �A�j���[�V�����f�^�b�`
            SetDetach(_main);
            SetDetach(_blend);
        }

        void ModelAnimComponent::Init() {
            // ������
            _mHandle = -1;
            _blendCnt = 0;
            _blendFrame = 0.0f;
        }

        void ModelAnimComponent::Process() {
            // �A�j���[�V�����Đ�
            PlayAnim(_main);
            PlayAnim(_blend);

            // �A�j���[�V�����u�����h
            AnimBlend();
        }

        void ModelAnimComponent::SetMainAttach(const int handle, std::string_view key, const float speed, const bool loop) {
            // �A�^�b�`�ς̏ꍇ���f
            if (IsAttachIndex(_main)) {
                return;
            }
            // ���f���n���h���ݒ�
            _mHandle = handle;
            // �A�j���[�V�����A�^�b�`
            SetAttach(_main, key, speed, loop);
        }

        void ModelAnimComponent::SetBlendAttach(std::string_view key, const float flame, const float speed, const bool loop) {
            // �A�^�b�`�ς̏ꍇ���f
            if (IsAttachIndex(_blend)) {
                return;
            }
            // �A�j���[�V�����A�^�b�`
            SetAttach(_blend, key, speed, loop);
            // �e��ݒ�
            _blendCnt = 0;
            _blendFrame = flame;
        }

        void ModelAnimComponent::SetAttach(ModelAnimInfo& motion, std::string_view key, const float speed, const bool loop) {
            // ���f���n���h���������̏ꍇ�G���[
            if (_mHandle == -1) {
#ifdef _DEBUG
                throw ("�A�j���[�V�������郂�f���n���h���̎擾�Ɏ��s���܂���\n");
                // ���f���n���h��������ɓǂݍ��߂Ă��Ȃ�
                // SetMainAttach()���g�킸��SetBlendAttach()���g����
#endif
                return;
            }
            // �A�j���[�V�����ԍ��̎擾
            int animNum = MV1GetAnimIndex(_mHandle, key.data());
            // �A�j���[�V�����ԍ��擾���s�̏ꍇ�G���[
            if (animNum == -1) {
#ifdef _DEBUG
                throw ("�A�j���[�V�����ԍ��̎擾�Ɏ��s���܂���\n");
                // ���f���n���h��������ɓǂݍ��߂Ă��Ȃ�
                // �A�j���[�V�������ɑ��Ⴊ����Ȃǂ���key������ɓǂݍ��߂Ă��Ȃ�
#endif
                return;
            }
            // �A�j���[�V�����A�^�b�`
            int index = MV1AttachAnim(_mHandle, animNum);
            // �e��ݒ�
            motion.SetAnimNum(animNum);
            motion.SetAttachIndex(index);
            motion.SetTotalTime(MV1GetAnimTotalTime(_mHandle, animNum));
            motion.SetPlaySpeed(speed);
            motion.SetAnimLoop(loop);
        }

        void ModelAnimComponent::SetDetach(ModelAnimInfo& motion) {
            // ���A�^�b�`�̏ꍇ���f
            if (!IsAttachIndex(motion)) {
                return;
            }
            // �A�j���[�V�����f�^�b�`
            MV1DetachAnim(_mHandle, motion.GetAttachIndex());
            // ��񏉊���
            motion.Reset();
        }

        void ModelAnimComponent::PlayAnim(ModelAnimInfo& motion) {
            // ���A�^�b�`�̏ꍇ���f
            if (!IsAttachIndex(motion)) {
                return;
            }
            // �A�j���[�V�����Đ�
            MV1SetAttachAnimTime(_mHandle, motion.GetAttachIndex(), motion.GetPlayTime());
            // �Đ����ԃJ�E���g
            motion.CountPlayTime();
        }

        void ModelAnimComponent::AnimBlend() {
            // �ǂ��炩���A�^�b�`�̏ꍇ���f
            if (!BothIsAttachIndex()) {
                return;
            }
            // �u�����h���Z�o
            float blendRate = static_cast<float>(_blendCnt) / _blendFrame;
            // �A�j���[�V�����u�����h
            MV1SetAttachAnimBlendRate(_mHandle, _main.GetAttachIndex(), 1.0f - blendRate);
            MV1SetAttachAnimBlendRate(_mHandle, _blend.GetAttachIndex(), blendRate);
            // �u�����h�J�E���g��i�߂�
            _blendCnt++;

            // �w��̃u�����h�t���[�����߂�����
            if (_blendFrame < _blendCnt) {
                // _main�̔j��
                SetDetach(_main);
                // _blend�̃A�j���[�V������_main�Ɉڂ�
                _main = _blend;
                // �u�����h�t���[�����i�߂�
                _main.SetPlayTime(_blendFrame);
                // _blend�̏�񏉊���
                _blend.Reset();
            }
        }
    } // namespace ModelAnim
} // namespace Gyro
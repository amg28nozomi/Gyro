/*****************************************************************//**
 * @file    MotionInfo.cpp
 * @brief   ���f���A�j�����N���X
 *
 * @author  �{�V�s��
 * @date    December 2021
 *********************************************************************/
#include "ModelAnimInfo.h"

namespace Gyro {
    namespace ModelAnim {
        ModelAnimInfo::ModelAnimInfo() {
            Reset();
        }

        ModelAnimInfo::~ModelAnimInfo() {

        }

        void ModelAnimInfo::Reset() {
            // ��񏉊���
            _animNum = -1;
            _attachIndex = -1;
            _totalTime = 0.0f;
            _playTime = 0.0f;
            _playSpeed = 0.0f;
            _motionLoop = false;
            _animEnd = false;
        }

        void ModelAnimInfo::CountPlayTime() {
            // ���x���Đ����Ԃ�i�߂�
            _playTime += _playSpeed;
            // �����Ԃ��߂�����
            if (_totalTime < _playTime) {
                // ���[�v�Đ��̗L������
                // �J��Ԃ� : �I��(��~)
                _playTime = _motionLoop ? 0.0f : _totalTime;
                _animEnd = _motionLoop ? false : true;
            }
        }
    } // namespace ModelAnim
} // namespace Gyro
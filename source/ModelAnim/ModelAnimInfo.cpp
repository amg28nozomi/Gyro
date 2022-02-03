/*****************************************************************//**
 * @file    MotionInfo.cpp
 * @brief   モデルアニメ情報クラス
 *
 * @author  宮澤耀生
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
            // 情報初期化
            _animNum = -1;
            _attachIndex = -1;
            _totalTime = 0.0f;
            _playTime = 0.0f;
            _playSpeed = 0.0f;
            _motionLoop = false;
            _animEnd = false;
        }

        void ModelAnimInfo::CountPlayTime() {
            // 速度分再生時間を進める
            _playTime += _playSpeed;
            // 総時間を過ぎたら
            if (_totalTime < _playTime) {
                // ループ再生の有無判定
                // 繰り返し : 終了(停止)
                _playTime = _motionLoop ? 0.0f : _totalTime;
                _animEnd = _motionLoop ? false : true;
            }
        }
    } // namespace ModelAnim
} // namespace Gyro
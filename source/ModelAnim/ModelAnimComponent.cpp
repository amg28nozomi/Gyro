/*****************************************************************//**
 * @file    ModelAnimComponent.cpp
 * @brief   モデルアニメクラス
 *
 * @author  宮澤耀生
 * @date    December 2021
 *********************************************************************/
#include "ModelAnimComponent.h"

namespace Gyro {
    namespace ModelAnim {
        ModelAnimComponent::ModelAnimComponent() {
            // 初期化
            Init();
        }

        ModelAnimComponent::~ModelAnimComponent() {
            // アニメーションデタッチ
            SetDetach(_main);
            SetDetach(_blend);
        }

        void ModelAnimComponent::Init() {
            // 初期化
            _mHandle = -1;
            _blendCnt = 0;
            _blendFrame = 0.0f;
        }

        void ModelAnimComponent::Process() {
            // アニメーション再生
            PlayAnim(_main);
            PlayAnim(_blend);

            // アニメーションブレンド
            AnimBlend();
        }

        void ModelAnimComponent::SetMainAttach(const int handle, const int animNum, const float speed, const bool loop) {
            // アタッチ済の場合デタッチする
            if (!IsNotAttachIndex(_main)) {
                SetDetach(_main);
            }
            // モデルハンドル設定
            _mHandle = handle;
            // アニメーションアタッチ
            SetAttach(_main, animNum, speed, loop);
        }

        void ModelAnimComponent::SetBlendAttach(const int animNum, const float flame, const float speed, const bool loop) {
            // アタッチ済の場合デタッチする
            if (!IsNotAttachIndex(_blend)) {
                SetDetach(_blend);
            }
            // アニメーションアタッチ
            SetAttach(_blend, animNum, speed, loop);
            // 各種設定
            _blendCnt = 0;
            _blendFrame = flame;
        }

        void ModelAnimComponent::SetAttach(ModelAnimInfo& motion, const int animNum, const float speed, const bool loop) {
            // モデルハンドル未所持の場合中断
            if (_mHandle == -1) {
                return;
            }
            // アニメーションアタッチ
            int index = MV1AttachAnim(_mHandle, animNum);
            // 各種設定
            motion.SetAnimNum(animNum);
            motion.SetAttachIndex(index);
            motion.SetTotalTime(MV1GetAnimTotalTime(_mHandle, animNum));
            motion.SetPlaySpeed(speed);
            motion.SetMotionLoop(loop);
        }

        void ModelAnimComponent::SetDetach(ModelAnimInfo& motion) {
            // 未アタッチの場合中断
            if (IsNotAttachIndex(motion)) {
                return;
            }
            // アニメーションデタッチ
            MV1DetachAnim(_mHandle, motion.GetAttachIndex());
            // 情報初期化
            motion.Reset();
        }

        void ModelAnimComponent::PlayAnim(ModelAnimInfo& motion) {
            // 未アタッチの場合中断
            if (IsNotAttachIndex(motion)) {
                return;
            }
            // アニメーション再生
            MV1SetAttachAnimTime(_mHandle, motion.GetAttachIndex(), motion.GetPlayTime());
            // 再生時間カウント
            motion.CountPlayTime();
        }

        void ModelAnimComponent::AnimBlend() {
            // どちらか未アタッチの場合中断
            if (EitherIsNotAttachIndex()) {
                return;
            }
            // ブレンド率算出
            float blendRate = static_cast<float>(_blendCnt) / _blendFrame;
            // アニメーションブレンド
            MV1SetAttachAnimBlendRate(_mHandle, _main.GetAttachIndex(), 1.0f - blendRate);
            MV1SetAttachAnimBlendRate(_mHandle, _blend.GetAttachIndex(), blendRate);
            // ブレンドカウントを進める
            _blendCnt++;

            // 指定のブレンドフレームが過ぎたら
            if (_blendFrame < _blendCnt) {
                // _mainの破棄
                SetDetach(_main);
                // _blendのアニメーションを_mainに移す
                _main = _blend;
                // ブレンドフレーム分進める
                _main.SetPlayTime(_blendFrame);
                // _blendの情報初期化
                _blend.Reset();
            }
        }
    } // namespace ModelAnim
} // namespace Gyro
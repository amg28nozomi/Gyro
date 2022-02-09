/*****************************************************************//**
 * @file    ModelAnimComponent.cpp
 * @brief   モデルアニメクラス
 *
 * @author  宮澤耀生
 * @date    December 2021
 *********************************************************************/
#include "../ModelAnim/ModelAnimComponent.h"

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

        void ModelAnimComponent::SetMainAttach(const int handle, std::string_view key, const float speed, const bool loop) {
            // アタッチ済の場合中断
            if (IsAttachIndex(_main)) {
                return;
            }
            // モデルハンドル設定
            _mHandle = handle;
            // アニメーションアタッチ
            SetAttach(_main, key, speed, loop);
        }

        void ModelAnimComponent::SetBlendAttach(std::string_view key, const float flame, const float speed, const bool loop) {
            // アタッチ済の場合中断
            if (IsAttachIndex(_blend)) {
                return;
            }
            // アニメーションアタッチ
            SetAttach(_blend, key, speed, loop);
            // 各種設定
            _blendCnt = 0;
            _blendFrame = flame;
        }

        void ModelAnimComponent::SetAttach(ModelAnimInfo& motion, std::string_view key, const float speed, const bool loop) {
            // モデルハンドル未所持の場合エラー
            if (_mHandle == -1) {
#ifdef _DEBUG
                throw ("アニメーションするモデルハンドルの取得に失敗しました\n");
                // モデルハンドルが正常に読み込めていない
                // SetMainAttach()を使わずにSetBlendAttach()を使った
#endif
                return;
            }
            // アニメーション番号の取得
            int animNum = MV1GetAnimIndex(_mHandle, key.data());
            // アニメーション番号取得失敗の場合エラー
            if (animNum == -1) {
#ifdef _DEBUG
                throw ("アニメーション番号の取得に失敗しました\n");
                // モデルハンドルが正常に読み込めていない
                // アニメーション名に相違があるなどしてkeyが正常に読み込めていない
#endif
                return;
            }
            // アニメーションアタッチ
            int index = MV1AttachAnim(_mHandle, animNum);
            // 各種設定
            motion.SetAnimNum(animNum);
            motion.SetAttachIndex(index);
            motion.SetTotalTime(MV1GetAnimTotalTime(_mHandle, animNum));
            motion.SetPlaySpeed(speed);
            motion.SetAnimLoop(loop);
        }

        void ModelAnimComponent::SetDetach(ModelAnimInfo& motion) {
            // 未アタッチの場合中断
            if (!IsAttachIndex(motion)) {
                return;
            }
            // アニメーションデタッチ
            MV1DetachAnim(_mHandle, motion.GetAttachIndex());
            // 情報初期化
            motion.Reset();
        }

        void ModelAnimComponent::PlayAnim(ModelAnimInfo& motion) {
            // 未アタッチの場合中断
            if (!IsAttachIndex(motion)) {
                return;
            }
            // アニメーション再生
            MV1SetAttachAnimTime(_mHandle, motion.GetAttachIndex(), motion.GetPlayTime());
            // 再生時間カウント
            motion.CountPlayTime();
        }

        void ModelAnimComponent::AnimBlend() {
            // どちらか未アタッチの場合中断
            if (!BothIsAttachIndex()) {
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
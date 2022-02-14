/*****************************************************************//**
 * @file    EffectComponent.cpp
 * @brief   エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "EffectComponent.h"

namespace Gyro {
    namespace Effect {
        EffectComponent::EffectComponent(Application::ApplicationMain& app) : _app(app) {

        }

        EffectComponent::~EffectComponent() {

        }

        void EffectComponent::Process() {
            // DXライブラリのカメラとEffekseerのカメラを同期する。
            Effekseer_Sync3DSetting();
            // Effekseerにより再生中のエフェクトを更新する。
            UpdateEffekseer3D();
        }

        void EffectComponent::Draw() const {
            // Effekseerにより再生中のエフェクトを描画する。
            DrawEffekseer3D();
        }

        void EffectComponent::PlayEffect(const std::string_view key, const AppMath::Vector4 position, const float radian) {
            // エフェクトハンドルの取得
            int handle = GetEffectHandle(key);
            if (handle == -1) {
                // 未登録の場合中断
                return;
            }
            // エフェクトを再生する。
            int play = PlayEffekseer3DEffect(handle);
            // エフェクトの位置を設定
            auto& [x, y, z] = position.GetVector3();
            SetPosPlayingEffekseer3DEffect(play, x, y, z);
            // エフェクトの向きを設定
            SetRotationPlayingEffekseer3DEffect(play, 0.0f, radian, 0.0f);
        }

        int EffectComponent::GetEffectHandle(const std::string_view key) {
            return _app.GetEffectServer().GetEffectHandle(key);
        }
    } // namespace Effect
} // namespace Gyro
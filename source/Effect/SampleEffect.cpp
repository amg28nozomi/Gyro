/*****************************************************************//**
 * @file   SampleEffect.cpp
 * @brief  お試しエフェクトクラス
 *
 * @author 宮澤耀生
 * @date   January 2021
 *********************************************************************/
#include "SampleEffect.h"

namespace Gyro {
    namespace Effect {
        SampleEffect::SampleEffect() {
            // 初期化
            Init();
        }

        SampleEffect::~SampleEffect() {

        }

        void SampleEffect::Init() {
            // 初期化
            _eScale = 10.0f;
            _eSpeed = 1.0f;
            // エフェクト読み込み
            _eHandle = LoadEffekseerEffect("res/Effect/Laser01.efkefc", _eScale);
            // エフェクト再生
            PlayEffect();
        }

        void SampleEffect::Process() {
            EffectBase::Process();
        }

        void SampleEffect::Draw() {
            EffectBase::Draw();
        }
    } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file   EffectBase.cpp
 * @brief  エフェクトの基底クラス
 *
 * @author 宮澤耀生
 * @date   January 2021
 *********************************************************************/
#include "EffectBase.h"

namespace Gyro {
    namespace Effect {
        EffectBase::EffectBase() {
            // 初期化
            Init();
        }

        EffectBase::~EffectBase() {

        }

        void EffectBase::Init() {
            // 初期化
            _eHandle = 0;
            _playEff = -1;
            _eScale = 0.0f;
            _eSpeed = 0.0f;
            _ePos = AppMath::Vector4();
            _eRot = AppMath::Vector4();
        }

        void EffectBase::Process() {
            // エフェクトが未再生の場合中断
            if (!IsEffectPlaying()) {
                return;
            }
            // 再生中のエフェクトの位置を設定
            SetPosPlayingEffekseer3DEffect(_playEff, _ePos.GetX(), 100.0f, _ePos.GetZ());
            // 再生中のエフェクトの向きを設定
            SetRotationPlayingEffekseer3DEffect(_playEff, 0, _eRot.GetY() *-1, 0);
            // Effekseerにより再生中のエフェクトを更新
            UpdateEffekseer3D();
        }

        void EffectBase::Draw() const{
            // エフェクトが未再生の場合中断
            //if (!IsEffectPlaying()) {
            //    return;
            //}
            // DXライブラリのカメラとEffekseerのカメラを同期
            Effekseer_Sync3DSetting();
            // Effekseerにより再生中の3Dエフェクトの描画を開始
            DrawEffekseer3D_Begin();
            // 指定されたEffekseerにより再生中のエフェクトを描画
            DrawEffekseer3D_Draw(_playEff);
            // Effekseerにより再生中の3Dエフェクトの描画を終了
            DrawEffekseer3D_End();
        }

        void EffectBase::PlayEffect() {
            // エフェクト再生中の場合中断
            if (IsEffectPlaying()) {
                return;
            }
            //エフェクトを再生
            _playEff = PlayEffekseer3DEffect(_eHandle);
            SetSpeedPlayingEffekseer3DEffect(_playEff, _eSpeed);
        }
    } // namespace Effect
} // namespace Gyro
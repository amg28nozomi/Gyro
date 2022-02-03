/*****************************************************************//**
 * @file   EffectBase.h
 * @brief  エフェクトの基底クラス
 *
 * @author 宮澤耀生
 * @date   January 2021
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "../ApplicationMain.h"

 /** 作品用名前空間 */
namespace Gyro {
    /** 敵用エフェクト用名前空間 */
    namespace Effect {
        /**
         * @class EffecBase
         * @brief 敵の基底クラス
         */
        class EffectBase {
        public:
            /**
             * @brief   コンストラクタ
             */
            EffectBase();
            /**
             * @brief   デストラクタ
             */
            virtual ~EffectBase();
            /**
             * @brief   初期化
             */
            virtual void Init();
            /**
             * @brief   更新
             */
            virtual void Process();
            /**
             * @brief   描画
             */
            virtual void Draw();
            /**
             * @brief   エフェクトを再生する
             */
            void PlayEffect();
            /**
             * @brief   エフェクト位置設定
             * @param   vPos エフェクト位置
             */
            void SetPosition(const VECTOR& position) {
                _ePos = position;
            }
            /**
             * @brief   エフェクト向き設定
             * @param   vDir エフェクト向き
             */
            void SetDirection(const VECTOR& direction) {
                _eDir = direction;
            }

        protected:
            /**
             * @brief   エフェクトの再生判定
             * @return  true:エフェクト再生中
             *          false:エフェクト未再生(または再生終了)
             */
            bool IsEffectPlaying() {
                return IsEffekseer3DEffectPlaying(_playEff) == 0;
            }

            int _eHandle;   //<! エフェクトハンドル
            int _playEff;   //<! 再生中のエフェクト
            float _eMagni;  //<! エフェクト拡大率
            float _eSpeed;  //<! エフェクト再生速度
            VECTOR _ePos;   //<! エフェクト位置
            VECTOR _eDir;   //<! エフェクト向き
        };
    } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file   SampleEffect.h
 * @brief  お試しエフェクトクラス
 *
 * @author 宮澤耀生
 * @date   January 2021
 *********************************************************************/
#pragma once
#include "EffectBase.h"

 /** 作品用名前空間 */
namespace Gyro {
    /** エフェクト用名前空間 */
    namespace Effect {
        /**
         * @class SampleEffect
         * @brief お試しエフェクトクラス
         */
        class SampleEffect : public EffectBase {
        public:
            /**
             * @brief     コンストラクタ
             */
            SampleEffect();
            /**
             * @brief     デストラクタ
             */
            ~SampleEffect() override;
            /**
             * @brief     初期化
             */
            void Init() override;
            /**
             * @brief   更新
             */
            void Process() override;
            /**
             * @brief   描画
             */
            void Draw() override;

        };
    } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EnemyWheel.h
 * @brief   敵クラス
 *
 * @author  宮澤耀生
 * @date    January 2022
 *********************************************************************/
#pragma once
#include "EnemyBase.h"

 /** 作品用名前空間 */
namespace Gyro {
    /** 敵用名前空間 */
    namespace Enemy {
        /**
         * @class EnemyWheel
         * @brief 敵クラス
         */
        class EnemyWheel : public EnemyBase {
        public:
            /**
             * @brief   コンストラクタ
             */
            EnemyWheel(Application::ApplicationMain& app);
            /**
             * @brief   デストラクタ
             */
            ~EnemyWheel();
            /**
             * @brief   初期化
             */
            bool Init() override;
            /**
             * @brief   更新
             */
            bool Process() override;
            /**
             * @brief  描画判定
             * @return 
             */
            bool Draw() const override;
        private:
          bool _iMove{false}; //!< 移動フラグ
        };
    } // namespace Enemy
} // namespace Gyro
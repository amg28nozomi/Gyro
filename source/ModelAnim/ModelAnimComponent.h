/*****************************************************************//**
 * @file    ModelAnimComponent.h
 * @brief   モデルアニメクラス
 *
 * @author  宮澤耀生
 * @date    December 2021
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "../ModelAnim/ModelAnimInfo.h"

 /** 作品用名前空間 */
namespace Gyro {
    /** モデルアニメ用名前空間 */
    namespace ModelAnim {
        /**
         * @class ModelAnimComponent
         * @brief モデルアニメクラス
         */
        class ModelAnimComponent {
        public:
            /**
             * @brief   コンストラクタ
             */
            ModelAnimComponent();
            /**
             * @brief   デストラクタ
             */
            ~ModelAnimComponent();
            /**
             * @brief   初期化
             */
            void Init();
            /**
             * @brief   更新
             */
            void Process();
            /**
             * @brief   メインアニメーションアタッチ
             * @param   handle モデルハンドル
             * @param   animNum アニメーション番号
             * @param   speed アニメーション再生速度
             * @param   loop ループ再生有無
             */
            void SetMainAttach(const int handle, const int animNum, const float speed, const bool loop);
            /**
             * @brief   ブレンドアニメーションアタッチ
             * @param   animNum アニメーション番号
             * @param   frame ブレンドフレーム
             * @param   speed アニメーション再生速度
             * @param   loop ループ再生有無
             */
            void SetBlendAttach(const int animNum, const float frame, const float speed, const bool loop);

        private:
            /**
             * @brief   アニメーションアタッチ
             * @param   info モデル情報
             * @param   animNum アニメーション番号
             * @param   speed アニメーション再生速度
             * @param   loop ループ再生有無
             */
            void SetAttach(ModelAnimInfo& info, const int animNum, const float speed, const bool loop);
            /**
             * @brief   アニメーションデタッチ
             * @param   info モデル情報
             */
            void SetDetach(ModelAnimInfo& info);
            /**
             * @brief   アニメーション再生
             * @param   info モデル情報
             */
            void PlayAnim(ModelAnimInfo& info);
            /**
             * @brief   アニメーションブレンド
             */
            void AnimBlend();
            /**
             * @brief   モデルの未アタッチ判定
             * @param   info モデル情報
             * @return  true:アニメーション未登録
             *          false:アニメーション登録済み
             */
            bool IsNotAttachIndex(ModelAnimInfo& info) const {
                return info.GetAttachIndex() == -1;
            }
            /**
             * @brief   両方のモデルの未アタッチ判定
             * @return  true:どちらか(または両方)アニメーション未登録
             *          false:どちらもアニメーション登録済み
             */
            bool EitherIsNotAttachIndex() const {
                return _main.GetAttachIndex() == -1 || _blend.GetAttachIndex() == -1;
            }

            int _mHandle;       //!< モデルハンドル
            int _blendCnt;      //!< ブレンドカウント
            float _blendFrame;  //!< ブレンドフレーム

            ModelAnimInfo _main;   //!< 現在のモデル情報
            ModelAnimInfo _blend;  //!< 切り替わるモデル情報
        };
    } // namespace ModelAnim
} // namespace Gyro
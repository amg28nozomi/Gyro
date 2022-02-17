/*****************************************************************//**
 * @file    ModelAnimComponent.h
 * @brief   モデルアニメクラス
 *
 * @author  宮澤耀生
 * @date    December 2021
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "ModelAnimInfo.h"

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
             *          (初期化時以外使ってはいけない)
             * @param   handle モデルハンドル
             * @param   key アニメーション名
             * @param   speed アニメーション再生速度
             * @param   loop ループ再生有無
             */
            void SetMainAttach(const int handle, std::string_view key, const float speed, const bool loop);
            /**
             * @brief   ブレンドアニメーションアタッチ
             *          (アニメーション切り替えはこちらを使う)
             * @param   key アニメーション名
             * @param   frame ブレンドフレーム
             * @param   speed アニメーション再生速度
             * @param   loop ループ再生有無
             */
            void SetBlendAttach(std::string_view key, const float frame, const float speed, const bool loop);
            /**
             * @brief   現在のアニメーション終了判定
             * @return  true:アニメーション終了
             *          false:アニメーション再生中
             */
            bool GetMainAnimEnd() const {
                return _main.GetAnimEnd();
            }
            /**
             * @brief   メインモデルの再生フレームを取得
             * @return  再生フレーム
             * @author  鈴木希海
             */
            float GetMainFrame() const {
              return _main.GetPlayTime();
            }
        private:
            /**
             * @brief   アニメーションアタッチ
             * @param   info モデル情報
             * @param   key アニメーション名
             * @param   speed アニメーション再生速度
             * @param   loop ループ再生有無
             */
            void SetAttach(ModelAnimInfo& info, std::string_view key, const float speed, const bool loop);
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
             * @brief   モデルのアタッチ判定
             * @param   info モデル情報
             * @return  true:アニメーション登録済み
             *          false:アニメーション未登録
             */
            bool IsAttachIndex(ModelAnimInfo& info) const {
                return info.GetAttachIndex() != -1;
            }
            /**
             * @brief   両方のモデルのアタッチ判定
             * @return  true:どちらもアニメーション登録済み
             *          false:どちらか(または両方)アニメーション未登録
             */
            bool BothIsAttachIndex() const {
                return _main.GetAttachIndex() != -1 && _blend.GetAttachIndex() != -1;
            }

            int _mHandle;       //!< モデルハンドル
            int _blendCnt;      //!< ブレンドカウント
            float _blendFrame;  //!< ブレンドフレーム

            ModelAnimInfo _main;   //!< 現在のモデル情報
            ModelAnimInfo _blend;  //!< 切り替わるモデル情報
        };
    } // namespace ModelAnim
} // namespace Gyro
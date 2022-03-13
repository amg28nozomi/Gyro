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

 /**
  * @brief ゲームベース
  */
namespace Gyro {
  /**
   * @brief モデルアニメベース
   */
  namespace ModelAnim {
    /**
     * @class ModelAnimComponent
     * @brief モデルアニメクラス
     */
    class ModelAnimComponent {
    public:
      /**
       * @brief  コンストラクタ
       */
      ModelAnimComponent();
      /**
       * @brief  デストラクタ
       */
      ~ModelAnimComponent();
      /**
       * @brief  解放
       */
      void Release();
      /**
       * @brief  更新
       */
      void Process();
      /**
       * @brief  メインアニメーションアタッチ
       *         (初期化時以外使ってはいけない)
       * @param  handle モデルハンドル
       * @param  key    アニメーション名
       * @param  speed  アニメーション再生速度
       * @param  loop   ループ再生有無
       */
      void SetMainAttach(const int handle, const std::string_view key, const float speed, const bool loop);
      /**
       * @brief  ブレンドアニメーションアタッチ
       *         (アニメーション切り替えはこちらを使う)
       * @param  key   アニメーション名
       * @param  frame ブレンドフレーム
       * @param  speed アニメーション再生速度
       * @param  loop  ループ再生有無
       */
      void SetBlendAttach(const std::string_view key, const float frame, const float speed, const bool loop);
      /**
       * @brief  現在のアニメーションの再生速度倍率の設定
       * @param  rate 再生速度倍率
       */
      void SetMainSpeedRate(const float rate) {
        _main.SetSpeedRate(rate);
      }
      /**
       * @brief  指定アニメーションがセットされているかの判定
       * @param  key    アニメーション名
       * @return true:セットされている false:セットされていない
       */
      bool IsSetMainAnim(std::string_view key);
      /**
       * @brief  アニメーション名のアニメーション番号変換
       * @param  key アニメーション名
       * @return アニメーション番号
       */
      int AnimKeyConversion(const std::string_view key) const {
        return MV1GetAnimIndex(_mHandle, key.data());
      }
      /**
       * @brief  現在のアニメーションのアニメーション番号の取得
       * @return アニメーション番号
       */
      int GetMainAnimNum() const {
        return _main.GetAnimNum();
      }
      /**
       * @brief  現在のアニメーションのアタッチ番号の取得
       * @return アタッチ番号
       */
      int GetMainAttachIndex() const {
        return _main.GetAttachIndex();
      }
      /**
       * @brief  現在のアニメーションの総時間の取得
       * @return アニメーション総時間
       */
      float GetMainTotalTime() const {
        return _main.GetTotalTime();
      }
      /**
       * @brief  現在のアニメーションの再生時間の取得
       * @return アニメーション再生時間
       */
      float GetMainPlayTime() const {
        return _main.GetPlayTime();
      }
      /**
       * @brief  現在のアニメーション終了判定
       * @return true:アニメーション終了
       *         false:アニメーション再生中
       */
      bool GetMainAnimEnd() const {
        return _main.GetAnimEnd();
      }
      /**
       * @brief  アニメーションブレンド中判定
       * @return true:アニメーションブレンド中
       *         false:アニメーションブレンドしていない
       */
      bool IsBlending() const {
        return _blending;
      }

    private:
      /**
       * @brief  アニメーションアタッチ
       * @param  info モデル情報
       * @param  key アニメーション名
       * @param  speed アニメーション再生速度
       * @param  loop ループ再生有無
       */
      void SetAttach(ModelAnimInfo& info, const std::string_view key, const float speed, const bool loop);
      /**
       * @brief  アニメーションデタッチ
       * @param  info モデル情報
       */
      void SetDetach(ModelAnimInfo& info);
      /**
       * @brief  アニメーション再生
       * @param  info モデル情報
       */
      void PlayAnim(ModelAnimInfo& info);
      /**
       * @brief  アニメーションブレンド
       */
      void AnimBlend();
      /**
       * @brief  モデルのアタッチ判定
       * @param  info モデル情報
       * @return true:アニメーション登録済み
       *         false:アニメーション未登録
       */
      bool IsAttachIndex(ModelAnimInfo& info) const {
        return info.GetAttachIndex() != -1;
      }

      int _mHandle{ -1 };         //!< モデルハンドル
      int _blendCnt{ 0 };         //!< ブレンドカウント
      float _blendFrame{ 0.0f };  //!< ブレンドフレーム
      bool _blending{ false };    //!< ブレンド中

      ModelAnimInfo _main;   //!< 現在のモデル情報
      ModelAnimInfo _blend;  //!< 切り替わるモデル情報
    };
  } // namespace ModelAnim
} // namespace Gyro
/*****************************************************************//**
 * @file    MotionInfo.h
 * @brief   モデルアニメ情報クラス
 *
 * @author  宮澤耀生
 * @date    December 2021
 *********************************************************************/
#pragma once

 /**
  * @brief ゲームベース
  */
namespace Gyro {
  /**
   * @brief モデルアニメベース
   */
  namespace ModelAnim {
    /**
     * @class MotionInfo
     * @brief モデルアニメ情報クラス
     */
    class ModelAnimInfo {
    public:
      /**
       * @brief  コンストラクタ
       */
      ModelAnimInfo();
      /**
       * @brief  デストラクタ
       */
      ~ModelAnimInfo();
      /**
       * @brief  情報初期化
       */
      void Reset();
      /**
       * @brief  再生時間カウント
       */
      void CountPlayTime();
      /**
       * @brief  アニメーション番号の設定
       * @param  animNum アニメーション番号
       */
      void SetAnimNum(const int animNum) {
        _animNum = animNum;
      }
      /**
       * @brief  アタッチ番号の設定
       * @param  index アタッチ番号
       */
      void SetAttachIndex(const int index) {
        _attachIndex = index;
      }
      /**
       * @brief  アニメーション総時間の設定
       * @param  time アニメーション総時間
       */
      void SetTotalTime(const float time) {
        _totalTime = time;
      }
      /**
       * @brief  アニメーション再生時間の設定
       * @param  time アニメーション再生時間
       */
      void SetPlayTime(const float time) {
        _playTime = time;
      }
      /**
       * @brief  アニメーション再生速度の設定
       * @param  speed アニメーション再生速度
       */
      void SetPlaySpeed(const float speed) {
        _playSpeed = speed;
      }
      /**
       * @brief  再生速度倍率の設定
       * @param  rate 再生速度倍率
       */
      void SetSpeedRate(const float rate) {
        _speedRate = rate;
      }
      /**
       * @brief  ループ再生有無の設定
       * @param  loop ループ再生有無
       */
      void SetAnimLoop(const bool loop) {
        _animLoop = loop;
      }
      /**
       * @brief  アニメーション番号の取得
       * @return アニメーション番号
       */
      int GetAnimNum() const {
        return _animNum;
      }
      /**
       * @brief  アタッチ番号の取得
       * @return アタッチ番号
       */
      int GetAttachIndex() const {
        return _attachIndex;
      }
      /**
       * @brief  アニメーション総時間の取得
       * @return アニメーション総時間
       */
      float GetTotalTime() const {
        return _totalTime;
      }
      /**
       * @brief  アニメーション再生時間の取得
       * @return アニメーション再生時間
       */
      float GetPlayTime() const {
        return _playTime;
      }
      /**
       * @brief  アニメーション終了の取得
       * @return アニメーション終了
       */
      bool GetAnimEnd() const {
        return _animEnd;
      }

    private:
      int _animNum{ -1 };        //!< アニメーション番号
      int _attachIndex{ -1 };    //!< アタッチ番号
      float _totalTime{ 0.0f };  //!< アニメーション総時間
      float _playTime{ 0.0f };   //!< アニメーション再生時間
      float _playSpeed{ 0.0f };  //!< アニメーション再生速度
      float _speedRate{ 1.0f };  //!< 再生速度倍率
      bool _animLoop{ false };   //!< ループ再生有無
      bool _animEnd{ false };    //!< アニメーション終了
    };
  } // namespace ModelAnim
} // namespace Gyro
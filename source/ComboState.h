/*****************************************************************//**
 * @file   ComboState.h
 * @brief  
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <string>
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief プレイヤーベース
   */
  namespace Player {
    class ComboState;
    /**
     * @class ComboState
     * @brief コンボ状態クラス
     */
    class ComboState {
    public:
      /**
       * @brief コンストラクタ
       */
      ComboState();
      /**
       * @brief  コンストラクタ
       * @param  animName アニメーション名
       * @param  total 総判定時間
       * @param  start ジャスト判定の開始フレーム
       * @param  end   ジャスト判定の終了フレーム
       */
      ComboState(std::string_view animName, float total, float start, float end);
      /**
       * @brief  更新処理
       * @param  animFrame アニメーションの経過フレーム
       * @return 
       */
      virtual bool Process(float animFrame);
      /**
       * @brief  アニメーション名の取得
       * @return アニメーション名
       */
      std::string GetAnimName() const {
        return _animName;
      }
      /**
       * @brief  総判定時間の取得
       * @return 総判定時間
       */
      float GetTotalTime() const {
        return _totalTime;
      }
      /**
       * @brief  ジャスト判定フレームの取得
       * @return ジャスト判定フレーム
       */
      float GetJustTime() const {
        return _justEnd - _justStart;
      }
    protected:
      std::string _animName{}; //!< アニメーション名
      int _key{0};             //!< アクションに紐づける
      float _totalTime{0};     //!< アニメーションフレーム
      float _inputStart{0};    //!< 入力判定の受付開始フレーム
      float _inputEnd{0};      //!< 入力判定の受付終了フレーム
      float _justStart{0};     //!< ジャスト判定の開始フレーム
      float _justEnd{0};       //!< ジャスト判定の終了フレーム
      /**
       * @brief  ジャスト判定時間の設定処理
       * @param  start 開始フレーム
       * @param  end   終了フレーム
       */
      virtual void SetJustTime(float start, float end);
    };
  } // namespace Player
} // namespace Gyro
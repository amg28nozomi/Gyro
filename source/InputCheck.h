/*****************************************************************//**
 * @file   InputCheck.h
 * @brief  入力判定用情報クラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <utility>

namespace Gyro {
  namespace Application {
    /**
     * @class InputCheck
     * @brief 
     */
    class InputCheck {
    public:
      /**
       * @brief コンストラクタ
       */
      InputCheck();
      /**
       * @brief 更新処理
       * @param 経過時間
       */
      void Process(float frame);
      /**
       * @brief  コンストラクタ
       * @param  total 総判定時間
       * @param  justStart ジャスト入力の判定開始フレーム
       * @param  justEnd   ジャスト入力の判定終了フレーム
       */
      InputCheck(float total, float justStart, float justEnd);
      /**
       * @brief  総判定時間の取得
       * @return 総判定時間
       */
      const inline float TotalTime() const {
        return _total;
      }
      /**
       * @brief  ジャスト判定フレームの取得
       * @return ジャスト判定フレーム
       */
      const inline float JustFrame() const {
        return _just.second - _just.first;
      }
    protected:
      float _total; //!< 総判定時間
      std::pair<float, float> _just; //!< ジャスト判定フレーム(frist:開始, second:終了)
      /**
       * @brief  ジャスト判定フレームの設定
       * @param  start 開始フレーム
       * @param  end   終了フレーム
       * @return 
       */
      bool JustTime(float start, float end);
    };
  } // namespace Application
} // namespace Gyro
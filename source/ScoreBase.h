/*****************************************************************//**
 * @file   ScoreBase.h
 * @brief  ゲームスコアの基底クラス
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief スコアベース
   */
  namespace Score {
    /**
     * @class ScoreBase
     * @brief スコアベース
     */
    class ScoreBase {
    public:
      /**
       * @brief コンストラクタ
       */
      ScoreBase();
      /**
       * @brief コンストラクタ
       * @param score スコアポイント
       */
      ScoreBase(int score);
      /**
       * @brief スコアの加算処理
       * @param value 値
       */
      void Add(float value);
      /**
       * @brief  スコアポイントの取得(整数値)
       * @return 整数値にキャストしたスコアポイント
       */
      inline int GetInteger() const {
        return static_cast<int>(_point);
      }
      /**
       * @brief  スコアポイントの取得(単精度浮動小数点数)
       * @return 生のスコアポイント
       */
      inline float GetFloat() const {
        return _point;
      }
      /**
       * @brief  スコア同士の加算処理
       * @param  score 合算するスコア
       * @return 合算スコア
       */
      ScoreBase operator+ (const ScoreBase score);
    protected:
      float _point{0}; //!< スコアポイント
    };
  } // namespace Score
} // namespace Gyro
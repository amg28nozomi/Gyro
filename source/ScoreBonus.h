/*****************************************************************//**
 * @file   ScoreBonus.h
 * @brief  スコア倍率データ
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <utility>
/**
 * @brief ゲームベース
 */
namespace Gyro {
  /**
   * @brief スコアベース
   */
  namespace Score {
    /**
     * @class ScoreBonus
     * @brief スコア倍率データ
     */
    class ScoreBonus {
    public:
      /**
       * @brief 空のコンストラクタ
       */
      ScoreBonus();
      /**
       * @brief コンストラクタ
       * @param combo コンボ数(正数)
       * @param bouns スコア倍率
       */
      ScoreBonus(unsigned int combo, const float bouns);
      /**
       * @brief  コンボ数の取得
       * @return コンボ数
       */
      inline int GetCombo() const {
        return _combo;
      }
      /**
       * @brief  スコア倍率の取得
       * @return スコア倍率
       */
      inline float GetBouns() const {
        return _bonus;
      }
      /**
       * @brief  全データの取得
       * @return first:コンボ数 second:スコア倍率
       */
      inline std::pair<int, float> GetScoreBonus() const {
        return { _combo, _bonus };
      }
    private:
      int _combo{0};      //!< 倍率が適応されるコンボ数
      float _bonus{1.0f}; //!< スコア倍率
    };
  } // namespace Score
} // namespace Gyro
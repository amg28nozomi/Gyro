/*****************************************************************//**
 * @file   ScoreBonus.cpp
 * @brief  スコア倍率データの定義
 *
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ScoreBonus.h"

namespace Gyro {
  namespace Score {

    ScoreBonus::ScoreBonus() {
    }

    ScoreBonus::ScoreBonus(unsigned int combo, const float bouns) {
      _combo = static_cast<int>(combo);
      _bonus = bouns;
    }
  } // namespace Score
} // namespace Gyro
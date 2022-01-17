/*****************************************************************//**
 * @file   ScoreBase.cpp
 * @brief  ゲームスコアの基底クラスの定義
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ScoreBase.h"

namespace Gyro {
  namespace Score {

    ScoreBase::ScoreBase() {
    }

    ScoreBase::ScoreBase(int score) {
      _point = static_cast<float>(score);
    }

    ScoreBase::ScoreBase(float score) : _point(score) {
    }

    void ScoreBase::Add(float value) {
      _point += value;
    }

    ScoreBase ScoreBase::operator+(const ScoreBase score) {
      // 二つのスコアを合算した値を返す
      return ScoreBase(this->_point + score._point);
    }
  } // namespace Score
} // namespace Gyro
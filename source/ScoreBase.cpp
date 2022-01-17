/*****************************************************************//**
 * @file   ScoreBase.cpp
 * @brief  �Q�[���X�R�A�̊��N���X�̒�`
 * 
 * @author ��؊�C
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
      // ��̃X�R�A�����Z�����l��Ԃ�
      return ScoreBase(this->_point + score._point);
    }
  } // namespace Score
} // namespace Gyro
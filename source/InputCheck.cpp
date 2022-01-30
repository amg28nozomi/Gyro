/*****************************************************************//**
 * @file   InputCheck.cpp
 * @brief  
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "InputCheck.h"

namespace Gyro {
  namespace Application {

    InputCheck::InputCheck() {
      _total = 0.0f;
      _just = std::make_pair(0.0f, 0.0f);
    }

    InputCheck::InputCheck(float total, float justStart, float justEnd) {
      _total = total;

    }

    void InputCheck::Process(float frame) {
      // 入力判定を行う
      
    }

    bool InputCheck::JustTime(float start, float end) {
      // 開始フレームが終了フレームより大きい場合は値をスワップ
      if (end < start) {
        std::swap(start, end);
      }
      // ジャスト入力時間を設定
      _just = std::make_pair(start, end);
      return true;
    }
  } // namespace Application
} // namespace Gyro
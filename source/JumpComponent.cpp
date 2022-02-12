/*****************************************************************//**
 * @file   JumpComponent.cpp
 * @brief  ジャンプ機能クラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "JumpComponent.h"
#include <appframe.h>
#include <cmath>

namespace Gyro {
  namespace Player {

    JumpComponent::JumpComponent() {
      _type = ComponentType::Jump;
    }

    void JumpComponent::Set(const float range, const int fright) {
      _range = range;
      _fright = fright;
      _f = fright / 10;
    }

    void JumpComponent::Start() {
      // ジャンプ処理の開始
      _count = 0;
      _jump = true;
    }

    void JumpComponent::Finish() {
      // ジャンプ処理の後始末を行う
      _count = 0;
      _jump = false;
    }

    float JumpComponent::JumpPower() {
      ++_count; // 時間経過
      // 経過時間が総対空時間を超過した場合はリセット
      if (_fright < _count) {
        _jump = false;
        return 0.0f;
      }
      auto t = static_cast<float>(_count);
      auto fi = static_cast<float>(_f);
      return _range * std::cos(t / fi) / fi;
    }

  } // namespace Player
} // namespace Gyro
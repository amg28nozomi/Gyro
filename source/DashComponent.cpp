/*****************************************************************//**
 * @file   DashComponent.cpp
 * @brief  ダッシュコンポーネントクラスの定義
 * 
 * @author 鈴木希海
 * @date   March 2022
 *********************************************************************/
#include "DashComponent.h"

namespace Gyro {
  namespace Object {

    DashComponent::DashComponent() : ObjectComponent() {
      // タイプの設定
      _type = ComponentType::Jump;
    }

    void DashComponent::Init() {

    }

    void DashComponent::Start() {
      // 
      _dashState = DashState::Active;
    }

    void DashComponent::Finish() {
      // ダッシュ状態を終了
      _dashState = DashState::NoActive;
    }

    bool DashComponent::Process(AppMath::Vector4& move) {
      if (_dashState != DashState::Active) {
        // インターバル中か？
        if (IsInterval()) {
          Interval();
        }
        return false;
      }
      // 移動量を設定する
      move = _move;
      return true;
    }

    void DashComponent::Interval() {
      // インターバルが終了したかの判定
      if (_time <= 0.0f) {
        _dashState = DashState::NoActive;
        _time = 0.0f;
        return;
      }
      _time -= 10.0f; // インターバルタイムを経過させる
    }

    void DashComponent::SetMove(const AppMath::Vector4& move, float time) {
      if (time <= 0.0f) {
        return;
      }
      // 設定
      _length = move;
      _move = move / time;
    }

    void DashComponent::SetIniterval(const float interval) {
      // 時間を設定する
      _time = interval;
      _dashState = DashState::Interval;
    }
  } // namespace Object
} // namespace Gyro
/*****************************************************************//**
 * @file   DashComponent.cpp
 * @brief  ダッシュコンポーネントクラスの定義
 * 
 * @author 鈴木希海
 * @date   March 2022
 *********************************************************************/
#include "DashComponent.h"
#include "ObjectBase.h"

namespace Gyro {
  namespace Object {

    DashComponent::DashComponent(ObjectBase& owner) : ObjectComponent(), _owner(owner) {
      // タイプの設定
      _type = ComponentType::Dash;
    }

    void DashComponent::Init() {
      // 初期化処理
      _dashState = DashState::NoActive;

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
      // ダッシュ状態かの判定
      if (!IsDash()) {
        // インターバル中か？
        Interval();
        return false;
      }
      // 向きベクトルの取得
      auto forward = _owner.GetForward();
      // 力を算出
      auto power = _power / _count;
      // 別名定義
      using Vector4 = AppMath::Vector4;
      // y成分を無視して計算を行う
      auto m = Vector4::Scale(forward, Vector4(1.0f, 0.0f, 1.0f));
      // 向いている方向に進ませる
      _move = m * power;
      return true;
    }

    bool DashComponent::Interval() {
      // インターバル中でない場合は処理を行わない
      if (!IsInterval()) {
        return false;
      }
      // インターバルが終了したかの判定
      if (_intervalTime <= 0.0f) {
        _dashState = DashState::NoActive;
        _intervalTime = 0.0f;
        return true;
      }
      _intervalTime -= 10.0f; // インターバルタイムを経過させる
      return true;
    }

    void DashComponent::SetDash(const float dashPower, float totalTime, float playSpeed) {
      if (totalTime <= 0.0f) {
        return;
      }
      // 移動力の設定
      _power = dashPower;
      // 処理回数の設定
      _count = static_cast<int>(totalTime / playSpeed);
    }

    void DashComponent::SetIniterval(const float interval) {
      // 時間を設定する
      _intervalTime = interval;
      _dashState = DashState::Interval;
    }
  } // namespace Object
} // namespace Gyro
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
      // ダッシュ起動
      _dashState = DashState::Active;
    }

    void DashComponent::Finish() {
      // ダッシュ状態を終了
      _dashState = DashState::Interval;
      _count = 0;
      _dashEnd = true;
    }

    bool DashComponent::Process() {
      // ダッシュ状態かの判定
      if (!IsDash()) {
        // インターバル中か？
        Interval();
        return false;
      }
      // 待機遷移判定
      if (_count == 30) {
        // インターバル状態に遷移する
        _dashState = DashState::Interval;
        _count = 0;
        return true;
      }
      // カウントでの終了判定
      ++_count;
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

    void DashComponent::SetDash(const AppMath::Vector4& direction, float power, float totalTime) {
      // 再生中の場合はセットを行わない
      if (totalTime <= 0.0f) {
        return;
      }
      // 移動速度の設定
      auto speed = 10.0f;
      using Vector4 = AppMath::Vector4;
      // 自機の向きベクトル
      auto forward = _owner.GetForward();

      _move = Vector4(speed * forward.GetX(), 0.0f, speed * forward.GetZ());
      // 単位ベクトル化
      auto normal = AppMath::Vector4::Normalize(_move);
      // ラジアンを生成(z軸は反転させる)
      auto radian = std::atan2f(normal.GetX(), !normal.GetZ());
#ifndef _DEBUG
      _owner.SetRotation(AppMath::Vector4(0.0f, radian, 0.0f));
#else
      // デグリー値をセットする(デバッグ用)
      _owner.SetRotation(AppMath::Vector4(0.0f, AppMath::Utility::RadianToDegree(radian), 0.0f));
#endif
      // 移動量を設定する
      // _move = Vector4::Scale(_direction, Vector4(speed, 0.0f, speed));
      _power = power;
    }

    void DashComponent::SetIniterval(const float interval) {
      // 時間を設定する
      _intervalTime = interval;
      _dashState = DashState::Interval;
    }
  } // namespace Object
} // namespace Gyro
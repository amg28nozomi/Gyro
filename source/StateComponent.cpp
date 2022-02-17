#include "StateComponent.h"
#include <appframe.h>

namespace {
  // 割合
  constexpr auto Max = 100;
  constexpr auto Min = 0;
}

namespace Gyro {
  namespace Object {

    StateComponent::StateComponent() {
      // 初期化
      _type = ComponentType::State;
      Init();
    }

    void StateComponent::Init() {
      // 初期化処理
    }

    bool StateComponent::Set(const float total, const int start, const int end) {
      using Arithmetic = AppFrame::Math::Arithmetic;
      // 範囲内に収まっているかの判定
      if (Arithmetic::IsRange(start, Min, Max)) {
        // 範囲内に収まっているかの判定
        if (Arithmetic::IsRange(end, Min, Max)) {
          // 開始フレームと終了フレームをセットする
          _start = Frame(total, start);
          _end = Frame(total, end);
          return true; // セット成功
        }
      }
      return false;    // 設定失敗
    }

    void StateComponent::Start() {
      _flag = false; // 入力状態をfalseにする
    }

    void StateComponent::Finish() {

    }

    bool StateComponent::Process(const float play) {
      using Arithmetic = AppFrame::Math::Arithmetic;
      // 判定範囲内収まっているか？
      if (Arithmetic::IsRange(play, static_cast<float>(_start), static_cast<float>(_end))) {
        // 終了処理を実行
        Finish();
        return true; // 入力有り
      }
      return false;  // 判定外
    }

    int StateComponent::Frame(const float total, const int percent) const {
      float num = 1.0 - (percent / Max);
      return static_cast<int>(total * num);
    }

  } // namespace Object
} // namespace Gyro
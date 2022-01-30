#include "ComboState.h"
#include <stdexcept>

namespace Gyro{
  namespace Player {

    ComboState::ComboState() {
    }

    ComboState::ComboState(std::string_view animName, float total, float start, float end) {
      _animName = animName.data();
      _totalTime = total;
      SetJustTime(start, end);
    }
    
    bool ComboState::Process(float animFrame) {
      // 
      return true;
    }

    void ComboState::SetJustTime(float start, float end) {
#ifdef _DEBUG
      // 判定用テーブル
      auto table = { start, end };
      for (auto value : table) {
        // 時間がマイナスの場合
        if (value < 0.0f) {
          throw std::logic_error("ComboState:ジャスト判定時間が不正です\n");
        }
      }
#endif
      // 開始フレームが終了フレーム以上の場合は値をスワップ
      if (end < start) {
        std::swap(start, end);
      }
      // ジャスト判定時間をセットする
      _justStart = start;
      _justEnd = end;
    }
  } // namespace Player
} // namespace Gyro
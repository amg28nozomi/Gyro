/*****************************************************************//**
 * @file    EffectPlayerUltSlash.cpp
 * @brief   プレイヤー必殺発動エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerUltSlash.h"

namespace {
  // エフェクト終了フラグセットカウント値定数
  constexpr int EndCount = 105;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerUltSlash::EffectPlayerUltSlash(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerUltSlash::~EffectPlayerUltSlash() {

    }

    void EffectPlayerUltSlash::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerUltSlash);
    }

    void EffectPlayerUltSlash::Process() {
      EffectBase::Process();
      // 終了フラグカウントを1増やす
      _endCount++;
      if (EndCount <= _endCount) {
        // 必殺攻撃エフェクト終了
        _app.GetEffectServer().SetUltSlashEnd(true);
      }
    }
  } // namespace Effect
} // namespace Gyro
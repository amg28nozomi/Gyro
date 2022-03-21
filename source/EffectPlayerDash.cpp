/*****************************************************************//**
 * @file    EffectPlayerDash.cpp
 * @brief   プレイヤーダッシュエフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerDash.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerDash::EffectPlayerDash(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerDash::~EffectPlayerDash() {

    }

    void EffectPlayerDash::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerDash);
    }
  } // namespace Effect
} // namespace Gyro
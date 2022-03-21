/*****************************************************************//**
 * @file    EffectPlayerLanding.cpp
 * @brief   プレイヤー着地エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerLanding.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerLanding::EffectPlayerLanding(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerLanding::~EffectPlayerLanding() {

    }

    void EffectPlayerLanding::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerLanding);
    }
  } // namespace Effect
} // namespace Gyro
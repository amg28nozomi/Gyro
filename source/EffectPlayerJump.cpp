/*****************************************************************//**
 * @file    EffectPlayerJump.cpp
 * @brief   プレイヤージャンプエフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerJump.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerJump::EffectPlayerJump(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerJump::~EffectPlayerJump() {

    }

    void EffectPlayerJump::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerJump);
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectPlayerAvoidance.cpp
 * @brief   プレイヤー被ダメエフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAvoidance.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerAvoidance::EffectPlayerAvoidance(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerAvoidance::~EffectPlayerAvoidance() {

    }

    void EffectPlayerAvoidance::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerAvoidance);
    }
  } // namespace Effect
} // namespace Gyro
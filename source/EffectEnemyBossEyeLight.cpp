/*****************************************************************//**
 * @file    EffectEnemyBossEyeLight.cpp
 * @brief   敵ボス眼光エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossEyeLight.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossEyeLight::EffectEnemyBossEyeLight(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyBossEyeLight::~EffectEnemyBossEyeLight() {

    }

    void EffectEnemyBossEyeLight::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossEyeLight);
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectEnemyEyeLight.cpp
 * @brief   敵眼光エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyEyeLight.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyEyeLight::EffectEnemyEyeLight(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyEyeLight::~EffectEnemyEyeLight() {

    }

    void EffectEnemyEyeLight::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyEyeLight);
    }
  } // namespace Effect
} // namespace Gyro
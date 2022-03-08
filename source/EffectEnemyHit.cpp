/*****************************************************************//**
 * @file    EffectEnemyHit.cpp
 * @brief   敵被ダメエフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyHit.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyHit::EffectEnemyHit(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyHit::~EffectEnemyHit() {

    }

    void EffectEnemyHit::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyHit);
    }
  } // namespace Effect
} // namespace Gyro
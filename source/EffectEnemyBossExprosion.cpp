/*****************************************************************//**
 * @file    EffectEnemyBossExprosion.cpp
 * @brief   敵ボス爆発エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossExprosion.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossExprosion::EffectEnemyBossExprosion(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyBossExprosion::~EffectEnemyBossExprosion() {

    }

    void EffectEnemyBossExprosion::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossExprosion);
    }
  } // namespace Effect
} // namespace Gyro
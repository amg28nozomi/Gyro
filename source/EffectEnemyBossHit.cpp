/*****************************************************************//**
 * @file    EffectEnemyBossHit.cpp
 * @brief   敵ボス被ダメエフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossHit.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossHit::EffectEnemyBossHit(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyBossHit::~EffectEnemyBossHit() {

    }

    void EffectEnemyBossHit::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossHit);
    }
  } // namespace Effect
} // namespace Gyro
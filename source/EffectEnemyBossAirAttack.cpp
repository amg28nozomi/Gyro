/*****************************************************************//**
 * @file    EffectEnemyBossAirAttack.cpp
 * @brief   敵ボス空中攻撃エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossAirAttack.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossAirAttack::EffectEnemyBossAirAttack(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyBossAirAttack::~EffectEnemyBossAirAttack() {

    }

    void EffectEnemyBossAirAttack::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossAirAttack);
    }
  } // namespace Effect
} // namespace Gyro
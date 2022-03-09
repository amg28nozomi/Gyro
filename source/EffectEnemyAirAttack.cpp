/*****************************************************************//**
 * @file    EffectEnemyAirAttack.cpp
 * @brief   敵空中攻撃エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyAirAttack.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyAirAttack::EffectEnemyAirAttack(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyAirAttack::~EffectEnemyAirAttack() {

    }

    void EffectEnemyAirAttack::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyAirAttack);
    }
  } // namespace Effect
} // namespace Gyro
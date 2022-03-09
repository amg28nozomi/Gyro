/*****************************************************************//**
 * @file    EffectEnemyBossGroundAttack.cpp
 * @brief   敵ボス地上攻撃エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossGroundAttack.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossGroundAttack::EffectEnemyBossGroundAttack(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyBossGroundAttack::~EffectEnemyBossGroundAttack() {

    }

    void EffectEnemyBossGroundAttack::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossGroundAttack);
    }
  } // namespace Effect
} // namespace Gyro
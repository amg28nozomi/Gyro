/*****************************************************************//**
 * @file    EffectEnemyBossGroundAttack2.cpp
 * @brief   敵ボス地上攻撃2エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossGroundAttack2.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossGroundAttack2::EffectEnemyBossGroundAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyBossGroundAttack2::~EffectEnemyBossGroundAttack2() {

    }

    void EffectEnemyBossGroundAttack2::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossGroundAttack2);
    }
  } // namespace Effect
} // namespace Gyro
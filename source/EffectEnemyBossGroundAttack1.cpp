/*****************************************************************//**
 * @file    EffectEnemyBossGroundAttack1.cpp
 * @brief   敵ボス地上攻撃1エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyBossGroundAttack1.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyBossGroundAttack1::EffectEnemyBossGroundAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyBossGroundAttack1::~EffectEnemyBossGroundAttack1() {

    }

    void EffectEnemyBossGroundAttack1::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyBossGroundAttack1);
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectEnemyGroundAttack.cpp
 * @brief   敵地上攻撃エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyGroundAttack.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyGroundAttack::EffectEnemyGroundAttack(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyGroundAttack::~EffectEnemyGroundAttack() {

    }

    void EffectEnemyGroundAttack::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyGroundAttack);
    }
  } // namespace Effect
} // namespace Gyro
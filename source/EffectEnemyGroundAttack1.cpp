/*****************************************************************//**
 * @file    EffectEnemyGroundAttack1.cpp
 * @brief   敵地上攻撃1エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyGroundAttack1.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyGroundAttack1::EffectEnemyGroundAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyGroundAttack1::~EffectEnemyGroundAttack1() {

    }

    void EffectEnemyGroundAttack1::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyGroundAttack1);
    }
  } // namespace Effect
} // namespace Gyro
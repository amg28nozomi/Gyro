/*****************************************************************//**
 * @file    EffectEnemyGroundAttack2.cpp
 * @brief   敵地上攻撃2エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyGroundAttack2.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyGroundAttack2::EffectEnemyGroundAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyGroundAttack2::~EffectEnemyGroundAttack2() {

    }

    void EffectEnemyGroundAttack2::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyGroundAttack2);
    }
  } // namespace Effect
} // namespace Gyro
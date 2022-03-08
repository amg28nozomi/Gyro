/*****************************************************************//**
 * @file    EffectEnemyExprosion.cpp
 * @brief   敵爆発エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyExprosion.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyExprosion::EffectEnemyExprosion(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyExprosion::~EffectEnemyExprosion() {

    }

    void EffectEnemyExprosion::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyExprosion);
    }
  } // namespace Effect
} // namespace Gyro
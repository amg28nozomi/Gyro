/*****************************************************************//**
 * @file    EffectPlayerAirHeavyAttack2.cpp
 * @brief   プレイヤー空中強攻撃2エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirHeavyAttack2.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerAirHeavyAttack2::EffectPlayerAirHeavyAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerAirHeavyAttack2::~EffectPlayerAirHeavyAttack2() {

    }

    void EffectPlayerAirHeavyAttack2::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirHeavyAttack2);
    }
  } // namespace Effect
} // namespace Gyro
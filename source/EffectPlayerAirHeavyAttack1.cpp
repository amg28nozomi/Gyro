/*****************************************************************//**
 * @file    EffectPlayerAirHeavyAttack1.cpp
 * @brief   プレイヤー空中強攻撃1エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirHeavyAttack1.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerAirHeavyAttack1::EffectPlayerAirHeavyAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerAirHeavyAttack1::~EffectPlayerAirHeavyAttack1() {

    }

    void EffectPlayerAirHeavyAttack1::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirHeavyAttack1);
    }
  } // namespace Effect
} // namespace Gyro
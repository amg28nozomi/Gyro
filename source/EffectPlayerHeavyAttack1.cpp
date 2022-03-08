/*****************************************************************//**
 * @file    EffectPlayerHeavyAttack1.cpp
 * @brief   プレイヤー強攻撃1エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerHeavyAttack1.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerHeavyAttack1::EffectPlayerHeavyAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerHeavyAttack1::~EffectPlayerHeavyAttack1() {

    }

    void EffectPlayerHeavyAttack1::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerHeavyAttack1);
    }
  } // namespace Effect
} // namespace Gyro
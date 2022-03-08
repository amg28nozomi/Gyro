/*****************************************************************//**
 * @file    EffectPlayerHeavyAttack2.cpp
 * @brief   プレイヤー強攻撃2エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerHeavyAttack2.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerHeavyAttack2::EffectPlayerHeavyAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerHeavyAttack2::~EffectPlayerHeavyAttack2() {

    }

    void EffectPlayerHeavyAttack2::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerHeavyAttack2);
    }
  } // namespace Effect
} // namespace Gyro
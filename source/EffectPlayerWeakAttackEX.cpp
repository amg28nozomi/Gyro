/*****************************************************************//**
 * @file    EffectPlayerWeakAttackEX.cpp
 * @brief   プレイヤー弱攻撃EXエフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerWeakAttackEX.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerWeakAttackEX::EffectPlayerWeakAttackEX(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerWeakAttackEX::~EffectPlayerWeakAttackEX() {

    }

    void EffectPlayerWeakAttackEX::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerWeakAttackEX);
    }
  } // namespace Effect
} // namespace Gyro
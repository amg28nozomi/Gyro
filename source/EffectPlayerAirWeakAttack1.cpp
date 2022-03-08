/*****************************************************************//**
 * @file    EffectPlayerAirWeakAttack1.cpp
 * @brief   プレイヤー空中弱攻撃1エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirWeakAttack1.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerAirWeakAttack1::EffectPlayerAirWeakAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerAirWeakAttack1::~EffectPlayerAirWeakAttack1() {

    }

    void EffectPlayerAirWeakAttack1::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirWeakAttack1);
    }
  } // namespace Effect
} // namespace Gyro
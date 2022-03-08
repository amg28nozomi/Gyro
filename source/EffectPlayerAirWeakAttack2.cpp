/*****************************************************************//**
 * @file    EffectPlayerAirWeakAttack2.cpp
 * @brief   プレイヤー空中弱攻撃2エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirWeakAttack2.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerAirWeakAttack2::EffectPlayerAirWeakAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerAirWeakAttack2::~EffectPlayerAirWeakAttack2() {

    }

    void EffectPlayerAirWeakAttack2::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirWeakAttack2);
    }
  } // namespace Effect
} // namespace Gyro
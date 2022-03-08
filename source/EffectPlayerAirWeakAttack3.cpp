/*****************************************************************//**
 * @file    EffectPlayerAirWeakAttack3.cpp
 * @brief   プレイヤー空中弱攻撃3エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirWeakAttack3.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerAirWeakAttack3::EffectPlayerAirWeakAttack3(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerAirWeakAttack3::~EffectPlayerAirWeakAttack3() {

    }

    void EffectPlayerAirWeakAttack3::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirWeakAttack3);
    }
  } // namespace Effect
} // namespace Gyro
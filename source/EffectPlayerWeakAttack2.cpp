/*****************************************************************//**
 * @file    EffectPlayerWeakAttack2.cpp
 * @brief   プレイヤー弱攻撃2エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerWeakAttack2.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerWeakAttack2::EffectPlayerWeakAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerWeakAttack2::~EffectPlayerWeakAttack2() {

    }

    void EffectPlayerWeakAttack2::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerWeakAttack2);
    }
  } // namespace Effect
} // namespace Gyro
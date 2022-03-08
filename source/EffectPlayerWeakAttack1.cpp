/*****************************************************************//**
 * @file    EffectPlayerWeakAttack1.cpp
 * @brief   プレイヤー弱攻撃1エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerWeakAttack1.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerWeakAttack1::EffectPlayerWeakAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerWeakAttack1::~EffectPlayerWeakAttack1() {

    }

    void EffectPlayerWeakAttack1::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerWeakAttack1);
    }
  } // namespace Effect
} // namespace Gyro
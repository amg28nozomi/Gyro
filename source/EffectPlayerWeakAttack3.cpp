/*****************************************************************//**
 * @file    EffectPlayerWeakAttack3.cpp
 * @brief   プレイヤー弱攻撃3エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerWeakAttack3.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerWeakAttack3::EffectPlayerWeakAttack3(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerWeakAttack3::~EffectPlayerWeakAttack3() {

    }

    void EffectPlayerWeakAttack3::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerWeakAttack3);
    }
  } // namespace Effect
} // namespace Gyro
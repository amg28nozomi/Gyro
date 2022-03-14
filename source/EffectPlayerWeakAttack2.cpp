/*****************************************************************//**
 * @file    EffectPlayerWeakAttack2.cpp
 * @brief   プレイヤー弱攻撃2エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerWeakAttack2.h"

namespace {
  // エフェクト生成時プレイヤーの状態
  constexpr auto CheckState = Gyro::Player::Player::PlayerState::Attack2;
}

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
      // プレイヤー状態確認あり
      _isCheck = true;
      _checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
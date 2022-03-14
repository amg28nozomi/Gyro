/*****************************************************************//**
 * @file    EffectPlayerWeakAttack1.cpp
 * @brief   プレイヤー弱攻撃1エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerWeakAttack1.h"

namespace {
  // エフェクト生成時プレイヤーの状態
  constexpr auto CheckState = Gyro::Player::Player::PlayerState::Attack1;
}

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
      // プレイヤー状態確認あり
      _isCheck = true;
      _checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
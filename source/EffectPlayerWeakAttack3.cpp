/*****************************************************************//**
 * @file    EffectPlayerWeakAttack3.cpp
 * @brief   プレイヤー弱攻撃3エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerWeakAttack3.h"

namespace {
  // エフェクト生成時プレイヤーの状態
  constexpr auto CheckState = Gyro::Player::Player::PlayerState::Attack3;
}

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
      // プレイヤー状態確認あり
      _isCheck = true;
      _checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectPlayerWeakAttackEX.cpp
 * @brief   プレイヤー弱攻撃EXエフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerWeakAttackEX.h"

namespace {
  // エフェクト生成時プレイヤーの状態
  //constexpr auto CheckState = Gyro::Player::Player::PlayerState::;
}

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
      // プレイヤー状態確認あり
      //_isCheck = true;
      //_checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectPlayerLanding.cpp
 * @brief   プレイヤー着地エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerLanding.h"

namespace {
  // エフェクト生成時プレイヤーの状態
  //constexpr auto CheckState = Gyro::Player::Player::PlayerState::;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerLanding::EffectPlayerLanding(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerLanding::~EffectPlayerLanding() {

    }

    void EffectPlayerLanding::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerLanding);
      // プレイヤー状態確認あり
      //_isCheck = true;
      //_checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
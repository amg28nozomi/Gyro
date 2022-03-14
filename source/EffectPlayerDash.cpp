/*****************************************************************//**
 * @file    EffectPlayerDash.cpp
 * @brief   プレイヤーダッシュエフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerDash.h"

namespace {
  // エフェクト生成時プレイヤーの状態
  //constexpr auto CheckState = Gyro::Player::Player::PlayerState::Run;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerDash::EffectPlayerDash(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerDash::~EffectPlayerDash() {

    }

    void EffectPlayerDash::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerDash);
      // プレイヤー状態確認あり
      //_isCheck = true;
      //_checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
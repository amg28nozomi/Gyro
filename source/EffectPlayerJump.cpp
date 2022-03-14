/*****************************************************************//**
 * @file    EffectPlayerJump.cpp
 * @brief   プレイヤージャンプエフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerJump.h"

namespace {
  // エフェクト生成時プレイヤーの状態
  //constexpr auto CheckState = Gyro::Player::Player::PlayerState::Jump;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerJump::EffectPlayerJump(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerJump::~EffectPlayerJump() {

    }

    void EffectPlayerJump::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerJump);
      // プレイヤー状態確認あり
      //_isCheck = true;
      //_checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectPlayerUltActivate.cpp
 * @brief   プレイヤー必殺発動エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerUltActivate.h"

namespace {
  // エフェクト生成時プレイヤーの状態
  //constexpr auto CheckState = Gyro::Player::Player::PlayerState::Attack1;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerUltActivate::EffectPlayerUltActivate(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerUltActivate::~EffectPlayerUltActivate() {

    }

    void EffectPlayerUltActivate::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerUltActivate);
      // プレイヤー状態確認あり
      //_isCheck = true;
      //_checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
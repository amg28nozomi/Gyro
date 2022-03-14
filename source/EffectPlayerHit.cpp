/*****************************************************************//**
 * @file    EffectPlayerHit.cpp
 * @brief   プレイヤー被ダメエフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerHit.h"

namespace {
  // エフェクト生成時プレイヤーの状態
  //constexpr auto CheckState = Gyro::Player::Player::PlayerState::;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerHit::EffectPlayerHit(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerHit::~EffectPlayerHit() {

    }

    void EffectPlayerHit::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerHit);
      // プレイヤー状態確認あり
      //_isCheck = true;
      //_checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
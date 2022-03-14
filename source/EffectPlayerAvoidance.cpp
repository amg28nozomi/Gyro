/*****************************************************************//**
 * @file    EffectPlayerAvoidance.cpp
 * @brief   プレイヤー回避エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAvoidance.h"

namespace {
  // エフェクト生成時プレイヤーの状態
  //constexpr auto CheckState = Gyro::Player::Player::PlayerState::Dash;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerAvoidance::EffectPlayerAvoidance(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerAvoidance::~EffectPlayerAvoidance() {

    }

    void EffectPlayerAvoidance::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerAvoidance);
      // プレイヤー状態確認あり
      //_isCheck = true;
      //_checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
/*****************************************************************//**
 * @file    EffectPlayerAirHeavyAttack2.cpp
 * @brief   プレイヤー空中強攻撃2エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirHeavyAttack2.h"

namespace {
  // 生成から再生までのラグ定数
  constexpr int PlayLag = 10;
  // エフェクト生成時プレイヤーの状態
  constexpr auto CheckState = Gyro::Player::Player::PlayerState::JumpAttack2;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerAirHeavyAttack2::EffectPlayerAirHeavyAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerAirHeavyAttack2::~EffectPlayerAirHeavyAttack2() {

    }

    void EffectPlayerAirHeavyAttack2::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirHeavyAttack2);
      // ラグ設定
      _playLag = PlayLag;
      // プレイヤー状態確認あり
      _isCheck = true;
      _checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
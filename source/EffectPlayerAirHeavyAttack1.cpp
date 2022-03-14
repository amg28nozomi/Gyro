/*****************************************************************//**
 * @file    EffectPlayerAirHeavyAttack1.cpp
 * @brief   プレイヤー空中強攻撃1エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirHeavyAttack1.h"

namespace {
  // 生成から再生までのラグ定数
  constexpr int PlayLag = 5;
  // エフェクト生成時プレイヤーの状態
  constexpr auto CheckState = Gyro::Player::Player::PlayerState::JumpAttack1;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerAirHeavyAttack1::EffectPlayerAirHeavyAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerAirHeavyAttack1::~EffectPlayerAirHeavyAttack1() {

    }

    void EffectPlayerAirHeavyAttack1::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirHeavyAttack1);
      // ラグ設定
      _playLag = PlayLag;
      // プレイヤー状態確認あり
      _isCheck = true;
      _checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
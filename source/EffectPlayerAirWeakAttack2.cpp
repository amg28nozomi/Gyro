/*****************************************************************//**
 * @file    EffectPlayerAirWeakAttack2.cpp
 * @brief   プレイヤー空中弱攻撃2エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirWeakAttack2.h"

namespace {
  // 生成から再生までのラグ定数
  constexpr int PlayLag = 10;
  // エフェクト生成時プレイヤーの状態
  constexpr auto CheckState = Gyro::Player::Player::PlayerState::JumpAttack2;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerAirWeakAttack2::EffectPlayerAirWeakAttack2(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerAirWeakAttack2::~EffectPlayerAirWeakAttack2() {

    }

    void EffectPlayerAirWeakAttack2::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirWeakAttack2);
      // ラグ設定
      _playLag = PlayLag;
      // プレイヤー状態確認あり
      _isCheck = true;
      _checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
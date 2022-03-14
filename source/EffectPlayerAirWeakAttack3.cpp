/*****************************************************************//**
 * @file    EffectPlayerAirWeakAttack3.cpp
 * @brief   プレイヤー空中弱攻撃3エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerAirWeakAttack3.h"

namespace {
  // 生成から再生までのラグ定数
  constexpr int PlayLag = 5;
  // エフェクト生成時プレイヤーの状態
  constexpr auto CheckState = Gyro::Player::Player::PlayerState::JumpAttack3;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerAirWeakAttack3::EffectPlayerAirWeakAttack3(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerAirWeakAttack3::~EffectPlayerAirWeakAttack3() {

    }

    void EffectPlayerAirWeakAttack3::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerAirWeakAttack3);
      // ラグ設定
      _playLag = PlayLag;
      // プレイヤー状態確認あり
      _isCheck = true;
      _checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
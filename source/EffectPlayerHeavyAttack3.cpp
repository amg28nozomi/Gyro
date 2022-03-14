/*****************************************************************//**
 * @file    EffectPlayerHeavyAttack3.cpp
 * @brief   プレイヤー強攻撃3エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerHeavyAttack3.h"

namespace {
  // 生成から再生までのラグ定数
  constexpr int PlayLag = 60;
  // エフェクト生成時プレイヤーの状態
  constexpr auto CheckState = Gyro::Player::Player::PlayerState::Attack3;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerHeavyAttack3::EffectPlayerHeavyAttack3(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerHeavyAttack3::~EffectPlayerHeavyAttack3() {

    }

    void EffectPlayerHeavyAttack3::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerHeavyAttack3);
      // ラグ設定
      _playLag = PlayLag;
      // プレイヤー状態確認あり
      _isCheck = true;
      _checkState = CheckState;
    }
  } // namespace Effect
} // namespace Gyro
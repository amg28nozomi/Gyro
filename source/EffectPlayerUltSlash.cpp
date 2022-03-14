/*****************************************************************//**
 * @file    EffectPlayerUltSlash.cpp
 * @brief   プレイヤー必殺発動エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerUltSlash.h"

namespace {
  // エフェクト生成時プレイヤーの状態
  //constexpr auto CheckState = Gyro::Player::Player::PlayerState::Attack1;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerUltSlash::EffectPlayerUltSlash(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerUltSlash::~EffectPlayerUltSlash() {

    }

    void EffectPlayerUltSlash::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerUltSlash);
      // プレイヤー状態確認あり
      //_isCheck = true;
      //_checkState = CheckState;
    }

    void EffectPlayerUltSlash::DeadEffect() {
      // エフェクト消去
      EffectBase::DeadEffect();
      // 必殺攻撃エフェクト終了
      _app.GetEffectServer().SetUltSlashEnd(true);
    }
  } // namespace Effect
} // namespace Gyro
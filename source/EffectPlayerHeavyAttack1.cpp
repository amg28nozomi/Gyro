/*****************************************************************//**
 * @file    EffectPlayerHeavyAttack1.cpp
 * @brief   プレイヤー強攻撃1エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerHeavyAttack1.h"

namespace {
  // 生成から再生までのラグ定数
  constexpr int PlayLag = 25;
}

namespace Gyro {
  namespace Effect {
    EffectPlayerHeavyAttack1::EffectPlayerHeavyAttack1(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerHeavyAttack1::~EffectPlayerHeavyAttack1() {

    }

    void EffectPlayerHeavyAttack1::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerHeavyAttack1);
      // ラグ設定
      _playLag = PlayLag;
    }
  } // namespace Effect
} // namespace Gyro
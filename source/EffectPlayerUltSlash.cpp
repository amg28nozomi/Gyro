/*****************************************************************//**
 * @file    EffectPlayerUltSlash.cpp
 * @brief   プレイヤー必殺発動エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerUltSlash.h"

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
    }
  } // namespace Effect
} // namespace Gyro
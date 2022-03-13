/*****************************************************************//**
 * @file    EffectPlayerJustActivate.cpp
 * @brief   プレイヤージャスト発動エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerJustActivate.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerJustActivate::EffectPlayerJustActivate(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerJustActivate::~EffectPlayerJustActivate() {

    }

    void EffectPlayerJustActivate::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerJustActivate);
    }
  } // namespace Effect
} // namespace Gyro
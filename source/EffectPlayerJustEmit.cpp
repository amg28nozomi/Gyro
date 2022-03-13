/*****************************************************************//**
 * @file    EffectPlayerJustEmit.cpp
 * @brief   プレイヤージャスト終了エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectPlayerJustEmit.h"

namespace Gyro {
  namespace Effect {
    EffectPlayerJustEmit::EffectPlayerJustEmit(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectPlayerJustEmit::~EffectPlayerJustEmit() {

    }

    void EffectPlayerJustEmit::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::PlayerJustEmit);
    }
  } // namespace Effect
} // namespace Gyro
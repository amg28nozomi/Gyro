/*****************************************************************//**
 * @file    EffectStageBarrier.cpp
 * @brief   ステージバリアエフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectStageBarrier.h"

namespace Gyro {
  namespace Effect {
    EffectStageBarrier::EffectStageBarrier(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectStageBarrier::~EffectStageBarrier() {

    }

    void EffectStageBarrier::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::StageBarrier);
    }
  } // namespace Effect
} // namespace Gyro
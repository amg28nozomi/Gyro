/*****************************************************************//**
 * @file    EffectStageBoxDestroy.cpp
 * @brief   ステージ箱破壊エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectStageBoxDestroy.h"

namespace Gyro {
  namespace Effect {
    EffectStageBoxDestroy::EffectStageBoxDestroy(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectStageBoxDestroy::~EffectStageBoxDestroy() {

    }

    void EffectStageBoxDestroy::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::StageBoxDestroy);
    }
  } // namespace Effect
} // namespace Gyro
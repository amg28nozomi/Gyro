/*****************************************************************//**
 * @file    EffectStageHeal.cpp
 * @brief   ステージ回復エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectStageHeal.h"

namespace Gyro {
  namespace Effect {
    EffectStageHeal::EffectStageHeal(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectStageHeal::~EffectStageHeal() {

    }

    void EffectStageHeal::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::StageHeal);
    }
  } // namespace Effect
} // namespace Gyro
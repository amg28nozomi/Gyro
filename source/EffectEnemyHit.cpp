/*****************************************************************//**
 * @file    EffectEnemyHit.cpp
 * @brief   敵被ダメエフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyHit.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyHit::EffectEnemyHit(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyHit::~EffectEnemyHit() {

    }

    void EffectEnemyHit::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyHit);
    }

    void EffectEnemyHit::Process() {
      // 再生中でない場合中断
      if (!_isPlay) {
        return;
      }
      // エフェクトの位置を設定
      auto& [x, y, z] = _ePos.GetVector3();
      SetPosPlayingEffekseer3DEffect(_playHandle, x, y, z);
      // エフェクトの向きを設定
      SetRotationPlayingEffekseer3DEffect(_playHandle, 0.0f, _eRadY, 0.0f);
      // エフェクト再生終了したか
      if (IsEffekseer3DEffectPlaying(_playHandle)) {
        // エフェクト消去
        DeadEffect();
      }
    }
  } // namespace Effect
} // namespace Gyro
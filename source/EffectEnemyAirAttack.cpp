/*****************************************************************//**
 * @file    EffectEnemyAirAttack.cpp
 * @brief   敵空中攻撃エフェクトクラス
 *
 * @author  宮澤耀生
 * @date    March 2022
 *********************************************************************/
#include "EffectEnemyAirAttack.h"

namespace Gyro {
  namespace Effect {
    EffectEnemyAirAttack::EffectEnemyAirAttack(Application::ApplicationMain& app) : EffectBase(app) {
      // 初期化
      Init();
    }

    EffectEnemyAirAttack::~EffectEnemyAirAttack() {

    }

    void EffectEnemyAirAttack::Init() {
      // エフェクトハンドルの取得
      _effectHandle = GetEffectHandle(EffectKey::EnemyAirAttack);
    }

    void EffectEnemyAirAttack::Process() {
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
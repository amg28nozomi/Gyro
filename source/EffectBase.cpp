/*****************************************************************//**
 * @file    EffectBase.cpp
 * @brief   エフェクトの基底クラス
 *
 * @author  宮澤耀生
 * @date    February 2022
 *********************************************************************/
#include "EffectBase.h"
#include "ObjectServer.h"

namespace Gyro {
  namespace Effect {
    EffectBase::EffectBase(Application::ApplicationMain& app) : _app(app) {

    }

    EffectBase::~EffectBase() {

    }

    void EffectBase::Init() {

    }

    void EffectBase::Process() {
      // 再生したか判定
      if (_isPlay) {
        // エフェクトの位置を設定
        auto& [x, y, z] = _ePos.GetVector3();
        SetPosPlayingEffekseer3DEffect(_playHandle, x, y, z);
        // エフェクトの向きを設定
        SetRotationPlayingEffekseer3DEffect(_playHandle, 0.0f, _eRadY, 0.0f);
        // エフェクト再生終了したか
        if (IsEffekseer3DEffectPlaying(_playHandle)) {
          // エフェクト消去
          DeadEffect();
          return;
        }
        // プレイヤー状態を確認するか
        if (_isCheck) {
          // プレイヤー状態の確認
          CheckPlayerState();
        }
        return;
      }
      // 生成から再生までのラグをラグカウントが超えたら
      if (_playLag <= _lagCount) {
        // エフェクト再生
        PlayEffect();
        return;
      }
      // ラグカウントを増やす
      _lagCount++;
    }

    void EffectBase::PlayEffect() {
      // エフェクト再生
      _playHandle = PlayEffekseer3DEffect(_effectHandle);
      // エフェクト活動状態
      _effectState = EffectState::Active;
      // エフェクト再生完了
      _isPlay = true;
    }

    void EffectBase::DeadEffect() {
      // エフェクト停止
      StopEffekseer3DEffect(_playHandle);
      // エフェクト再生ハンドル消去
      _playHandle = -1;
      // エフェクト死亡状態
      _effectState = EffectState::Dead;
    }

    void EffectBase::CheckPlayerState() {
      // プレイヤー状態の取得
      auto player = _app.GetObjectServer().GetPlayer();
      auto pState = player->GetPlayerState();
      // プレイヤー状態が生成時の状態と違う
      if (pState != _checkState) {
        // エフェクト消去
        DeadEffect();
      }
    }
  } // namespace Effect
} // namespace Gyro
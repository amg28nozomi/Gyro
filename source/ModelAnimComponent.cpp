/*****************************************************************//**
 * @file    ModelAnimComponent.cpp
 * @brief   モデルアニメクラス
 *
 * @author  宮澤耀生
 * @date    December 2021
 *********************************************************************/
#include "ModelAnimComponent.h"

namespace Gyro {
  namespace ModelAnim {
    ModelAnimComponent::ModelAnimComponent() {

    }

    ModelAnimComponent::~ModelAnimComponent() {
      // 解放
      Release();
    }

    void ModelAnimComponent::Release() {
      // アニメーションデタッチ
      SetDetach(_main);
      SetDetach(_blend);
    }

    void ModelAnimComponent::Process() {
      // アニメーション再生
      PlayAnim(_main);
      PlayAnim(_blend);
      // アニメーションブレンド
      AnimBlend();
    }

    void ModelAnimComponent::SetMainAttach(const int handle, const std::string_view key, const float speed, const bool loop) {
      // アタッチ済の場合エラー
      if (IsAttachIndex(_main)) {
#ifdef _DEBUG
        throw ("既にアニメーションがアタッチされています\n");
        // SetMainAttach()は初期化時しか使わない
        // SetBlendAttach()を使ってください
#endif
        return;
      }
      // モデルハンドル設定
      _mHandle = handle;
      // アニメーションアタッチ
      SetAttach(_main, key, speed, loop);
    }

    void ModelAnimComponent::SetBlendAttach(const std::string_view key, const float flame, const float speed, const bool loop) {
      // アタッチ済の場合デタッチ
      if (IsAttachIndex(_blend)) {
        SetDetach(_blend);
      }
      // アニメーションアタッチ
      SetAttach(_blend, key, speed, loop);
      // 各種設定
      _blendCnt = 0;
      _blendFrame = flame;
      // ブレンド開始
      _blending = true;
    }

    bool ModelAnimComponent::IsSetMainAnim(std::string_view key) {
      // メインにセットされているアニメーションを取得
      auto mainAnim = _main.GetAnimNum();
      auto number = AnimKeyConversion(key.data());
      // 取得に失敗した場合は偽を返す
      if (number == -1) {
        return false;
      }
      // 一致している場合はtrueを返す
      return number == mainAnim;
    }

    void ModelAnimComponent::SetAttach(ModelAnimInfo& motion, const std::string_view key, const float speed, const bool loop) {
      // モデルハンドル未所持の場合エラー
      if (_mHandle == -1) {
#ifdef _DEBUG
        throw ("アニメーションするモデルハンドルの取得に失敗しました\n");
        // モデルハンドルが正常に読み込めていない
        // SetMainAttach()を使わずにSetBlendAttach()を使った
#endif
        return;
      }
      // アニメーション名のアニメーション番号変換
      int animNum = AnimKeyConversion(key);
      // アニメーション番号取得失敗の場合エラー
      if (animNum == -1) {
#ifdef _DEBUG
        throw ("アニメーション番号の取得に失敗しました\n");
        // モデルハンドルが正常に読み込めていない
        // アニメーション名に相違があるなどしてkeyが正常に読み込めていない
#endif
        return;
      }
      // アニメーションアタッチ
      int index = MV1AttachAnim(_mHandle, animNum);
      // 各種設定
      motion.SetAnimNum(animNum);
      motion.SetAttachIndex(index);
      motion.SetTotalTime(MV1GetAnimTotalTime(_mHandle, animNum));
      motion.SetPlaySpeed(speed);
      motion.SetAnimLoop(loop);
    }

    void ModelAnimComponent::SetDetach(ModelAnimInfo& motion) {
      // 未アタッチの場合中断
      if (!IsAttachIndex(motion)) {
        return;
      }
      // アニメーションデタッチ
      MV1DetachAnim(_mHandle, motion.GetAttachIndex());
      // 情報初期化
      motion.Reset();
    }

    void ModelAnimComponent::PlayAnim(ModelAnimInfo& motion) {
      // 未アタッチの場合中断
      if (!IsAttachIndex(motion)) {
        return;
      }
      // アニメーション再生
      MV1SetAttachAnimTime(_mHandle, motion.GetAttachIndex(), motion.GetPlayTime());
      // 再生時間カウント
      motion.CountPlayTime();
    }

    void ModelAnimComponent::AnimBlend() {
      // ブレンドしない場合中断
      if (!_blending) {
        return;
      }
      // ブレンド率算出
      float blendRate = static_cast<float>(_blendCnt) / _blendFrame;
      // アニメーションブレンド
      MV1SetAttachAnimBlendRate(_mHandle, _main.GetAttachIndex(), 1.0f - blendRate);
      MV1SetAttachAnimBlendRate(_mHandle, _blend.GetAttachIndex(), blendRate);
      // ブレンドカウントを進める
      _blendCnt++;

      // 指定のブレンドフレームが過ぎたら
      if (_blendFrame < _blendCnt) {
        // _mainの破棄
        SetDetach(_main);
        // _blendのアニメーションを_mainに移す
        _main = _blend;
        // ブレンドフレーム分進める
        _main.SetPlayTime(_blendFrame);
        // _blendの情報初期化
        _blend.Reset();
        // ブレンド終了
        _blending = false;
      }
    }
  } // namespace ModelAnim
} // namespace Gyro
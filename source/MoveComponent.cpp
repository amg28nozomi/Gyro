/*****************************************************************//**
 * @file   MoveComponent.cpp
 * @brief  移動コンポーネントクラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "MoveComponent.h"
#include <appframe.h>
#include "ApplicationMain.h"
#include "Camera.h"
#include "ObjectBase.h"

namespace Gyro {
  namespace Object {

    MoveComponent::MoveComponent(ObjectBase& owner) : _owner(owner) {
      _move = AppMath::Vector4();
      _speed = 10.0f;
    }

    void MoveComponent::OldPosition() {
      // 前フレーム座標の更新
      _oldPosition = _owner.GetPosition();
    }

    bool MoveComponent::Move(const float x, const float z) {
      // 移動量がない場合は処理を行わない
      if (AppMath::Arithmetic::LengthSquared(x, z) == 0.0f) {
        _move.Zero(); // 移動量初期化
        return false; // 移動無し
      }
      // 別名定義
      using Vector4 = AppMath::Vector4;
      // デッドゾーンの取得
      const auto xState = _owner.GetApplicaton().GetOperation().GetXBoxState();
      auto deadZone = static_cast<float>(xState.GetDeadZoneMax());
      // 移動方向
      auto inputX = (x / deadZone);
      auto inputZ = (z / deadZone);
      // 移動量
      _move = Vector4(inputX * _speed, 0.0f, (inputZ * _speed));
      _move = _move * -1.0f;
      // ラジアンを生成(z軸は反転させる)
      auto radian = std::atan2(_move.GetX(), -_move.GetZ());
      // auto radian = std::atan2(-move.GetZ(), move.GetX());
#ifndef _DEBUG
      _owner.SetRotation(Vector4(0.0f, radian, 0.0f));
#else
      // デグリー値をセットする(デバッグ用)
      _owner.SetRotation(Vector4(0.0f, AppMath::Utility::RadianToDegree(radian), 0.0f));
#endif
      return true;   // 移動有り
    }

    void MoveComponent::Start() {

    }
    
    void MoveComponent::Finish() {
      _move.Zero();
    }
  } // namespace Object
} // namespace Gyro
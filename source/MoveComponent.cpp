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
      _speed = 8.0f;
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
      // カメラの取得
      const auto& camera = _owner.GetApplicaton().GetCamera();
      // カメラ情報の取得
      const auto cameraPos = camera.GetPosition();
      const auto cameraTarget = camera.GetTarget();
      // 別名定義
      using Vector4 = AppMath::Vector4;
      // 所有者の座標
      const auto target = _owner.GetPosition();
      // 二つのベクトルのなす角を求める
      auto cos = Vector4::Dot(cameraPos, target) / (Vector4::Length(cameraPos) * Vector4::Length(target));
      // ラジアンで算出
      auto f = std::acos(cos);
      // カメラ向きの取得
      // auto cameraForward = cameraPos.Direction(_owner.GetPosition());
      // カメラ向きの取得(y軸は無視する)
      // cameraForward = Vector4::Normalize(Vector4::Scale(cameraForward, Vector4(1.0f, 0.0f, 1.0f)));

      // デッドゾーンの取得
      const auto xState = _owner.GetApplicaton().GetOperation().GetXBoxState();
      auto deadZone = static_cast<float>(xState.GetDeadZoneMax());
      // 移動方向
      auto inputX = (x / deadZone);
      auto inputZ = (z / deadZone);
      // auto moveForward = Vector4::Normalize(Vector4::Scale(cameraForward ,Vector4(x / 30000.0f, 0.0f, z / 30000.0f)));
      _move = Vector4(inputX * _speed, 0.0f, inputZ * _speed) * f;
      //// デッドゾーンの取得
      //const auto xState= _owner.GetApplicaton().GetOperation().GetXBoxState();
      //auto deadZone = static_cast<float>(xState.GetDeadZoneMax());
      //// 移動方向
      //auto inputX = (x / deadZone);
      //auto inputZ = (z / deadZone);
      //// auto moveForward = Vector4::Normalize(Vector4::Scale(cameraForward ,Vector4(x / 30000.0f, 0.0f, z / 30000.0f)));
      //auto moveForward = Vector4::Normalize(Vector4::Scale(cameraForward, Vector4(inputX , 0.0f, inputZ)));
      // 移動量の算出
      // _move = moveForward * _speed;
      // _move = Vector4::Scale(move, moveForward);
      // Y座標の情報は無視する
      // _move.SetY(0.0f);
      return true;   // 移動有り
    }

    void MoveComponent::Start() {

    }
    
    void MoveComponent::Finish() {
      _move.Zero();
    }
  } // namespace Object
} // namespace Gyro
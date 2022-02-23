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
      // カメラの取得
      const auto& camera = _owner.GetApplicaton().GetCamera();
      // カメラ情報の取得
      const auto cameraPos = camera.GetPosition();
      const auto cameraTarget = camera.GetTarget();
      // 別名定義
      using Vector4 = AppMath::Vector4;
      // カメラ向きの取得
      // auto cameraForward = Vector4::Normalize(cameraPos.Direction(cameraTarget));
      auto cameraForward = cameraPos.Direction(_owner.GetPosition());
      cameraForward = Vector4::Normalize(Vector4::Scale(cameraForward, Vector4(1.0f, 0.0f, 1.0f)));
      // デッドゾーンの取得
      const auto xState= _owner.GetApplicaton().GetOperation().GetXBoxState();
      auto deadZone = xState.GetDeadZone();
      // 移動方向
      auto inputX = (x / static_cast<float>(deadZone.first));
      auto inputZ = (z / static_cast<float>(deadZone.second));
      // auto moveForward = Vector4::Normalize(Vector4::Scale(cameraForward ,Vector4(x / 30000.0f, 0.0f, z / 30000.0f)));
      auto moveForward = Vector4::Normalize(Vector4::Scale(cameraForward, Vector4(inputX , 0.0f, inputZ)));
      // 移動量の算出
      //auto speedX = (x / 30000.0f) * _speed;
      //auto speedZ = (z / 30000.0f) * _speed; // * /* length.GetZ()) * */ -1.0f
      _move = moveForward * _speed;
      // _move = Vector4::Scale(move, moveForward);
      // Y座標の情報は無視する
      _move.SetY(0.0f);
      return true;   // 移動有り
    }

    void MoveComponent::Start() {

    }
    
    void MoveComponent::Finish() {
      _move.Zero();
    }
  } // namespace Object
} // namespace Gyro
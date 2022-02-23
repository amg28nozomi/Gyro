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
      _speed = 5.0f;
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

      auto cameraZ = Vector4::Normalize(cameraTarget - cameraPos);
      auto cameraX = Vector4::Cross(cameraZ.Up(), cameraZ);
      cameraX = Vector4::Normalize(cameraX);
      // カメラ向きを基に移動量を算出する
      auto length = _owner.GetPosition().Direction(cameraPos);
      // 正規化
      length.Normalize();

      // 所有者の向きベクトルを取得
      const auto [forwardX, forwardY, forwardZ] = _owner.GetForward().GetVector3();
      // 移動量の算出
      auto speedX = (x / 30000.0f) * _speed;
      auto speedZ = ((z / 30000.0f) * _speed * length.GetZ()) * -1.0f;
      _move = Vector4(speedX, 0.0f, speedZ);
      return true;   // 移動有り
    }

    void MoveComponent::Start() {

    }
    
    void MoveComponent::Finish() {
      _move.Zero();
    }
  } // namespace Object
} // namespace Gyro
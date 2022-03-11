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
      const auto position = camera.GetPosition();
      const auto target = camera.GetTarget();
      // 別名定義
      using Vector4 = AppMath::Vector4;
      // デッドゾーンの取得
      const auto xState = _owner.GetApplicaton().GetOperation().GetXBoxState();
      auto deadZone = static_cast<float>(xState.GetDeadZoneMax());
      // 移動方向
      auto inputX = (x / deadZone);
      auto inputZ = (z / deadZone);
      // 移動量
      auto move = Vector4(inputX * _speed, 0.0f, inputZ * _speed);
      // 移動量(-1~ 1)
      // auto normal = Vector4(inputX, 0.0f, inputZ);

      // auto thisDirection = Vector4::Cross(_owner.GetPosition(), normal);

      //// カメラからターゲットへの向きベクトルを取得
      //auto direction = position.Direction(target);
      //// カメラからターゲットへの向きを求める
      //auto cameraCross = Vector4::Cross(position, direction);

      ////
      //auto angle = std::acos(thisDirection.Dot(cameraCross) / (thisDirection.Length() * cameraCross.Length()));
      //// デグリー値に変換
      //auto degree = AppMath::Utility::RadianToDegree(angle);

      // 行列の別名定義
      using Matrix44 = AppMath::Matrix44;

      // ラジアンを生成(z軸は反転させる)
      auto radian = std::atan2(-move.GetZ(), move.GetX());
      auto l = Vector4::Normalize(position.Direction(target));
      radian += std::atan2(l.GetZ(), l.GetX());
#ifndef _DEBUG
      _owner.SetRotation(Vector4(0.0f, radian, 0.0f));
#else
      // デグリー値をセットする(デバッグ用)
      _owner.SetRotation(Vector4(0.0f, AppMath::Utility::RadianToDegree(radian), 0.0f));
#endif

      // 回転→平行移動
      auto moveMatrix = /*translate **/ Matrix44::ToRotationY(radian);
      auto v = Vector4(0.0f, 0.0f, 8.0f);
      _move = moveMatrix * v;
      return true;   // 移動有り
    }

    void MoveComponent::Start() {

    }
    
    void MoveComponent::Finish() {
      _move.Zero();
    }
  } // namespace Object
} // namespace Gyro
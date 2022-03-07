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
      // 行列の別名定義
      using Matrix44 = AppMath::Matrix44;
      // 平行移動行列化
      auto translate = Matrix44::Translate(move);

      // ラジアンを生成(z軸は反転させる)
      auto radian = std::atan2(move.GetX(), -move.GetZ());
#ifndef _DEBUG
      _owner.SetRotation(Vector4(0.0f, radian, 0.0f));
#else
      // デグリー値をセットする(デバッグ用)
      _owner.SetRotation(Vector4(0.0f, AppMath::Utility::RadianToDegree(radian), 0.0f));
#endif
      // 回転→平行移動
      auto moveMatrix = translate * Matrix44::ToRotationY(radian);
      // auto moveMatrix = Matrix44::ToRotationY(radian) * translate;
      auto v = Vector4(1.0f, 1.0f, -1.0f);
      _move = moveMatrix * v;
      // ターゲット座標までの向きを算出
      //auto direction = position.Direction(target);
      //// 向きベクトルの各成分を取得
      //auto [dX, dY, dZ] = direction.GetVector3();
      //// カメラの回転行列
      //auto cameraRotateY = Matrix44::ToRotationY(atan2(dZ, dX));
      //// カメラの平行移動行列
      //auto cameraTranslate = Matrix44::Translate(position);
      //// カメラのワールド座標行列
      //auto cameraWorld = cameraTranslate * cameraRotateY;
      //// 逆行列に変換
      //auto inverseWorld = Matrix44::Inverse(cameraWorld);
      //// 現在の向きと

      //// ラジアンを生成(z軸は反転させる)
      //auto pRad = std::atan2(move.GetX(), -move.GetZ());
      //// 回転行列をビュー行列
      //auto moveRad =  inverseWorld * Matrix44::ToRotationY(pRad);
      //// 以上！
      //auto mPower = moveRad * translate;
      //_move = mPower * Vector4(1.0f, 0.0f, 1.0f);

      // カメラ向きの取得
      // auto cameraForward = cameraPos.Direction(_owner.GetPosition());
      // カメラ向きの取得(y軸は無視する)
      // cameraForward = Vector4::Normalize(Vector4::Scale(cameraForward, Vector4(1.0f, 0.0f, 1.0f)));
      // auto moveForward = Vector4::Normalize(Vector4::Scale(cameraForward ,Vector4(x / 30000.0f, 0.0f, z / 30000.0f)));
      //_move = Vector4(inputX * _speed, 0.0f, inputZ * _speed) * f;
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
/*****************************************************************//**
 * @file   SkySphere.cpp
 * @brief  スカイスフィアクラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "SkySphere.h"
#include "ApplicationMain.h"
#include "SpawnBase.h"
#include "UtilityDX.h"

namespace Gyro {
  namespace Object {

    SkySphere::SkySphere(Application::ApplicationMain& app, ObjectBase& owner) : ObjectBase(app), _owner(owner) {
      _id = ObjectId::SkySphere;
      _gravity = false;
      Init();
    }

    bool SkySphere::Init() {
      _handle = 0;
      return true;
    }

    void SkySphere::Set(Object::SpawnBase& spawn) {
      // 各種情報の設定
      _position = spawn.GetPosition();
      _rotation = spawn.GetRotation();
      _scale = spawn.GetScale();
    }

    bool SkySphere::Process() {
      // ワールド座標行列
      _world= AppMath::Utility::ToWorldMatrix(_owner.GetPosition(), _rotation, _scale);
      // _world = AppMath::Matrix44::Identity();
      //_world.Translate(_position);
      //_world = _world * w;

      // _position = _owner.GetPosition();
      // MV1SetPosition(_handle, UtilityDX::ToVECTOR(_position));
      // ワールド座標の更新
      // WorldMatrix();
      // 座標の設定
      auto num = MV1SetMatrix(_handle ,UtilityDX::ToMATRIX(_world));
      return true;
    }

    bool SkySphere::Draw() const {
      // モデルの描画に成功したかの判定
      if (MV1DrawModel(_handle) == -1) {
        return false; // 失敗
      }
      return true;
    }

    bool SkySphere::SetKey(std::string_view key) {
      // モデルハンドルの取得
      auto [handle, id] = _app.GetModelServer().GetModel(key, 1);
      // モデルハンドルの取得に成功したか
      if (handle == -1) {
        return false; // 失敗
      }
      // ハンドルを設定
      _handle = handle;
      return true;
    }

  } // namespace Object
} // namespace Gyro
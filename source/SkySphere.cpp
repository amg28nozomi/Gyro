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
      // 自機の中心座標を追従する
      _position = _owner.GetPosition();
      // ワールド座標の更新
      WorldMatrix();
      // 座標の設定
      MV1SetMatrix(_handle ,UtilityDX::ToMATRIX(_world));
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
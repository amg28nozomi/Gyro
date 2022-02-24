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
      // 別名定義
      using Matrix44 = AppMath::Matrix44;
      // 初期化
      _world = Matrix44::Identity();
      // 拡大率を追加
      _world.MulScaling(_scale);
      _world.MulTranslate(_position + _owner.GetPosition());
      // 設定に成功したかを戻り値で返す
      auto flag = MV1SetMatrix(_handle, UtilityDX::ToMATRIX(_world)) == 0;
      return flag;
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
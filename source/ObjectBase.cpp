/*****************************************************************//**
 * @file   ObjectBase.cpp
 * @brief  オブジェクトのスーパークラスの定義
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ObjectBase.h"
#include <appframe.h>
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "SpawnBase.h"
#include "UtilityDX.h"

namespace {
  constexpr auto MaxGravity = -50.0f;
} // namespace

namespace Gyro {
  namespace Object {

    ObjectBase::ObjectBase(Application::ApplicationMain& app) : _app(app) {
      _gravity = false;
      _mass = 0.0f;
      _world = AppMath::Matrix44::Identity();
    }

    bool ObjectBase::Init() {
      return true;
    }

    bool ObjectBase::Process() {
      // 重力影響フラグがtrueの場合重力処理を行う
      if (_gravity) {
        Gravity(); // 重力処理実行
      }
      return true;
    }

    bool ObjectBase::Draw() const {
      // モデルの描画を行う
      return true;
    }

    void ObjectBase::Set(SpawnBase& spawn) {
      // 各種パラメータの取得
      auto [position, rotation, scale] = spawn.GetTransform();
      // 座標・向き・スケールの設定
      _position = position;
      _rotation = rotation;
      _scale = scale;
    }

    void ObjectBase::Gravity() {
      // グラビティスケールの更新
      GravityScale();
      // 立ちフラグの更新
      _isStand = IsStand();
      // 地形との衝突判定
      if (_isStand) {
        GravityReset(); // 重力スケールの初期化
      }
    }

    void ObjectBase::GravityScale() {
      // デフォルトの重力加速度を重力スケールに加算する
      using Gravity = AppFrame::Math::GravityBase;
      if (MaxGravity < _gravityScale) {
        _gravityScale += Gravity::Acceleration();
        if (_gravityScale <= MaxGravity) {
          _gravityScale = MaxGravity; // 下限を超過した場合は修正
        }
      }
    }

    bool ObjectBase::IsStand() {
      return true;
    }

    void ObjectBase::GravityReset() {
      // 重力スケールを初期化する
      _gravityScale = 0.0f;
    }

    void ObjectBase::WorldMatrix(bool angle) {
      using Utility = AppMath::Utility;
      // ワールド座標変換を行う
#ifndef _DEBUG
      _world = Utility::ToWorldMatrix(_position, _rotation, _scale);
#else
      _world = Utility::ToWorldMatrix(_position, _rotation, _scale, angle);
#endif
    }

#ifdef _DEBUG
    bool ObjectBase::DebugDraw() const {
      return _app.GetDebugFlag();
    }
#endif
  } // namespace Object
} // namespace Gyro
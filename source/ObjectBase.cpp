/*****************************************************************//**
 * @file   ObjectBase.cpp
 * @brief  オブジェクトのスーパークラスの定義
 * 
 * @author 鈴木希海
 * @date   January 2022
 *********************************************************************/
#include "ObjectBase.h"
#include "appframe.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

namespace Gyro {
  namespace Object {

    ObjectBase::ObjectBase(Application::ApplicationMain& app) : _app(app) {
      _gravity = false;
      _mass = 0.0f;
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

    void ObjectBase::Gravity() {
      GravityScale(); // グラビティスケールの更新
      // 地形との衝突判定
      if (IsStand()) {
        GravityReset(); // 重力スケールの初期化
      }
    }

    void ObjectBase::GravityScale() {
      // デフォルトの重力加速度を重力スケールに加算する
      using Gravity = AppFrame::Math::GravityBase;
      _gravityScale += Gravity::Acceleration();
    }

    bool ObjectBase::IsStand() {
      return true;
    }

    void ObjectBase::GravityReset() {
      // 重力スケールを初期化する
      _gravity = 0.0f;
      // 線分とステージの押し出し処理を行う
    }

    AppMath::Matrix44 ObjectBase::WorldMatrix() {
      using Matrix = AppMath::Matrix44;
      auto world = Matrix::Identity(); // 単位行列の取得
      world.MulScaling(_scale);        // 拡縮
      using Utility = AppMath::Utility;
      world.RotateZ(_rotation.GetZ()); // z軸回転
      world.RotateY(_rotation.GetY()); // y軸回転
      world.RotateX(_rotation.GetX()); // x軸回転
      world.MulTranslate(_position);   // 平行移動
      return world; // 行列を返す
    }

#ifdef _DEBUG
    bool ObjectBase::DebugDraw() const {
      return _app.GetDebugFlag();
    }
#endif
  } // namespace Object
} // namespace Gyro
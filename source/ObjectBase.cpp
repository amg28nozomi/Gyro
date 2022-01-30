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
      // 重力処理を行うかの判定
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
      using Gravitys = AppFrame::Math::GravityBase;
      // 重力スケールの更新
      // _gravityScale = Gravitys::GravityScale(_gravityScale, _mass);
      // 床に接触しているか判定を行う

      // 接触している場合は押し出し処理を実行
      // _gravityScaleを0.0fで初期化
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
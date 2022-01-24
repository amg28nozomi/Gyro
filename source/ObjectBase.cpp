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
      _position;
      _rotation;
      _scale = AppFrame::Math::Vector4(1.0f, 1.0f, 1.0f);
      _world = AppFrame::Math::Matrix44::Identity();
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

    bool ObjectBase::WorldMatrixUpdate() {
      namespace AppMath = AppFrame::Math;
      // ワールド座標変換
      _world.MulScaling(_scale);        // 拡大縮小
      _world.RotateZ(_rotation.GetZ()); // z軸回転
      _world.RotateY(_rotation.GetY()); // y軸回転
      _world.RotateX(_rotation.GetX()); // x軸回転
      _world.MulTranslate(_position);   // 平行移動
    }

    void ObjectBase::Gravity() {
      using Gravitys = AppFrame::Math::GravityBase;
      // 重力スケールの更新
      // _gravityScale = Gravitys::GravityScale(_gravityScale, _mass);
      // 床に接触しているか判定を行う

      // 接触している場合は押し出し処理を実行
      // _gravityScaleを0.0fで初期化
    }
  } // namespace Object
} // namespace Gyro
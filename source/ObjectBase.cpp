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
      _gravityScale = Gravitys::GravityScale(_gravityScale, _mass);
      // 床に接触しているか判定を行う

      // 接触している場合は押し出し処理を実行
      // _gravityScaleを0.0fで初期化
    }
  } // namespace Object
} // namespace Gyro
/*****************************************************************//**
 * @file   InteriorBase.cpp
 * @brief  インテリヤの基底クラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "InteriorBase.h"
#include "ApplicationMain.h"
#include "SpawnBase.h"

namespace Gyro {
  namespace Interior {

    InteriorBase::InteriorBase(Application::ApplicationMain& app) : ObjectBase(app) {
    }

    bool InteriorBase::Init() {
      return true;
    }

    bool InteriorBase::Process() {
      // 更新処理
      return true;
    }

    bool InteriorBase::Draw() const {
#ifdef _DEBUG
      // デバッグフラグが立っている場合は描画を行う
      if (_app.GetDebugFlag()) {
        _collision->Draw();
      }
#endif
      return true;
    }

    void InteriorBase::Set(Object::SpawnBase& spawn) {
      // スポーン情報を基に設定を行う
      _position = spawn.GetPosition();
      _rotation = spawn.GetRotation();
      _scale = spawn.GetScale();
    }
  } // namespace Interior
} // namespace Gyro
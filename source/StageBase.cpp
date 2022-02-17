/*****************************************************************//**
 * @file   StageBase.cpp
 * @brief  ステージのスーパークラスの定義
 * 
 * @author 土橋峡介
 * @date   February 2022
 *********************************************************************/
#include "StageBase.h"
#include <appframe.h>
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "SpawnBase.h"

namespace Gyro {
  namespace Object {

    StageBase::StageBase(Application::ApplicationMain& app) : _app(app) {
    }

    bool StageBase::Init() {
      // リソースの解放
      _model.clear();
      return true;
    }

    bool StageBase::Process() {
      return true;
    }

    bool StageBase::Draw() const {
      return true;
    }

    void StageBase::Set(SpawnBase& spawn) {
      // 各種パラメータの取得
      auto [position, rotation, scale] = spawn.GetTransform();
      // 座標・向き・スケールの設定
      _position = position;
      _rotation = rotation;
      _scale = scale;
    }
  }
}

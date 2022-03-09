/*****************************************************************//**
 * @file   InvincibleComponent.cpp
 * @brief  無敵処理用のコンポーネントクラスの定義
 * 
 * @author 鈴木希海
 * @date   February 2022
 *********************************************************************/
#include "InvincibleComponent.h"
#include "ApplicationMain.h"

namespace Gyro {
  namespace Object {

    InvincibleComponent::InvincibleComponent(Application::ApplicationMain& app) : _app(app) {
      // 無敵処理
      _type = ComponentType::Invincible;
      _limit = 60;
      _time = 0;
      _infinity = false;
    }

    void InvincibleComponent::Init() {
      // 各種パラメータの初期化
      _time = 0;
      _infinity = false;
    }

    void InvincibleComponent::Start() {
      Init(); // 初期化
      // 無敵状態に遷移
      _invincible = InvincibleState::Invincible;
    }

    void InvincibleComponent::Finish() {
      // 通常状態に遷移
      _invincible = InvincibleState::Normal;
      Init();
    }

    void InvincibleComponent::InvincibleStart() {
      // 無敵状態に遷移
      _invincible = InvincibleState::Invincible;
      _infinity = true;
    }

    void InvincibleComponent::Process(const int speed) {
      // 無敵時間を終えたか
      if (TimeEnd(speed)) {
        Finish(); // 終了
      }
    }

    bool InvincibleComponent::TimeEnd(const int speed) {
      // 無制限フラグが立っているか
      if (_infinity) {
        return false;
      }
      _time += speed; // タイムに加速度を加算する
      // 経過時間は上限を超過したか
      return _limit <= _time;
    }

  } // namespace Object
} // namespace Gyro
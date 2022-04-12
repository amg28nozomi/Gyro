/*****************************************************************//**
 * @file   KnockBackComponent.cpp
 * @brief  ノックバックコンポーネントの定義
 * 
 * @author 土橋峡介
 * @date   March 2022
 *********************************************************************/
#include "KnockBackComponent.h"
#include "ObjectBase.h"
#include "EnemyBase.h"
#include "ApplicationMain.h"
#include "ObjectBase.h"
#include "ObjectServer.h"

namespace Gyro {
  namespace Object {

    KnockBackComponent::KnockBackComponent(ObjectBase& owner, Application::ApplicationMain& app) : _owner(owner), _app(app) {
      _state = KnockBackState::NonActive;
    }

    void KnockBackComponent::Start() {
      _state = KnockBackState::Active;
      _cnt = 20;
    }

    void KnockBackComponent::Finish() {
      _state = KnockBackState::NonActive;
      _move.Zero();
    }

    bool KnockBackComponent::Process() {
      // モーション中以外は当たり判定の更新を行わない
      if (_state == KnockBackState::NonActive) {
        return false;
      }
      auto objects = _app.GetObjectServer().GetObjects();
      // Playerの座標を取得
      auto pPos = _owner.GetPosition();
      _cnt--;
      if (_cnt > 0) {
        std::shared_ptr <Enemy::EnemyBase> enemy = nullptr;
        for (auto obj : objects) {
          if (obj->GetId() != ObjectBase::ObjectId::Enemy) continue;
          enemy = std::dynamic_pointer_cast<Enemy::EnemyBase>(obj);
          if (enemy.get()->GetEnemyState() != Enemy::EnemyBase::EnemyState::Attack) continue;
          auto knockBackVector = pPos - enemy->GetPosition();
          // 高さがいらないのでｙ以外を分解して取り出す
          auto [x, y, z] = knockBackVector.GetVector3();
          auto knockBack = AppMath::Vector4(x, 0.0f, z);
          knockBack.Normalize();
          _move = knockBack * 10;
        }
      }else {
        Finish();
      }
      return true;
    }
  } // namespace Object
} // namespace Gyro

/*****************************************************************//**
 * @file   KnockBackComponent.cpp
 * @brief  �m�b�N�o�b�N�R���|�[�l���g�̒�`
 * 
 * @author �y������
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
      // ���[�V�������ȊO�͓����蔻��̍X�V���s��Ȃ�
      if (_state == KnockBackState::NonActive) {
        return false;
      }
      auto objects = _app.GetObjectServer().GetObjects();
      // Player�̍��W���擾
      auto pPos = _owner.GetPosition();
      _cnt--;
      if (_cnt > 0) {
        std::shared_ptr <Enemy::EnemyBase> enemy = nullptr;
        for (auto obj : objects) {
          if (obj->GetId() != ObjectBase::ObjectId::Enemy) continue;
          enemy = std::dynamic_pointer_cast<Enemy::EnemyBase>(obj);
          if (enemy.get()->GetEnemyState() != Enemy::EnemyBase::EnemyState::Attack) continue;
          auto knockBackVector = pPos - enemy->GetPosition();
          // ����������Ȃ��̂ł��ȊO�𕪉����Ď��o��
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

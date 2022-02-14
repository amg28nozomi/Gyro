#include "AttackComponent.h"
#include "ObjectBase.h"
#include "CollisionCapsule.h"

namespace Gyro {
  namespace Object {

    AttackComponent::AttackComponent(ObjectBase& owner, std::shared_ptr<CollisionBase> collision) : _owner(owner) {
      // �U������p�̃R���W���������Z�b�g
      _collision = std::move(collision);
    }

    bool AttackComponent::Process(const AppMath::Vector4& localPosition) {
      // ���W�X�V
      auto pos = LocalToWorld(AppMath::Vector4()) * localPosition;
      // �ړ��ʕ��A�����蔻��̍X�V���s��
      _collision->SetPosition(pos);
      // �����蔻����̍X�V
      _collision->Process();
      return true;
    }

    AppMath::Matrix44 AttackComponent::LocalToWorld(const AppMath::Vector4& local) const {
      auto position = _owner.GetPosition() + local;
      // ���[���h�ϊ��s��̎擾
#ifndef _DEBUG
      return AppMath::Utility::ToWorldMatrix(position, _owner.GetRotation(), AppMath::Vector4(1.0f, 1.0f, 1.0f));
#else
      return AppMath::Utility::ToWorldMatrix(position, _owner.GetRotation(), AppMath::Vector4(1.0f, 1.0f, 1.0f), AppMath::Degree);
#endif
    }
  } // mamespace Object
} // namespace Gyro
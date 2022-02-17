/*****************************************************************//**
 * @file   AttackComponent.cpp
 * @brief  �U���R���|�[�l���g�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "AttackComponent.h"
#include "ObjectBase.h"
#include "CollisionCapsule.h"

namespace Gyro {
  namespace Object {

    AttackComponent::AttackComponent(ObjectBase& owner, std::shared_ptr<CollisionBase> collision) : _owner(owner) {
      _state = AttackState::NonActive;
      // �U������p�̃R���W���������Z�b�g
      _collision = std::move(collision);
    }

    void AttackComponent::Finish() {
      _state = AttackState::NonActive;
      _collision->SetPosition(_owner.GetPosition());
    }

    bool AttackComponent::Process(const AppMath::Vector4& localPosition) {
      // ���[�V�������ȊO�͓����蔻��̍X�V���s��Ȃ�
      if (_state == AttackState::NonActive) {
        return false;
      }
      auto pos = localPosition;
      // ���W�X�V
      // auto pos = LocalToWorld(_owner.GetPosition()) * localPosition;
      // �ړ��ʕ��A�����蔻��̍X�V���s��
      _collision->SetPosition(pos);
      // �����蔻����̍X�V
      _collision->Process();
      return true;
    }

#ifdef _DEBUG
    void AttackComponent::Draw() const {
      // �U�����蒆�̂ݓ����蔻��̕`������s����
      if (_state == AttackState::Active) {
        _collision->Draw();
      }
    }
#endif

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
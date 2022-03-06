/*****************************************************************//**
 * @file   AttackComponent.cpp
 * @brief  �U���R���|�[�l���g�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#include "AttackComponent.h"
#include "ObjectBase.h"
#include "CollisionBase.h"
#include "ApplicationMain.h"

namespace Gyro {
  namespace Object {

    AttackComponent::AttackComponent(ObjectBase& owner, std::shared_ptr<CollisionBase> collision) : _owner(owner) {
      _state = AttackState::NonActive;
      // �U������p�̃R���W���������Z�b�g
      _collision.emplace_back(std::move(collision));
    }

    AttackComponent::AttackComponent(ObjectBase& owner, std::vector<std::shared_ptr<CollisionBase>> collisions) : _owner(owner) {
      _state = AttackState::NonActive;
      // �U������p�̃R���W���������Z�b�g
      _collision = collisions;
    }

    void AttackComponent::Finish() {
      _state = AttackState::NonActive;
      // �U��������C������
      for (auto collision : _collision) {
        collision->SetPosition(_owner.GetPosition());
      }
      _indexs.clear(); // �t���[�����̍폜
    }

    bool AttackComponent::Process(const AppFrame::Math::Vector4& localPosition) {
      // ���[�V�������ȊO�͓����蔻��̍X�V���s��Ȃ�
      if (_state == AttackState::NonActive) {
        return false;
      }
      auto pos = localPosition;
      // ���W�X�V
      // �ړ��ʕ��A�����蔻��̍X�V���s��
      _collision.front()->SetPosition(pos);
      // �����蔻����̍X�V
      _collision.front()->Process();
      return true;
    }

    bool AttackComponent::Process() {
      // ���[�V�������ȊO�͓����蔻��̍X�V���s��Ȃ�
      if (_state == AttackState::NonActive) {
        return false;
      }
      // �Z�b�g���ꂽ�t���[���񕪔�����s��
      for (auto num = 0; auto frame : _indexs) {
        // �����蔻����W���Z�b�g����
        _collision.at(num)->SetPosition(_owner.GetFramePosition(frame));
        // �R���W�����̍X�V
        _collision.at(num)->Process();
      }
      return true; // ����I��
    }

    void AttackComponent::SetFrame(std::vector<int> frames, std::vector<std::shared_ptr<CollisionBase>> collisions) {
      // �t���[���ԍ��̐؂�ւ�
      _indexs = frames;
      // �R���W�������̐؂�ւ�
      _collision = collisions;
    }

#ifdef _DEBUG
    void AttackComponent::Draw() const {
      // �U�����蒆�̂ݓ����蔻��̕`������s����
      if (_state == AttackState::Active) {
        for (auto collision : _collision) {
          collision->Draw();
        }
      }
    }
#endif

    AppFrame::Math::Matrix44 AttackComponent::LocalToWorld(const AppFrame::Math::Vector4& local) const {
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
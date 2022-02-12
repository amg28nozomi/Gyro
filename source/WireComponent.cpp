#include "WireComponent.h"
#include "ObjectBase.h"

namespace Gyro {
  namespace Player {

    WireComponent::WireComponent(Object::ObjectBase& owner) : _owner(owner) {
      _type = ComponentType::Wire;
    }

    bool WireComponent::SetTarget(const Vector4& target) {
      // ���L�҂̌��ݍ��W�ƃ^�[�Q�b�g���W���狗���ƌ������Z�o
      auto v = target - _owner.GetPosition();
      // �����x�N�g�����X�V����
      _forward = Vector4::Normalize(v);
      // �ړ��ʂ��Z�o����
      return false;
    }

    AppMath::Matrix44 WireComponent::Move() const {
      return AppMath::Matrix44::Translate(_forward);
    }

  } // namespace Player
} // namespace Gyro
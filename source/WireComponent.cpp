#include "WireComponent.h"
#include "ObjectBase.h"

namespace Gyro {
  namespace Player {

    WireComponent::WireComponent(Object::ObjectBase& owner) : _owner(owner) {
      _type = ComponentType::Wire;
    }

    bool WireComponent::SetTarget(const Vector4& target, const float time) {
      // �ړ����Ԃ�ݒ�
      _time = time;
      // ���L�҂̌��ݍ��W���J�n���W�ɂ���
      _start = _owner.GetPosition();
      // ���L�҂̌��ݍ��W�ƃ^�[�Q�b�g���W���狗���ƌ������Z�o
      _target = target;
      // �����x�N�g�����X�V����
      _forward = Vector4::Normalize(_start - _owner.GetPosition());
      // �ړ��ʂ��Z�o����
      return false;
    }

    Vector4 WireComponent::WireMove() const {
      auto v = (_target - _start) / _time; // �ړ���
      return v;
    }

  } // namespace Player
} // namespace Gyro
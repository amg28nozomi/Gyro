/*****************************************************************//**
 * @file   WireComponent.cpp
 * @brief  ���C���[�A�N�V�����@�\�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   April 2022
 *********************************************************************/
#include "WireComponent.h"
#include "ObjectBase.h"

namespace Gyro {
  namespace Player {

    WireComponent::WireComponent(Object::ObjectBase& owner) : _owner(owner) {
      _type = ComponentType::Wire;
    }

    void WireComponent::Start() {
      _wire = true;
      // ���L�҂̏d�͏����𖳌�������
      _owner.GravitySet(false);
    }

    void WireComponent::Finish() {
      _wire = false;
      // ���L�҂̏d�͏�����L���ɂ���
      _owner.GravitySet(true);
    }

    bool WireComponent::SetTarget(const Vector4& target, const float speed) {
      // �ړ����Ԃ�ݒ�
      _speed = speed;
      // ���L�҂̌��ݍ��W���J�n���W�ɂ���
      _start = _owner.GetPosition();
      // ���L�҂̌��ݍ��W�ƃ^�[�Q�b�g���W���狗���ƌ������Z�o
      _target = target;
      // �����x�N�g�����X�V����
      _forward = Vector4::Normalize(_start - _owner.GetPosition());
      // �ړ��ʂ��Z�o����
      return false;
    }

    Vector4 WireComponent::WireMove() {
      // �������̎擾
      _forward = Vector4::Normalize(_target - _owner.GetPosition());
      // �����x�N�g����0�̏ꍇ�͏������s��Ȃ�
      if (_forward.LengthSquared() == 0.0f) {
        _wire = false;
        return Vector4(); // ������Ԃ�
      }
      // ���������p�x�ɕϊ�
      return _forward * _speed; // �ړ��ʂ�Ԃ�
    }
  } // namespace Player
} // namespace Gyro
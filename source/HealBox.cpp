/*****************************************************************//**
 * @file   HealBox.cpp
 * @brief  �񕜃{�b�N�X�N���X�̒�`
 * 
 * @author ��؊�C
 * @date   March 2022
 *********************************************************************/
#include "HealBox.h"
#include "ApplicationMain.h"
#include "CollisionAABB.h"
#include "CollisionCapsule.h"
#include "EffectComponent.h"

namespace Gyro {
  namespace Object {

    HealBox::HealBox(Application::ApplicationMain& app) : ObjectBase(app) {
      _state = ObjectState::Active;
    }

    bool HealBox::Process() {
      // ���N���X���̍X�V�������Ăяo��
      ObjectBase::Process();
      // �Đ����Ԃ�������������ꍇ
      if (_totalTime <= 0.0f) {
        // ���S��ԂɑJ�ڂ���
        _state = ObjectState::Dead;
        return true;
      }
      // �������Ԃ�����������
      _totalTime -= _speed;
      return true;
    }

    bool HealBox::IsInvasion(const CollisionCapsule& capsule) const {
      // �J�v�Z����AABB�̏Փ˔�����s��
      return false;
    }

    bool HealBox::SetParam(const AppMath::Vector4& position, const float totalTime, const float speed) {
      // �ݒ�͊��ɍs���Ă��邩
      if (_speed) {
        return false; // ���ɓo�^����Ă���
      }
      // ���W�̐ݒ�
      _position = position;
      // �����蔻����̐���

      // �Đ����ԂƍĐ����x�̐ݒ�
      _totalTime = totalTime;
      _speed = speed;
      return true;
    }
  } // namespace Object
} // 

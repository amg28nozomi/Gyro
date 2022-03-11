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
#include "ObjectServer.h"
#include "Player.h"

namespace Gyro {
  namespace Object {

    HealBox::HealBox(Application::ApplicationMain& app) : ObjectBase(app) {
      _id = ObjectId::Field;
      _state = ObjectState::Active;
      _healPoint = 300.0f / 600.0f;
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
      // ���@���񕜂�����
      HealPlayer();
      return true;
    }

    bool HealBox::IsInvasion(const CollisionCapsule& capsule, float& heal) const {
      const auto [min, max] = capsule.LineSegment().GetVector();
      if (_collision->CheckPoint(min) || _collision->CheckPoint(max)) {
        // �񕜗ʂ�Ԃ�
        heal = _healPoint;
        return true;
      }
      return false;
    }

    bool HealBox::HealPlayer() {
      // ���@�̎擾
      auto player = _app.GetObjectServer().GetPlayer();
      // �擾�Ɏ��s�����ꍇ�̓X�L�b�v
      if (player == nullptr) return false;
      // �ڐG���Ă���ꍇ�͎��@���񕜂���
      if (_collision->CheckPoint(player->GetPosition())) {
        // �񕜏������J�n����
        player->Heal(_healPoint);
        return true;
      }
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

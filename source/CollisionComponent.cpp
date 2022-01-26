/*****************************************************************//**
 * @file   CollisionComponent.cpp
 * @brief  �Փ˔��菈�����s���R���|�[�l���g�N���X�̒�`
 *
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#include "CollisionComponent.h"
#include "CollisionBase.h"
#include "ObjectBase.h"

namespace Gyro {
  namespace Object {

    CollisionComponent::CollisionComponent(ObjectBase& obj) : _owner(obj) {
      // �����蔻��̐ݒ���s��

    }
    

    bool CollisionComponent::SetCollision(std::unique_ptr<CollisionBase> collision) {
      // ������null�̏ꍇ�͓o�^���s��Ȃ�
      if (collision == nullptr) {
        return false; // �ݒ莸�s
      }
      // ���̂�����ꍇ�͓o�^����
      _collision = std::move(collision);
      return true;    // �ݒ芮��
    }
  } // namespace Object
} // namespace Gyro
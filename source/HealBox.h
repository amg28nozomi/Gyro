/*****************************************************************//**
 * @file   HealBox.h
 * @brief  �񕜃{�b�N�X�N���X
 * 
 * @author ��؊�C
 * @date   March 2022
 *********************************************************************/
#pragma once
#include "ObjectBase.h"

namespace Gyro {
  /**
   * @brief �R���W�����x�[�X
   */
  namespace Object {
    class CollisionCapsule;
    class CollisionAABB;
  } // namespace Collision
  namespace Object {
    /**
     * @class HealBox
     * @brief �񕜃{�b�N�X�N���X
     */
    class HealBox : public ObjectBase {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      HealBox(Application::ApplicationMain& app);
      /**
       * @brief  ���W�̐ݒ�
       * @param  totalTime ���Đ�����
       * @param  speed     �Đ����x
       * @return 
       */
      bool SetParam(const AppMath::Vector4& position, const float totalTime, const float speed);
      /**
       * @brief �����蔻��̓o�^
       * @param collision �R���W�������
       */
      inline void SetCollision(std::unique_ptr<Object::CollisionAABB> collision) {
        _collision = std::move(collision);
      }
      /**
       * @brief  �X�V����
       * @return true
       */
      bool Process() override;
      /**
       * @brief  �Ώۂ��񕜔�����ɑ��݂��邩�̔���
       * @return true:���݂��� false:���݂��Ȃ�
       */
      bool IsInvasion(const CollisionCapsule& capsule) const;
      /**
       * @brief  �񕜃|�C���g�̎擾
       * @return �񕜗�
       */
      float HealPoint() const {
        return _healPoint;
      }
    private:
      //!< �Փ˔�����
      std::unique_ptr<Object::CollisionAABB> _collision{nullptr};
      //!< �Đ����x
      float _speed{0.0f};
      //!< ��������
      float _totalTime{0.0f};
      //!< �񕜗�
      float _healPoint{0.0f};
    };
  } // namespace Object
} // 
/*****************************************************************//**
 * @file   CollisionComponent.h
 * @brief  �Փ˔��菈�����s���R���|�[�l���g�N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <memory>
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    class ObjectBase;    //!< �I�u�W�F�N�g�x�[�X�̑O���錾
    class CollisionBase; //!< �R���W�����x�[�X�̑O���錾
    /**
     * @class CollisionComponent
     * @brief �����蔻�菈�����s���R���|�[�l���g
     */
    class CollisionComponent {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param owner �ΏۃI�u�W�F�N�g�̎Q��
       */
      CollisionComponent(ObjectBase& owner);
      /**
       * @brief �����蔻��̓o�^
       * @param collision CollisionBase�̃��j�[�N�|�C���^
       */
      bool SetCollision(std::unique_ptr<CollisionBase> collision);
    private:
      ObjectBase& _owner; //!< ���L�҂̎Q��
      std::unique_ptr<CollisionBase> _collision{nullptr}; //!< �Փ˔�����
    };
  }
} // namespace Gyro
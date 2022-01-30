/*****************************************************************//**
 * @file   CollisionBase.h
 * @brief  �����蔻��p���̊��N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once

namespace AppFrame::Math {
  class Vector4;
}
 /**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    namespace AppMath = AppFrame::Math;
    class ObjectBase;
    /**
     * @class CollisionBase
     * @brief �����蔻����̊��N���X
     */
    class CollisionBase {
    public:
      /**
       * @brief �����蔻��̊��N���X
       * @param owner ���L�҂̎Q��
       */
      CollisionBase(ObjectBase& owner);
      /**
       * @brief �����蔻��̍X�V
       */
      virtual void Process();
      /**
       * @brief �����蔻��̕`��
       */
      virtual void Draw();
      /**
       * @brief  �Փ˔���
       * @return true:�Փ˗L�� false:�Փ˂Ȃ�
       */
      virtual bool IsHit();
      /**
       * @brief �Փ˔���t���O�̐ݒ�
       * @param flag �����t���O(true:�Փ˔�����s�� false:�Փ˔�����s��Ȃ�)
       */
      void SetHitFlag(const bool flag) {
        _hit = flag;
      }
    protected:
      ObjectBase& _owner; //!< ���L�҂̎Q��
      AppMath::Vector4 _position{}; //!< ���[�J�����W
      bool _hit{true}; //!< �Փ˔���t���O(true:�L�� false:��L��)
    };
  } // namespace Object
} // namespace Gyro


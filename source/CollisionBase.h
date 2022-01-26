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
  class Matrix44;
}
 /**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    namespace AppMath = AppFrame::Math; //!< ���O��Ԃ̏ȗ�
    class ObjectBase; //!< �O���錾
    /**
     * @class CollisionBase
     * @brief �����蔻����
     */
    class CollisionBase {
    public:
      /**
       * @brief �R���W�����̎�ނ�\���񋓌^�N���X
       */
      enum class CollisionType {
        Null,  // �Y���Ȃ�
        Line,  // ����
        Sphere // ��
      };
      /**
       * @brief �R���X�g���N�^
       * @param owner ���L�҂̎Q��
       */
      CollisionBase(ObjectBase& owner);
      /**
       * @brief �����蔻��̍X�V
       */
      virtual void Process();
#ifdef _DEBUG
      /**
       * @brief �f�o�b�O�p�̓����蔻��`��
       */
      virtual void Draw();
#endif
      /**
       * @brief  �R���W�������m�̏Փ˔���
       * @tparam Collision �R���W�����N���X�̎Q��
       * @param  left  ����R���W�����̎Q��
       * @param  right ����R���W�����̎Q��
       * @return true:�Փ˂��� false:�Փ˂��Ă��Ȃ�
       */
      template <class Collision>
      bool IsHit(Collision& left, Collision& right);
      /**
       * @brief  �����蔻��̎�ނ��擾����
       * @return �R���W�����^�C�v
       */
      inline CollisionType GetCollisionType() const {
        return _type;
      }
    protected:
      //!< �R���W�����^�C�v
      CollisionType _type{CollisionType::Null};
      ObjectBase& _owner;  //!< ���L�҂̎Q��
      AppMath::Vector4 _position; //!< ���[�J�����W
      AppMath::Vector4 _rotation; //!< ����
      AppMath::Vector4 _scale;    //!< �g�嗦
      /**
       * @brief  ���[���h���W�s��̎擾
       * @return ���[���h���W�s��
       */
      AppMath::Matrix44 WorldMatrix() const;
    };

    template <class Collision>
    bool CollisionBase::IsHit(Collision& left, Collision& right) {
      return true;
    }
  } // namespace Object
} // namespace Gyro
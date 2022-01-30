/*****************************************************************//**
 * @file   CollisionBase.h
 * @brief  �����蔻��p���̊��N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "appframe.h"

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
       * @brief �����蔻��̎�ނ�\���񋓌^�N���X
       */
      enum class CollisionType {
        None,   // �Y���Ȃ�
        Line,   // ����
        Sphere, // ��
      };
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
       * @brief �����蔻��̍X�V
       * @param vector 
       */
      virtual void Process(AppMath::Vector4 vector);
#ifdef _DEBUG
      /**
       * @brief �����蔻��̕`��
       */
      virtual void Draw();
      /**
       * @brief �f�o�b�O���̐؂�ւ�
       */
      inline void ChangeDebugFlag() {
        _debug = !_debug;
      }
#endif
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
      /**
       * @brief  �R���W�����^�C�v�̎擾
       * @return �R���W�����^�C�v��Ԃ�
       */
      CollisionType GetType() const {
        return _type;
      }
    protected:
      //!< �R���W�����̎��
      CollisionType _type{CollisionType::None};
      //!< ���L�҂̎Q��
      ObjectBase& _owner;
      //!< ���[�J�����W
      AppMath::Vector4 _position;
      //!< �Փ˔���t���O(true:�L�� false:��L��)
      bool _hit{true};
#ifdef _DEBUG
      //!< �f�o�b�O���t���O
      bool _debug{false};
#endif
    };
  } // namespace Object
} // namespace Gyro


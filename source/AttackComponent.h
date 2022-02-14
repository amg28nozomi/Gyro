/*****************************************************************//**
 * @file   AttackComponent.h
 * @brief  �U���p�R���|�[�l���g�N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"
#include "CollisionBase.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    class ObjectBase; //!< �I�u�W�F�N�g�x�[�X
    /**
     * @class AttackComponent
     * @brief �U���p�R���|�[�l���g
     */
    class AttackComponent : public ObjectComponent {
    public:
      /**
       * @brief �U����Ԃ�\���񋓌^�N���X
       */
      enum class AttackState {
        NonActive, // �m�[�A�N�V����
        Active,    // �������
        Damega     // �_���[�W�t���[���L��
      };
      /**
       * @brief  �R���X�g���N�^
       * @param  owner     ���L�҂̎Q��
       * @param  collision �����蔻��̃V�F�A�[�h�|�C���^
       */
      AttackComponent(ObjectBase& owner, std::shared_ptr<CollisionBase> collision);
      /**
       * @brief �U������̊J�n
       */
      void Start() override{}
      /**
       * @brief �U������̏I��
       */
      void Finish() override{}
      /**
       * @brief  �U������̍X�V
       * @param  localPosition ���[�J�����W
       * @return true:����I�� false:��蔭��
       */
      virtual bool Process(const AppMath::Vector4& localPosition);
      /**
       * @brief  �U����Ԃ̎擾
       * @return �U�����
       */
      const AttackState& GetState() {
        return _state;
      }
      /**
       * @brief  �����蔻����̎擾
       * @return �����蔻����
       */
      const std::shared_ptr<CollisionBase>& GetCollision()  {
        return _collision;
      }
    protected:
      //!< ���L�҂̎Q��
      ObjectBase& _owner;
      //!< �U�����
      AttackState _state;
      //!< �U���p�����蔻����
      std::shared_ptr<CollisionBase> _collision;
      //!< �U�����莞��
      float _time;
      /**
       * @brief ���[�J�����W�����[���h���W�ɕϊ�����
       */
      AppMath::Matrix44 LocalToWorld(const AppMath::Vector4& local) const;
    };
  } // mamespace Object
} // namespace Gyro
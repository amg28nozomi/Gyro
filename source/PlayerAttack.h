/*****************************************************************//**
 * @file   PlayerAttack.h
 * @brief  ���@�̍U�������N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "AttackComponent.h"
  
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �v���C���[�x�[�X
   */
  namespace Player {
    /**
     * @class  PlaterAttack
     * @brief  ���@�̍U�������N���X
     */
    class PlayerAttack : public Object::AttackComponent {
    public:
      /**
       * @brief �U���̎�ނ�\���񋓌^�N���X
       */
      enum class AttackType {
        None,  //!< �Ȃ�
        Light, //!< ��U��
        Heavy, //!< ���U��
        Trick  //!< �g���b�N
      };
      /**
       * @brief �R���X�g���N�^
       * @param owner ���L�҂̔���
       */
      PlayerAttack(Object::ObjectBase& owner);
      /**
       * @brief �J�n����
       */
      void Start() override;
      /**
       * @brief �I������
       */
      void Finish() override;
      /**
       * @brief  �U����Ԃ̎擾
       * @return �U�����
       */
      AttackType GetAttackType() const {
        return _attackType;
      }
    private:
      //!< �U���̎��
      AttackType _attackType{AttackType::None};
      //!< �`�F�C���J�E���g
      int _chain{0};
    };
  } // namespace Player
} // namespace Gyro
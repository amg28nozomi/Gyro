/*****************************************************************//**
 * @file   PlayerAttack.h
 * @brief  ���@�̍U�������N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "AttackComponent.h"
#include <unordered_map>
  
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �v���C���[�x�[�X
   */
  namespace Player {

    //class PlayerAttackData; //!< �O���錾
    ///**
    // * @class  PlaterAttack
    // * @brief  ���@�̍U�������N���X
    // */
    //class PlayerAttack : public Object::AttackComponent {
    //public:
    //  /**
    //   * @brief �U���̎�ނ�\���񋓌^�N���X
    //   */
    //  enum class AttackType {
    //    None,   //!< �Ȃ�
    //    Light1, //!< ��U��1
    //    Light2, //!< ��U��2
    //    Light3, //!< ��U��3
    //    Heavy1, //!< ���U��1
    //    Heavy2, //!< ���U��2
    //    Heavy3, //!< ���U��3
    //    Trick   //!< �g���b�N
    //  };
    //  /**
    //   * @brief �R���X�g���N�^
    //   * @param owner ���L�҂̔���
    //   */
    //  PlayerAttack(Object::ObjectBase& owner);
    //  /**
    //   * @brief �J�n����
    //   */
    //  void Start() override;
    //  /**
    //   * @brief �I������
    //   */
    //  void Finish() override;
    //  /**
    //   * @brief  �U����Ԃ̎擾
    //   * @return �U�����
    //   */
    //  AttackType GetAttackType() const {
    //    return _attackType;
    //  }
    //private:
    //  //!< �U����Ԃ��L�[�Ƃ��āA�U�������Ǘ�����A�z�z��
    //  std::unordered_map<AttackType, PlayerAttackData> _registry;
    //  //!< �U���̎��
    //  AttackType _attackType{AttackType::None};
    //  //!< �`�F�C���J�E���g
    //  int _chain{0};
    //  /**
    //   * @brief  �U����Ԃ̐؂�ւ�
    //   * @param  attack
    //   * @return 
    //   */
    //  bool ChangeState(const AttackType& attack);
    //  /**
    //   * @brief �f�[�^�x�[�X�̐���
    //   */
    //  void CreateRegistry();
    //};
  } // namespace Player
} // namespace Gyro
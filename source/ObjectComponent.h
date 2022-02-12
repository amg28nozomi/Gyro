/*****************************************************************//**
 * @file   ObjectComponentComponent.h
 * @brief  �I�u�W�F�N�g�p�@�\�̃X�[�p�[�N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    /**
     * @class ObjectComponent 
     * @brief �I�u�W�F�N�g�p�@�\�̊��N���X
     */
    class ObjectComponent {
    public:
      /**
       * @brief �@�\�̎�ނ�\���񋓌^�N���X
       */
      enum class ComponentType {
        None, // �Y���Ȃ�
        Jump, // �W�����v
        Wire  // ���C���[
      };
      /**
       * @brief �R���X�g���N�^
       */
      ObjectComponent();
      /**
       * @brief ����������
       */
      virtual void Init(){}
      /**
       * @brief �J�n����
       */
      virtual void Start() = 0;
      /**
       * @brief �I������
       */
      virtual void Finish(){}
      /**
       * @brief  �R���|�[�l���g�^�C�v�̎擾
       * @return �R���|�[�l���g�^�C�v
       */
      ComponentType GetType() const {
        return _type;
      }
    protected:
      ComponentType _type; //!< �@�\��\���񋓌^
    };
  } // namespace Player
} // namespace Gyro
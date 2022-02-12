/*****************************************************************//**
 * @file   JumpComponent.h
 * @brief  �W�����v�@�\�N���X
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
   * @brief �v���C���[�x�[�X
   */
  namespace Player {
    /**
     * @brief �W�����v����
     */
    class JumpComponent {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      JumpComponent() {}
      /**
       * @brief  �W�����v�̐ݒ�
       * @param  range  ���􋗗�
       * @param  frigth �΋󎞊�
       */
      void Set(const float range, const int frigth);
      /**
       * @brief �W�����v�����̊J�n
       */
      void Start();
      /**
       * @brief �W�����v�̏I��
       */
      void Finish();
      /**
       * @brief  �W�����v�͂̎擾
       * @return �W�����v��
       */
      float JumpPower();
      /**
       * @brief �J�E���^�̏�����
       */
      inline void CountClear() {
        _count = 0;
      }
      /**
       * @brief  ���΋󎞊Ԃ̎擾
       * @return ���΋󎞊�(�J�E���g)
       */
      int Fright() const {
        return _fright;
      }
      /**
       * @brief  �o�߃t���[���̎擾
       * @return �o�߃t���[��
       */
      int Count() const {
        return _count;
      }
      /**
       * @brief  ���ݐݒ肳��Ă���΋󎞊Ԃ̎擾
       * @return �΋󎞊�
       */
      float Range() const {
        return _range;
      }
      /**
       * @brief  �W�����v�t���O�̎擾
       * @return �W�����v�t���O
       */
      bool IsJump() const {
        return _jump;
      }
    protected:
      int _fright{0};     //!< ���΋󎞊�
      int _count{0};      //!< �o�߃J�E���^
      float _range{0.0f}; //!< ���􋗗�
      int _f{0};
      bool _jump{false};  //!< �W�����v�t���O
    };
  } // namespace Player
} // namespace Gyro
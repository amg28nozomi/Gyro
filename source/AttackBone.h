/*****************************************************************//**
 * @file   AttackBone.h
 * @brief  �U������Ŏg�p����{�[�����N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <vector>

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    /**
     * @class  AttackBone
     * @brief  �A�^�b�N�{�[�����
     */
    class AttackBone {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      AttackBone();
      /**
       * @brief  �{�[��
       * @param  bone �{�[���ԍ�
       */
      AttackBone(int bone);

      AttackBone(int a, int b);
      /**
       * @brief  �{�[�����̎擾
       * @return �{�[�����
       */
      std::vector<int> GetBone() const {
        return _bone;
      }
    protected:
      std::vector<int> _bone; //!< �{�[�����
    };
  } // namespace Object
} // namespace Gyro
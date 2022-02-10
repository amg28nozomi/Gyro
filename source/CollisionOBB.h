/*****************************************************************//**
 * @file   CollisionOBB.h
 * @brief  �L���o�E���f�B���O�{�b�N�X�̏Փ˔���N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "CollisionBase.h"
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    /**
     * @class 
     * @brief
     */
    class CollisionOBB : public CollisionBase {
      /**
       * @brief �R���X�g���N�^
       * @param  owner    ���L�҂̎Q��
       * @param  position ���W
       * @param  rotation ����
       * @param  scale    �X�P�[��
       */
      CollisionOBB(ObjectBase& owner, AppMath::Vector4 position, AppMath::Vector4 rotation, AppMath::Vector4 scale);

      bool CheckLineSegment(const AppMath::LineSegment& segment);
    private:
      AppMath::Matrix44 _matrix;  //!< �s��
      AppMath::Matrix44 _inverse; //!< �t�s��
    };
  } // namespace Object
} // namespace Gyro
/*****************************************************************//**
 * @file   CollisionAABB.h
 * @brief  �����s�o�E���f�B���O�{�b�N�X�̏Փ˔���N���X
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
     * @class CollisionAABB
     * @brief �����s�o�E���f�B���O�{�b�N�X�̏Փ˔���N���X
     */
    class CollisionAABB : public CollisionBase {
      /**
       * @brief �R���X�g���N�^
       * @param owner ���L�҂̎Q��
       * @param min   �ŏ��_�x�N�g��
       * @param max   �ő�_�x�N�g��
       */
      CollisionAABB(ObjectBase& owner, const AppMath::Vector4& min, const AppMath::Vector4& max);
      /**
       * @brief �����蔻��̍X�V
       * @param point ���S���W
       */
      void Process(const AppMath::Vector4& point);

#ifdef _DEBUG
      /**
       * @brief �����蔻��̕`��
       */
       // void Draw() override;
#endif
      /**
       * @brief  �_���W�̕�ܔ���
       * @param  point �_���W
       */
      bool CheckPoint(const AppMath::Vector4& point);
      /**
       * @brief  �����Ƃ̏Փ˔���
       * @param  segment �����̎Q��
       * @return true:�Փ� false:�Փ˂��Ă��Ȃ�
       */
      bool CheckLineSegment(const AppMath::LineSegment& segment);
    private:
      AppMath::Vector4 _max; // �ő�_
    };
  } // namespace Object
} // namespace Gyro
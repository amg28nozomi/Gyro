/*****************************************************************//**
 * @file   WirePoint.h
 * @brief  ���C���[�A�N�V�����̊�_���N���X
 * 
 * @author ��؊�C
 * @date   March 2022
 *********************************************************************/
#pragma once
#include <appframe.h>
#include "CollisionAABB.h"

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    namespace AppMath = AppFrame::Math; //!< ���O��Ԃ̏ȗ�
    /**
     * @class WirePoint
     * @brief ���C���[�A�N�V�����p�̍��W
     */
    class WirePoint {
    public:
      /**
       * @brief �R���X�g���N�^
       * @param point ���S���W
       * @param target �Ή�����|�C���g���
       */
      WirePoint(const AppMath::Vector4& point, WirePoint& target);
      /**
       * @brief  �_���W�̎擾
       * @return �_���W���
       */
      AppMath::Vector4 Point() const {
        return _position;
      }
      /**
       * @brief  �R���W�������̎擾
       * @return ����p�{�b�N�X
       */
      CollisionAABB& Collision() const {
        return *_box;
      }
    private:
      //!< �΂ƂȂ���W
      WirePoint& _target;
      //!< ���[���h���W
      AppMath::Vector4 _position;
      //!< ����p�{�b�N�X
      std::unique_ptr<CollisionAABB> _box;
    };
  } // namespace Object
} // namespace Gyro
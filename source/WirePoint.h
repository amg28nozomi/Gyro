#pragma once
#include <appframe.h>
#include "CollisionAABB.h"

namespace Gyro {
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
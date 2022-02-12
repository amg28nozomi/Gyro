#pragma once
#include "ObjectComponent.h"

namespace AppFrame {
  namespace Math {
    class Vector4;
  }
}

namespace Gyro {
  namespace Object {
    class ObjectBase;
    /**
     * @brief �ړ��R���|�[�l���g
     */
    class MoveComponent : public ObjectComponent {
      using Vector4 = AppFrame::Math::Vector4;
    public:
      /**
       * @brief �R���X�g���N�^
       * @param owner ���L��
       */
      MoveComponent(ObjectBase& owner);
      /**
       * @brief �ړ��ʂ̐ݒ�
       * @param speed
       */
      void Set(const float speed) {
        _speed = speed;
      }
      /**
       * @brief  �ړ��ʂ̎Z�o(���@�p)
       * @param  move �A�i���O�X�e�B�b�N�̓��͏��x�N�g��
       * @return �ړ��x�N�g��
       */
      Vector4 Move(const Vector4& move) const;
    private:
      float _speed;
    };
  } // namespace Object
} // namespace Gyro
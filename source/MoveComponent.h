#pragma once
#include "ObjectComponent.h"
#include <appframe.h>

namespace Gyro {
  namespace Object {
    class ObjectBase;
    namespace AppMath = AppFrame::Math;
    /**
     * @brief �ړ��R���|�[�l���g
     */
    class MoveComponent : public ObjectComponent {
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

      void Start() override;

      void Finish() override;
      /**
       * @brief  �ړ��ʂ̎Z�o(���@�p)
       * @param  move �A�i���O�X�e�B�b�N�̓��͏��x�N�g��
       * @return �ړ��x�N�g��
       */
      AppMath::Vector4 Move(const AppMath::Vector4& move);

      AppMath::Matrix44 GetTranslate() {
        return AppMath::Matrix44::Translate(_move);
      }

      AppMath::Vector4 MoveVector() const {
        return _move;
      }
    private:
      ObjectBase& _owner;
      AppMath::Vector4 _move{}; //!< �ړ��x�N�g��
      float _speed;  //!< ���x
    };
  } // namespace Object
} // namespace Gyro
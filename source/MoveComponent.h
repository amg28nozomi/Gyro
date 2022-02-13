/*****************************************************************//**
 * @file   MoveComponent.h
 * @brief  �ړ��R���|�[�l���g�N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"
#include <appframe.h>

/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
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
       * @brief  �ړ��ʂ̍X�V
       * @param  x x���̓��͏��
       * @param  z z���̓��͏��
       * @return true:�ړ��ʗL�� false:�ړ��ʖ���
       */
      bool Move(const float x, const float z);
      /**
       * @brief  �ړ���(���s�ړ��s��)�̎擾
       * @return ���s�ړ��s��
       */
      AppMath::Matrix44 MoveTranslate() {
        return AppMath::Matrix44::Translate(_move);
      }
      /**
       * @brief  �ړ���(�x�N�g��)�̎擾
       * @return �ړ��ʃx�N�g��
       */
      AppMath::Vector4 MoveVector() const {
        return _move;
      }
    private:
      ObjectBase& _owner;       //!< ���L�҂̎Q��
      AppMath::Vector4 _move{}; //!< �ړ��x�N�g��
      float _speed;  //!< ���x
    };
  } // namespace Object
} // namespace Gyro
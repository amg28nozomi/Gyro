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
      /**
       * @brief �ړ������̊J�n
       */
      void Start() override;
      /**
       * @brief �ړ������̍X�V
       */
      void Finish() override;
      /**
       * @brief �O�t���[�����W�̍X�V
       */
      void OldPosition();
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
       * @brief  ���L�҂̑O�t���[�����W�̎擾
       * @return ���L�҂̑O�t���[�����W
       */
      AppMath::Vector4 OldPosition() const {
        return _oldPosition;
      }
      /**
       * @brief  �ړ���(�x�N�g��)�̎擾
       * @return �ړ��ʃx�N�g��
       */
      AppMath::Vector4 MoveVector() const {
        return _move;
      }
    private:
      //!< ���L�҂̎Q��
      ObjectBase& _owner;
      //!< ���L�҂̑O�t���[�����W
      AppMath::Vector4 _oldPosition{};
      //!< �ړ��x�N�g��
      AppMath::Vector4 _move{};
      //!< ���x
      float _speed;
    };
  } // namespace Object
} // namespace Gyro
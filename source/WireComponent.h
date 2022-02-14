/*****************************************************************//**
 * @file   WireComponent.h
 * @brief  ���C���[�A�N�V�����@�\�N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectComponent.h"
#include <appframe.h>

namespace Gyro {
  namespace Object {
    class ObjectBase;
  }
  namespace Player {
    namespace AppMath = AppFrame::Math;
    using Vector4 = AppMath::Vector4;
    /**
     * @class 
     * @brief ���C���[�A�N�V�����@�\
     */
    class WireComponent : public Object::ObjectComponent {
    public:

      WireComponent(Object::ObjectBase& owner);
      /**
       * @brief  �^�[�Q�b�g���W�̐ݒ�
       * @param  target �Ώۂ̍��W�x�N�g��
       * @param  time   �ړ�����
       * @return true:�ݒ萬�� false:�ݒ莸�s
       */
      bool SetTarget(const Vector4& target, const float time);
      /**
       * @brief �J�n����
       */
      void Start() override;
      /**
       * @brief �I������
       */
      void Finish() override;
      /**
       * @brief  
       * @return 
       */
      Vector4 WireMove();
      /**
       * @brief  ���C���[�A�N�V���������̔���
       * @return true:�A�N�V������ false:�A�N�V�����O
       */
      bool IsAction() const {
        return _wire;
      }
      /**
       * @brief  �ڕW�n�_�̎擾
       * @return �ڕW�n�_
       */
      Vector4 Target() const {
        return _target;
      }
    private:
      //!< ���L�҂̎Q��
      Object::ObjectBase& _owner;
      //!< �A�N�V�����J�n���W
      Vector4 _start{};
      //!< �^�[�Q�b�g���W
      Vector4 _target{};
      //!< �^�[�Q�b�g�ւ̌���
      Vector4 _forward{};
      //!< �ړ�����
      float _time{0.0f};
      //!< ���C���[�A�N�V�����t���O
      bool _wire{false};
    };
  } // namespace Player
} // namespace Gyro
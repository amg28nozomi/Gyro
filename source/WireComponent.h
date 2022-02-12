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
       * @return true:�ݒ萬�� false:�ݒ莸�s
       */
      bool SetTarget(const Vector4& target);
      /**
       * @brief �J�n����
       */
      void Start() override;
      /**
       * @brief �I������
       */
      void Finish() override;

      AppMath::Matrix44 Move() const;
    private:
      //!< ���L�҂̎Q��
      Object::ObjectBase& _owner;
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
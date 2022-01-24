/*****************************************************************//**
 * @file   CameraBase.h
 * @brief  �J�����x�[�X�N���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

namespace Gyro {

  namespace Object {
    class ObjectBase;
  } // namespace Object
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {

    namespace AppMath = AppFrame::Math;
    /**
     * @class CameraBase
     * @brief �J�����̊��N���X
     */
    class CameraBase {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      CameraBase(Object::ObjectBase& owner);
      /**
       * @brief ������
       */
      virtual void Init();
      /**
       * @brief �X�V����
       */
      virtual void Process();
    protected:
      Object::ObjectBase& _owner; //!< �J�����ۗ̕L��
      AppMath::Vector4 _position; //!< �J�������W
      AppMath::Vector4 _rotation; //!< �����_
      AppMath::Matrix44 _lookAt;  //!< �����s��

    };
  } // namespace Application
} // namespace Gyro
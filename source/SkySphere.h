/*****************************************************************//**
 * @file   SkySphere.h
 * @brief  �X�J�C�X�t�B�A�N���X
 * 
 * @author ��؊�C
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "ObjectBase.h"
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �I�u�W�F�N�g�x�[�X
   */
  namespace Object {
    /**
     * @class  SkySphere
     * @brief  �X�J�C�X�t�B�A�N���X
     */
    class SkySphere : public ObjectBase {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      SkySphere(Application::ApplicationMain& app, ObjectBase& owner);


    protected:
      ObjectBase& _owner; //!< ���L��
    };
  } // namespace Object
} // namespace Gyro
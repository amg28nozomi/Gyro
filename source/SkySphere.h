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
      /**
       * @brief ����������
       */
      bool Init() override;
      /**
       * @brief  �I�u�W�F�N�g�̐ݒ�
       * @param  spawn �������
       */
      void Set(Object::SpawnBase& spawn) override;
      /**
       * @brief  �X�V����
       * @return true:�X�V���� false:�X�V���s
       */
      bool Process() override;
      /**
       * @brief  �`�揈��
       */
      bool Draw() const override;
      /**
       * @brief  ���f���n���h���̐ݒ�
       * @param  key ���f���n���h���ɕR�Â���ꂽ������
       * @return true:�ݒ萬�� false:�ݒ莸�s
       */
      bool SetKey(std::string_view key);
      /**
       * @brief  �n���h���̎擾
       * @return ���f���n���h��
       */
      int GetHandle() const {
        return _handle;
      }
    protected:
      //!< ���L�҂̎Q��
      Object::ObjectBase& _owner;
      //!< ���f���n���h��
      int _handle;
    };
  } // namespace Interior
} // namespace Gyro
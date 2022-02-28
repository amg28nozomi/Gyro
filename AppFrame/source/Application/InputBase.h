/*****************************************************************//**
 * @file   InputBase.h
 * @brief  ���͏�Ԃ̊��N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <DxLib.h>
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �A�v���P�[�V����
   */
  namespace Application {
    constexpr auto Error = -1; // �������s
    /**
     * @class  InputBase
     * @brief  ���͏�ԃN���X
     */
    class InputBase {
    public:
      /**
       * @brief ���̓f�o�C�X�̎��
       */
      enum class DeviceType {
        Joypad,  //!< �W���C�p�b�h
        Mouse,   //!< �}�E�X
        Keyborad //!< �L�[�{�[�h
      };
      /**
       * @brief ���̓f�o�C�X�̏��
       */
      enum class State {
        Active,   //!< �ڑ��L��
        NonActive //!< �ڑ�����
      };
      /**
       * @brief  �R���X�g���N�^
       */
      InputBase();
      /**
       * @brief  �f�X�g���N�^
       */
      virtual ~InputBase();
      /**
       * @brief  �X�V����
       */
      virtual void Process() = 0;
      /**
       * @brief  �f�o�C�X�^�C�v�̎擾
       * @return �f�o�C�X�^�C�v
       */
      inline const DeviceType GetType() const {
        return _type;
      }
      /**
       * @brief  ���ڑ����̎擾
       * @return ���ڑ���
       */
      static inline int GetConnection() {
        return _connection;
      }
      /**
       * @brief  �L�����ǂ����̔���
       * @return true:�L�� false:��L��
       */
      bool IsActive() const {
        return _active;
      }
    protected:
      static inline int _connection{0}; //!< ���ڑ���
      DeviceType _type{0}; //!< �f�o�C�X�̋@��
      State _state;        //!< ���
      bool _active{true};  //!< �L�����ǂ���
    };
  } // Application
} // AppFrame
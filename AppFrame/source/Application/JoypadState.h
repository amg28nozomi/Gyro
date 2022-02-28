/*****************************************************************//**
 * @file   JoypadState.h
 * @brief  �W���C�p�b�h�̓��͏�ԃN���X
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "InputBase.h"
#include <utility>
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    /**
     * @class JoyoadState
     * @brief �W���C�p�b�h�̓��͏��
     */
    class JoypadState : public InputBase {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      JoypadState();
      /**
       * @brief  ���͏�Ԃ̍X�V
       */
      void Process() override;
      /**
       * @brief  �������̎擾
       * @return �W���C�p�b�h�̉������
       */
      inline int GetKey() const {
        return _press;
      }
      /**
       * @brief  �g���K���̎擾
       * @return �W���C�p�b�h�̃g���K���
       */
      inline int GetTriggerKey() const {
        return _trigger;
      }
      /**
       * @brief  �A�i���O�X�e�B�b�N�̓��͏�Ԏ擾
       * @return first:�����̓��͏�� second:�c���̓��͏��
       */
      inline std::pair<int, int> GetAnalogStick() const {
        return { _stickX, _stickY };
      }
    private:
      int _press{0};   //!< �������
      int _trigger{0}; //!< �g���K���
      int _stickX{0};  //!< �A�i���O�X�e�B�b�N�̓��͏��(x��)
      int _stickY{0};  //!< �A�i���O�X�e�B�b�N�̓��͏��(y��)
    };
  } // namespace Application
} // namespace AppFrame
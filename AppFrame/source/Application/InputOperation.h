/*****************************************************************//**
 * @file   InputOperation.h
 * @brief  ���͏����N���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <string>
#include <vector>
#include <future>
#include "JoypadState.h"
#include "XboxState.h"

/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    // XBOX�R���g���[���̊e��{�^���ɕR�Â��镶����
    constexpr auto PadUp = "up";       //!< ����{�^��
    constexpr auto PadDown = "down";   //!< �����{�^��
    constexpr auto PadLeft = "left";   //!< �����{�^��
    constexpr auto PadRight = "right"; //!< �E���{�^��
    constexpr auto PadStart = "start"; //!< START�{�^��
    constexpr auto PadBack = "back";   //!< BACK�{�^��
    //!< ���X�e�B�b�N
    constexpr auto PadLeftThumb = "leftThumb";
    //!< �E�X�e�B�b�N
    constexpr auto PadRightThumb = "rightThumb";
    //!< LB�{�^��
    constexpr auto PadLeftShoulder = "leftShoulder";
    //!< RB�{�^��
    constexpr auto PadRightShoulder = "rightShoulder";
    constexpr auto PadButtonA = "a"; //!< A�{�^��
    constexpr auto PadButtonB = "b"; //!< B�{�^��
    constexpr auto PadButtonX = "x"; //!< X�{�^��
    constexpr auto PadButtonY = "y"; //!< Y�{�^��
    // �f�o�C�X�^�C�v(���͏�Ԃ̎擾�Ŏg�p)
    constexpr auto DeviceKeyboard = 0; //!< �L�[�{�[�h
    constexpr auto DeviceMouse = 1;    //!< �}�E�X
    constexpr auto DeviceJoypad = 2;   //!< �W���C�p�b�h
    /**
     * @class InputOperation
     * @brief ���͏���
     */
    class InputOperation {
    public:
      /**
       * @brief ���s���
       */
      enum class State {
        Active,   // ����
        Paused,   // �ꎞ��~
        NonActive // �ڑ��Ȃ�
      };
      /**
       * @brief �R���X�g���N�^
       * @param app �A�v���P�[�V�����̎Q��
       */
      InputOperation(class ApplicationBase& app);
      /**
       * @brief �f�X�g���N�^
       */
      ~InputOperation();
      /**
       * @brief �X�V����
       */
      void Process();
      /**
       * @brief  ���̓f�o�C�X�̓o�^
       * @return true:�ǉ����� false:�ǉ����s
       */
      bool AddJoypad();
      /**
       * @brief  ���̓f�o�C�X���ڑ�����Ă��邩�̔���
       * @return true:�ڑ�����@false:�ڑ��Ȃ�
       */
      const bool IsConnection();
      /**
       * @brief  ���s��Ԃ̎擾
       * @return ���s���
       */
      const State OperationState() const {
        return _state;
      }
      /**
       * @brief  XBOX�R���g���[�����͏�Ԃ̎擾
       * @return XBOX�R���g���[���̓��͏�Ԃ̎Q��
       */
      inline XBoxState& GetXBoxState() {
        return _xBox;
      }
      /**
       * @brief  �W���C�p�b�h��Ԃ̎擾
       * @return �W���C�p�b�h�̓��͏�Ԃ̎Q��
       */
      //inline JoypadState& GetJoypadState() {
      //  return _joypad;
      //}
    private:
      ApplicationBase& _app; //!< �A�v���P�[�V�����̎Q��
      State _state{};        //!< ���
      XBoxState _xBox; //!< x�{�b�N�X�R���g���[���̓��͏��
      // JoypadState _joypad;  //!< �W���C�p�b�h�̓��͏��
      int _accessLimit{0};   //!< �f�o�C�X�̐ڑ����
      /**
       * @brief 
       * @param  key �Ώۃ{�^���̃L�[
       * @return 
       */
      int ToNumber(std::string_view key) const;
    };
  } // namespace Application
} // namespace AppFrame
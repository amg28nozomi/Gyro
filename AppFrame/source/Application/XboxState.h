/*****************************************************************//**
 * @file   XBoxState.h
 * @brief  Xbox�R���g���[���[�̓��͏�ԃN���X
 * 
 * @author ��؊�C
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "InputBase.h"
#include <array>
#include <utility>
#include <DxLib.h>
/**
 * @brief �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  /**
   * @brief �A�v���P�[�V�����x�[�X
   */
  namespace Application {
    constexpr auto ButtonNum = 16; //!< �{�^������
    constexpr auto InputPress = true;    //!< �������
    constexpr auto InputTrigger = false; //!< �g���K����
    /**
     * @class XBoxState
     * @brief Xbox�R���g���[���[�̓��͏��(XInput)
     */
    class XBoxState : public InputBase  {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      XBoxState();
      /**
       * @brief  ���͏�Ԃ̍X�V
       */
      void Process() override;
      /**
       * @brief
       * @param min
       * @param max
       * @return 
       */
      bool SetDeadZone(const float min, const float max);
      /**
       * @brief  �{�^�����̎擾(����)
       * @param  key  �Ή�����L�[�ԍ�(0�`15)
       *              DX���C�u������XINPUT�{�^�����͒�`
       * @brief  type �擾������̎��
       *              InputPress:�������(�f�t�H���g) InputTrigger:�g���K���
       * @return true:���͗L�� false:���͖���
       */
      bool GetButton(const int key, const bool type = InputPress) const;
      /**
       * @brief  �A�i���O�X�e�B�b�N�̓��͏�Ԃ��擾
       * @brief  stick ���E�ǂ���̃A�i���O�X�e�B�b�N�̓��͂��擾���邩
       *               false:���X�e�B�b�N�@true:�E�X�e�B�b�N
       * @return first:�����̓��͏�� second:�c���̓��͏��
       */
      std::pair<int, int> GetStick(const bool stick) const;
      /**
       * @brief  ���E�g���K�[�{�^���̓��͏�Ԃ��擾
       * @return first:���g���K�[ second:�E�g���K�[
       */
      inline std::pair<int, int> GetTrigger() const {
        return std::make_pair(_press.LeftTrigger, _press.RightTrigger);
      }
      /**
       * @brief  �f�b�h�]�[���̎擾����
       * @return �f�b�h�]�[��(����:�Œ�l �E��:�ő�l)
       */
      inline std::pair<short, short> GetDeadZone() const {
        return _deadZone;
      }
      /**
       * @brief  �f�b�h�]�[��(�Œ�l)�̎擾
       * @return �f�b�h�]�[��
       */
      inline short GetDeadZoneMin() const {
        return _deadZone.first;
      }
      /**
       * @brief  �f�b�h�]�[��(�ő�l)�̎擾
       * @return �f�b�h�]�[��
       */
      inline short GetDeadZoneMax() const {
        return _deadZone.second;
      }
    private:
      XINPUT_STATE _press;   //!< ���͏��(��������)
      std::array<bool, ButtonNum> _triggerButtons; //!< �e��{�^���̉������
      std::pair<short, short> _deadZone;           //!< �e��X�e�B�b�N�̃f�b�h�]�[�����
      /**
       * @brief  �g���K���̐���
       * @param  press �ΏۃL�[�̉������
       * @param  old   �ΏۃL�[�̉������(�O�t���[��)
       * @return �ΏۃL�[�̃g���K���
       */
      inline int Trigger(const int press, const int old) {
        return press ^ old & press;
      }
      /**
       * @brief �f�b�h�]�[������
       * @param param ���͏��̎Q��
       */
      void DeadZone(short& param);
      /**
       * @brief �A�i���O�X�e�B�b�N�̍X�V
       */
      void AnalogStickUpdate();
    };
  } // namespace Application
} // namespace AppFrame
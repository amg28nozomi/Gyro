/*****************************************************************//**
 * @file   ComboState.h
 * @brief  
 * 
 * @author ��؊�C
 * @date   January 2022
 *********************************************************************/
#pragma once
#include <string>
/**
 * @brief �Q�[���x�[�X
 */
namespace Gyro {
  /**
   * @brief �v���C���[�x�[�X
   */
  namespace Player {
    class ComboState;
    /**
     * @class ComboState
     * @brief �R���{��ԃN���X
     */
    class ComboState {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      ComboState();
      /**
       * @brief  �R���X�g���N�^
       * @param  animName �A�j���[�V������
       * @param  total �����莞��
       * @param  start �W���X�g����̊J�n�t���[��
       * @param  end   �W���X�g����̏I���t���[��
       */
      ComboState(std::string_view animName, float total, float start, float end);
      /**
       * @brief  �X�V����
       * @param  animFrame �A�j���[�V�����̌o�߃t���[��
       * @return 
       */
      virtual bool Process(float animFrame);
      /**
       * @brief  �A�j���[�V�������̎擾
       * @return �A�j���[�V������
       */
      std::string GetAnimName() const {
        return _animName;
      }
      /**
       * @brief  �����莞�Ԃ̎擾
       * @return �����莞��
       */
      float GetTotalTime() const {
        return _totalTime;
      }
      /**
       * @brief  �W���X�g����t���[���̎擾
       * @return �W���X�g����t���[��
       */
      float GetJustTime() const {
        return _justEnd - _justStart;
      }
    protected:
      std::string _animName{}; //!< �A�j���[�V������
      int _key{0};             //!< �A�N�V�����ɕR�Â���
      float _totalTime{0};     //!< �A�j���[�V�����t���[��
      float _inputStart{0};    //!< ���͔���̎�t�J�n�t���[��
      float _inputEnd{0};      //!< ���͔���̎�t�I���t���[��
      float _justStart{0};     //!< �W���X�g����̊J�n�t���[��
      float _justEnd{0};       //!< �W���X�g����̏I���t���[��
      /**
       * @brief  �W���X�g���莞�Ԃ̐ݒ菈��
       * @param  start �J�n�t���[��
       * @param  end   �I���t���[��
       */
      virtual void SetJustTime(float start, float end);
    };
  } // namespace Player
} // namespace Gyro